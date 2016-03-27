with Infinite_Work;
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;
procedure Main is
   task Worker;
   task body Worker is
     Deadline : Time := Clock + Seconds(1);
   begin
      select
        delay until Deadline;
        Put_Line ("Interrupted");
      then abort
         Infinite_Work;
      end select;
   end Worker;
begin
   null;
end Main;
