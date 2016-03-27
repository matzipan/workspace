#include "toplevel.h"

//Top-level function
void toplevel(hls::stream<uint32> &input, hls::stream<uint32> &output) {
#pragma HLS RESOURCE variable=input core=AXI4Stream
#pragma HLS RESOURCE variable=output core=AXI4Stream
#pragma HLS INTERFACE ap_ctrl_none port=return

    for(int i = 0; i < NUMTESTS; i++) {
#pragma HLS PIPELINE
    	uint32 x = input.read();
    	uint32 y = input.read();

		output.write(x/y);
	}
}
