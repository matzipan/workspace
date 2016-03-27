pragma Task_Dispatching_Policy(FIFO_Within_Priorities);
with Infinite_Work;
with System; use System;
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;

procedure Main is
   protected Controlled_Interrupt is
     entry Wait_For_Interrupt;
     procedure Interrupt_Now;
   private
      Go : Boolean := False;
   end Controlled_Interrupt;

   protected body Controlled_Interrupt is
      entry Wait_For_Interrupt when Go is
      begin
        Go := False;
      end Wait_For_Interrupt;

      procedure Interrupt_Now is
      begin
        Go := True;
      end Interrupt_Now;

   end Controlled_Interrupt;

   task Worker is
      pragma Priority(System.Priority'First + 1 );
   end Worker;

   task body Worker is
   begin
      select
         Controlled_Interrupt.Wait_For_Interrupt;
         Put_Line ("Interrupted");
      then abort
         Infinite_Work;
      end select;
   end Worker;

   task Boss is
      pragma Priority(System.Priority'First + 5);
   end Boss;

   task body Boss is
   begin
     delay 0.5;
      Controlled_Interrupt.Interrupt_Now;
   end Boss;

begin
   null;
end Main;
