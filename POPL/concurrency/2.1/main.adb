with Ada.Text_IO; use Ada.Text_IO;

procedure Main is
	X : Integer := 0;

   	procedure Sync is 
	   	task type T;
	   	task body T is
	   	begin
	   		for I in 1..20 loop
	   			X := X+1;
	   		end loop;
	   	end T;

	   	T1: T;
	   	T2: T;
   	begin null; end;
begin
   Sync; Put_Line(X'Img);
end Main;