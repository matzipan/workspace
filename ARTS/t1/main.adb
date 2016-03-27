with Ada.Text_IO;use Ada.Text_IO;
procedure Main is
   task Hello;
   task body Hello is
   begin
      Put_line("Hello World");
   end Hello;

begin
   null;
end Main;
