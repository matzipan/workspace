pragma Task_Dispatching_Policy(FIFO_Within_Priorities);
with Ada.Text_IO; use Ada.Text_IO;
with System; use System;
with Ada.Real_Time; use Ada.Real_Time;
procedure Main is

   Start_Time : Time := Clock + Milliseconds(100);
   task Periodic is
      pragma Priority(System.Priority'First + 5);
   end Periodic;

   task body Periodic is
      Period : Time_Span := milliseconds(10);
      Next_Time: Time := Clock + Period;
   begin
      delay until Start_Time;
      for i in 1 .. 10 loop
         delay until Next_Time;
         Put_Line("High priority executing now");
         Next_Time := Clock + Period;
      end loop;
   end Periodic;

   task Worker is
      pragma Priority(System.Priority'First);
   end Worker;

   task body Worker is
     I : Integer := 0;
     F : Duration := 0.0;
   begin
      delay until Start_Time;
      loop
        Put_Line("Low Executing");
        F := 0.0;
       for J in 1 .. 1000 loop
         F := F + Duration(J * 10.0);
       end loop;
       I := I + 1;
       exit when I = 5000;
      end loop;
      Put_Line("Low terminating");
   end Worker;
begin
   null;
end Main;
