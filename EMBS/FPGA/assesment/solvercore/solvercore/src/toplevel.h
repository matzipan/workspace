#ifndef __TOPLEVEL_H_
#define __TOPLEVEL_H_

#include <stdio.h>
#include <stdlib.h>
#include <ap_int.h>
#include <hls_stream.h>

//Typedefs
typedef ap_uint<32> u32;
typedef ap_uint<16> u16;
typedef ap_int<32> i32;
typedef ap_int<8> i8;
typedef ap_int<5> i5;
typedef ap_int<9> i9;
typedef ap_uint<8> u8;
typedef ap_uint<6> u6;
typedef ap_uint<1> u1;
typedef ap_uint<4> u4;
typedef ap_uint<7> u7;
typedef ap_uint<12> u12;
typedef ap_int<13> i13;


//Prototypes
void toplevel(hls::stream<u32> &input, hls::stream<u32> &output);

#define WORLD_WALL 0
#define WORLD_EMPTY 1
#define WAYPOINT_INDEX(x) x + 12
#define WAYPOINT_ID(x) x - 12
#define IS_WAYPOINT(x) x < 0

#endif
