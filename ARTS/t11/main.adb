with Finite_Work;
with Ada.Real_Time; use Ada.Real_Time;
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Execution_Time; use Ada.Execution_Time;

procedure Prac_11 is
   task Worker;
   task body Worker is
      Actual_CPU_Time  : Time_Span;
      Initial_CPU_Time : CPU_Time;
      Final_CPU_Time   : CPU_Time;
   begin
      for i in 1 .. 10 loop
         Put_Line("Timing " & Integer'Image(i*100) & " cycles");
         Initial_CPU_Time := Ada.Execution_Time.Clock;
         Finite_Work (i*100);
         Final_CPU_Time  := Ada.Execution_Time.Clock

         Actual_CPU_Time := Final_CPU_Time - Initial_CPU_Time;
         Put_Line
           ("Time taken is " &
            Duration'Image (To_Duration (Actual_CPU_Time)) &
              " seconds");
         New_Line;
      end loop;
   end Worker;
begin
   null;
end Prac_11;
