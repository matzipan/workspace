#ifndef __TOPLEVEL_H_
#define __TOPLEVEL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ap_int.h>
#include <hls_stream.h>

//Typedefs
typedef ap_uint<32> uint32;
typedef ap_uint<8> uint8;
typedef ap_int<32> int32;

#define NUMTESTS 10

//Prototypes
void toplevel(hls::stream<uint32> &input, hls::stream<uint32> &output);

#endif
