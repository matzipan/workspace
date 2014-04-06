with Ada.Text_IO; use Ada.Text_IO;
with Ada.integer_text_IO; use Ada.integer_text_IO;

procedure Main is
	Buffer_Size : constant Integer :=5;
	type Index is mod Buffer_Size;
	subtype Count is Natural range 0 .. Buffer_Size;
	type Buffer is array (Index) of Integer;
	
	protected type Bounded_Buffer is
		entry Get (Item : out Integer);
		entry Put (Item : in Integer);
	private
		First : Index := Index'First;
		Last : Index := Index'Last;
		Num : Count := 0;
		Buf : Buffer;
	end Bounded_Buffer;

	protected body Bounded_Buffer is
		entry Get (Item : out Integer) when Num /= 0 is
		begin
			Item := Buf(First);
			First := First + 1; 
			Num := Num - 1;
			end Get;
		entry Put (Item : in Integer) when 
			Num /= Buffer_Size is
		begin
			Last := Last + 1;
			Num := Num + 1;
			Buf(Last) := Item;
		end Put;
	end Bounded_Buffer;

	My_Buffer : Bounded_Buffer;
	

	task type Consumer;
	task type Producer; 

	Consumers : array(1 .. 10) of Consumer;
	Producers : array(1 .. 10) of Producer;

	task body Consumer is
		V : integer;
	begin
		for I in 0..4 loop
			My_Buffer.Get(V);
			Put(V); 
			New_Line;
		end loop;
	end Consumer;

	task body Producer is
	begin
		for I in 10..14 loop
			delay 0.5;
			My_Buffer.Put(I);
		end loop;
	end Producer;
begin
	null;
end Main;