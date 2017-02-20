############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
set_directive_interface -mode ap_ctrl_none "toplevel"
set_directive_resource -core AXI4Stream "toplevel" input
set_directive_resource -core AXI4Stream "toplevel" output
set_directive_stream -depth 500 -dim 1 "calculate_distances" visit_queue
set_directive_inline -recursive "toplevel"
set_directive_array_partition -type complete -factor 4 -dim 1 "permute" permutation
set_directive_array_map -instance bla -mode horizontal "toplevel" waypoint_distances
set_directive_array_map -instance bla -mode horizontal "toplevel" world
set_directive_array_map -instance bla -mode horizontal "toplevel" best_route
set_directive_unroll -factor 11 "check_route/summing_loop"
set_directive_pipeline "permute/k_find"
set_directive_pipeline "permute/l_find"
set_directive_pipeline "permute/reverse"
set_directive_pipeline "permute/permutation_init"
