pragma Task_Dispatching_Policy(FIFO_Within_Priorities);
with Ada.Text_IO; use Ada.Text_IO;
with System; use System;
with Ada.Real_Time; use Ada.Real_Time;
with Ada.Real_Time.Timing_Events; use Ada.Real_Time.Timing_Events;

procedure Main is
  TE : aliased Timing_Event;
  Period : Time_Span := Milliseconds(50);
  Start_Time : Time := Clock + Milliseconds(100);

  protected Releaser is
      entry Wait_Next_Release;
      procedure Release(Event : in out Timing_Event);
   private
   Go : Boolean := False;
   Next_Time : Time := Start_Time;
   end Releaser;

   protected body Releaser is
      entry Wait_Next_Release when Go is
      begin
        Go := False;
      end Wait_Next_Release;

      procedure Release(Event : in out Timing_Event) is
      begin
        Go := True;
        Next_Time := Next_Time + Period;
        Event.Set_Handler(Next_Time, Release'Unrestricted_Access);
      end Release;
   end Releaser;

   task Periodic is
      pragma Priority(System.Priority'First + 5);
   end Periodic;

   task body Periodic is
   begin
      TE.Set_Handler(Start_Time, Releaser.Release'Unrestricted_Access);
      for i in 1 .. 100 loop
        Releaser.Wait_Next_Release;
        Put_Line("High priority executing now");
      end loop;
   end Periodic;

   task Worker is
      pragma Priority(System.Priority'First);
   end Worker;

   task body Worker is
     I : Integer := 0
     F1 : Integer := 0;
     F2 : Integer := 0;
   begin
     delay until Start_Time;
     loop
       Put_Line("Low Executing");
       for J in 1 .. 10000 loop
         F1 := F1 + J * 2;
       end loop;

       for J in 1 .. 1000 loop
         F2 := F2 + J * 2;
       end loop;
       I := I + 1;
       exit when I = 30;
     end loop;
     Put_Line("Low terminating");
     exception when others => Put_Line("Low terminating with exception");
   end Worker;
begin
   null;
end Main;
