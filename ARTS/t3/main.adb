with Ada.Text_IO; use Ada.Text_IO;
procedure Main is

   Global_Array : array (1 .. 100) of Integer;
   pragma Volatile(Global_Array);
   procedure Go is
      procedure Slow_Down is
      begin
         for i in 1 .. 10000 loop
            null;
         end loop;
      end Slow_Down;


      task One;
      task body One is
      begin
         Put_Line("One running");
         for i in Global_Array'Range loop
            if Global_Array (i) = 7 then
               Global_Array (i) := 1;
            else
               Global_Array (i) := 1;
               --Slow_Down;
            end if;
         end loop;
      end One;

      task Seven;
      task body Seven is
      begin
         Put_Line("Seven running");
         for i in Global_Array'Range loop
            if Global_Array (i) = 1 then
               Global_Array (i) := 7;
            else
               Global_Array (i) := 7;
             --Slow_Down; -- with this, the tasks end up being interleaved
            end if;
         end loop;
      end Seven;
   begin
      null;
   end Go;

begin

   for i in Global_Array'Range loop
      Global_Array (i) := 0;
   end loop;

   Go;

   for i in Global_Array'Range loop
     Put(Integer'Image(Global_Array(i)) & " ");
   end loop;
   New_Line;

end Main;
