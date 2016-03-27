with Ada.Text_IO; use Ada.Text_Io;
procedure Infinite_Work is
  F : Duration := 0.0;
begin
  Put_Line("Working");
  loop
    F := 0.0;
    for J in 1 .. 10000 loop
      F := F + Duration(J * 10.0);
    end loop;
    Put_Line("Still Working");
  end loop;
end Infinite_Work;
