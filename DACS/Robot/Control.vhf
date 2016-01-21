--------------------------------------------------------------------------------
-- Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.2
--  \   \         Application : sch2hdl
--  /   /         Filename : Control.vhf
-- /___/   /\     Timestamp : 05/17/2013 16:23:27
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family xc9500xl -flat -suppress -vhdl H:/documents/Robot/Control.vhf -w H:/documents/Robot/Control.sch
--Design Name: Control
--Device: xc9500xl
--Purpose:
--    This vhdl netlist is translated from an ECS schematic. It can be 
--    synthesized and simulated, but it should not be modified. 
--

library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity OR7_MXILINX_Control is
   port ( I0 : in    std_logic; 
          I1 : in    std_logic; 
          I2 : in    std_logic; 
          I3 : in    std_logic; 
          I4 : in    std_logic; 
          I5 : in    std_logic; 
          I6 : in    std_logic; 
          O  : out   std_logic);
end OR7_MXILINX_Control;

architecture BEHAVIORAL of OR7_MXILINX_Control is
   attribute BOX_TYPE   : string ;
   signal I36 : std_logic;
   component OR4
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             I3 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR4 : component is "BLACK_BOX";
   
begin
   I_36_89 : OR4
      port map (I0=>I3,
                I1=>I4,
                I2=>I5,
                I3=>I6,
                O=>I36);
   
   I_36_90 : OR4
      port map (I0=>I0,
                I1=>I1,
                I2=>I2,
                I3=>I36,
                O=>O);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity Control is
   port ( BK  : in    std_logic; 
          BW  : in    std_logic; 
          FW  : in    std_logic; 
          LR  : in    std_logic; 
          LT  : in    std_logic; 
          RR  : in    std_logic; 
          RT  : in    std_logic; 
          LM0 : out   std_logic; 
          LM1 : out   std_logic; 
          Q0  : out   std_logic; 
          Q1  : out   std_logic; 
          Q2  : out   std_logic; 
          Q3  : out   std_logic; 
          Q4  : out   std_logic; 
          RM0 : out   std_logic; 
          RM1 : out   std_logic);
end Control;

architecture BEHAVIORAL of Control is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   signal LMB       : std_logic;
   signal XLXN_1512 : std_logic;
   component OR7_MXILINX_Control
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             I3 : in    std_logic; 
             I4 : in    std_logic; 
             I5 : in    std_logic; 
             I6 : in    std_logic; 
             O  : out   std_logic);
   end component;
   
   component OR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR2 : component is "BLACK_BOX";
   
   component OR4
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             I3 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR4 : component is "BLACK_BOX";
   
   component OR3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR3 : component is "BLACK_BOX";
   
   component BUF
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of BUF : component is "BLACK_BOX";
   
   attribute HU_SET of XLXI_327 : label is "XLXI_327_62";
begin
   XLXI_327 : OR7_MXILINX_Control
      port map (I0=>BK,
                I1=>RT,
                I2=>LT,
                I3=>RR,
                I4=>LR,
                I5=>FW,
                I6=>BW,
                O=>Q0);
   
   XLXI_360 : OR2
      port map (I0=>BK,
                I1=>RT,
                O=>LMB);
   
   XLXI_362 : OR2
      port map (I0=>BK,
                I1=>LT,
                O=>XLXN_1512);
   
   XLXI_409 : OR4
      port map (I0=>XLXN_1512,
                I1=>RT,
                I2=>LR,
                I3=>FW,
                O=>RM0);
   
   XLXI_412 : OR3
      port map (I0=>BW,
                I1=>RR,
                I2=>XLXN_1512,
                O=>RM1);
   
   XLXI_413 : OR4
      port map (I0=>LMB,
                I1=>LT,
                I2=>RR,
                I3=>FW,
                O=>LM0);
   
   XLXI_414 : OR3
      port map (I0=>BW,
                I1=>LR,
                I2=>LMB,
                O=>LM1);
   
   XLXI_424 : OR2
      port map (I0=>BW,
                I1=>FW,
                O=>Q1);
   
   XLXI_426 : OR2
      port map (I0=>RR,
                I1=>LR,
                O=>Q2);
   
   XLXI_427 : OR2
      port map (I0=>RT,
                I1=>LT,
                O=>Q3);
   
   XLXI_428 : BUF
      port map (I=>BK,
                O=>Q4);
   
end BEHAVIORAL;


