with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Discrete_Random;

procedure Main is
    subtype Delay_Time is Integer range 1 .. 10;
    package Random_Integer is new Ada.Numerics.Discrete_Random(Delay_Time);

   type Client_Id is new Integer range 1 .. 6;
   type Bools is array (Client_Id'Range) of Boolean;

   protected Controller is
      entry Barrier_Wait(Calling_Client : Client_Id);
   private
      entry Wait_Release (Client_Id'Range) (Calling_Client : Client_Id);
      Open_Barrier : Bools   := (others => False);
      Arrived      : Integer := 0;
  end Controller;

   protected body Controller is
      entry Barrier_Wait(Calling_Client : Client_Id) when True is
      begin
          Arrived := Arrived + 1;
          if Arrived = Integer (Client_Id'Last) then
             Open_Barrier (1) := True;
          end if;
          requeue Wait_Release (Calling_Client) with abort;
      end Barrier_Wait;

      entry Wait_Release(for i in Client_Id'Range) (Calling_Client : Client_Id) when Open_Barrier(i) is
      begin
          Put_Line("Client " & Client_Id'Image(Calling_Client) & " Being Released from Barrier");
          if i /= Client_Id'Last then
              Open_Barrier (Client_Id'Succ (i))  := True;
          end if;
      end Wait_Release;
   end Controller;

   task type Client(Id : Client_Id);

   task body Client is
       Gen : Random_Integer.Generator;
       Random_Int : Integer;
   begin
       Random_Integer.Reset (Gen, Integer (Id));
       Random_Int := Random_Integer.Random (Gen);
       Put_Line("Task " & Client_Id'Image (Id) & " Random delay is " & Integer'Image (Random_Int));
       delay Random_Int * 1.0;

        Put_Line("Client " & Client_Id'Image(Id) & " Waiting at Barrier");
        select
            Controller.Barrier_Wait(Id);
            Put_Line("Client " & Client_Id'Image(Id) & " Released from Barrier");
        or delay 10.0;
            Put_Line("Client " & Client_Id'Image(Id) & " Missed Released from Barrier");
        end select;
    exception when others =>
         Put_Line ("Oh dear");
   end Client;

   C1: Client(1);
   C2: Client(2);
   C3: Client(3);
   C4: Client(4);
   C5: Client(5);
   C6: Client(6);
begin
   null;
end Main;
