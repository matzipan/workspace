############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
open_project solvercore
set_top toplevel
add_files solvercore/src/toplevel.cpp
add_files solvercore/src/toplevel.h
add_files -tb solvercore/src/testbench.cpp
open_solution "solvercore"
set_part {xc3s500efg320-4}
create_clock -period 20 -name default
source "./solvercore/solvercore/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format pcore -use_netlist none
