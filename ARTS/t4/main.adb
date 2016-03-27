with Ada.Text_IO; use Ada.Text_IO;
procedure Main is

   Global_Array : array (1 .. 100) of Integer;

   protected Turn is
      entry Wait_Ones_Turn(Index : Integer);
      entry Wait_Sevens_Turn(Index : Integer);
   private
      Last : Integer := 7;
      Count : Integer := 1;
   end Turn;

   protected body Turn is
      entry Wait_Ones_Turn(Index : Integer) when Last = 7 is
      begin
          if Count = 1 then
             Last := 1;
             Count := 0;
          else
             Count := Count + 1;
          end if;
         Global_Array (Index) := 1;
      end Wait_Ones_Turn;

      entry Wait_Sevens_Turn(Index : Integer) when Last = 1 is
      begin
          If Count = 1 then
            Last := 7;
            Count := 0;
         else
            Count := Count + 1;
         end if;
         Global_Array (Index) := 7;
      end Wait_Sevens_Turn;
   end Turn;

   procedure Go is
       task Seven;
       task body Seven is
       begin
          for i in Global_Array'Range loop
            Put_line("Waiting for seven's turn");
             Turn.Wait_Sevens_Turn(i);
          end loop;
       end Seven;
       
      task One;
      task body One is
      begin
         for i in Global_Array'Range loop
            Put_line("Waiting for one's turn");
            Turn.Wait_Ones_Turn(i);
         end loop;
      end One;


   begin
      null;
   end Go;

begin
   Go;
   for i in Global_Array'Range loop
     Put_line(Integer'Image(Global_Array(i)));
   end loop;
end Main;
