############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
open_project bla
set_top toplevel
add_files bla/src/toplevel.cpp
add_files bla/src/toplevel.h
add_files -tb bla/src/testbench.cpp
open_solution "solution1"
set_part {xc3s1600efg320-4}
create_clock -period 20 -name default
#source "./bla/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
