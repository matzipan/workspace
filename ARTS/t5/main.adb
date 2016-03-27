with Ada.Text_IO; use Ada.Text_IO;
procedure Main is
   type Client_Id is new Integer range 1 .. 6;

   Releaser : constant Client_Id := 6;
   Open_Barrier : Boolean := False;


   protected Controller is
      entry Barrier_Wait(Calling_Client : Client_Id);
   private
      entry Wait_Release(Calling_Client : Client_Id);
      Open_Barrier : Boolean := False;
  end Controller;

   protected body Controller is
      entry Barrier_Wait(Calling_Client : Client_Id) when True is
      begin
          if Calling_Client = Releaser then
            Open_Barrier := True;
         else
            requeue Wait_Release with abort;
         end if;
      end Barrier_Wait;

      entry Wait_Release(Calling_Client : Client_Id) when Open_Barrier is
      begin
          Put_Line("Client " & Client_Id'Image(Calling_Client) & " Being Released from Barrier");
          if Wait_Release'Count = 0 then
             Open_Barrier := False;
          end if;
      end Wait_Release;
   end Controller;

   task type Client(Id : Client_Id);

   task body Client is
   begin
      Put_Line("Client " & Client_Id'Image(Id) & " Waiting at Barrier");
      select
        Controller.Barrier_Wait(Id);
         Put_Line("Client " & Client_Id'Image(Id) & " Released from Barrier");
      or delay 3.0;
         Put_Line("Client " & Client_Id'Image(Id) & " Missed Released from Barrier");
      end select;

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
