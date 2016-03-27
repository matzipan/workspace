with MaRTE_OS;
with Text_IO;
with Chute;
with Ada.Real_Time; use Ada.Real_Time;

procedure Main is
  Period : Time_Span := milliseconds(500);

begin

   Text_IO.New_Line;
   Text_IO.Put ("Hello, This is a Ada program running on MaRTE OS.");
   Text_IO.New_Line (2);

   while True loop
     Chute.Hopper_Load
     delay Period;
     Chute.Hopper_Unload
     delay Period;
   end loop;

end Main;
