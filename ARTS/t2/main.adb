with Ada.Text_IO;use Ada.Text_IO;
procedure Main is
   task Numbers;
   task body Numbers is
   begin
      for i in 1 .. 100 loop
         Put_line(Integer'Image(i));
      end loop;
   end Numbers;


   task Hello;
   task body Hello is
   begin
      for i in Character'('a') .. Character'('z') loop
         Put_Line(Character'Image(i));
      end loop;
      for i in Character'('A') .. Character'('Z') loop
         Put_Line(Character'Image(i));
      end loop;
   end Hello;

begin
   null;
end Main;
