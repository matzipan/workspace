############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
open_project md5core
set_top toplevel
add_files md5core/solution1/src/toplevel.cpp
add_files md5core/solution1/src/toplevel.h
add_files -tb md5core/solution1/src/testbench.cpp
open_solution "solution1"
set_part {xc3s500efg320-4}
create_clock -period 20 -name default
#source "./md5core/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format pcore -use_netlist none
