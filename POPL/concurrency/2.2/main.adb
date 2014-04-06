with Ada.integer_text_IO; use Ada.integer_text_IO;

procedure Main is

	protected Barrier is
		entry Wait(Val : out integer);
		procedure Go(Val : integer);
		private
			X : Integer := 0;
			Go_Called : Boolean := False;
			Releasing : Boolean := False;
	end Barrier;
	protected body Barrier is
		entry Wait(Val : out integer) when (Wait'Count = 4 and Go_Called) or Releasing is 
		begin
			Releasing := True;
			if Wait'Count = 0 then
				Releasing := False;
				Go_Called := False;
			end if;
			Val:=X;
		end Wait;

		procedure Go(Val : integer) is
		begin
			Go_Called := True;
			if Wait'Count = 4 then
				Releasing := True;
			end if;
			X:=Val;
		end Go;
	end Barrier;

	task type Consumer;
	task Producer; 

	c1,c2,c3,c4: Consumer;

	task body Consumer is
		V : integer;
	begin
		for I in 1..5 loop
			Barrier.Wait(V);
		end loop;
		put(V);
	end Consumer;

	task body Producer is
	begin
		for I in 10..14 loop
			delay 0.5;
			Barrier.Go(I);
		end loop;
	end Producer;

begin
	null;
end Main;