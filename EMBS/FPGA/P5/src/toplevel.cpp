#include "toplevel.h"

//Input data storage
uint1 matrix[SIZE][SIZE];

uint4 inline get_neighbour(uint32 i, uint32 j) {
#pragma HLS INLINE
	return (uint4) (matrix[i][j] & 0x1);
}


//Top-level function
void toplevel(hls::stream<uint32> &input, hls::stream<uint32> &output) {
	#pragma HLS ARRAY_PARTITION variable=matrix dim=2
	#pragma HLS ARRAY_PARTITION variable=matrix dim=1
	#pragma HLS RESOURCE variable=input core=AXI4Stream
	#pragma HLS RESOURCE variable=output core=AXI4Stream
	#pragma HLS INTERFACE ap_ctrl_none port=return

    read: for(uint32 i=0; i<SIZE; i++) {
		#pragma HLS LOOP_UNROLL

    	uint32 value = input.read();

    	unpack: for(uint32 j=0; j<SIZE; j++) {
			#pragma HLS LOOP_UNROLL

    		 matrix[i][j] = (value >> j) & 0x1;
    	 }
    }

    outer: for(uint32 i=0; i< SIZE; i++) {
		#pragma HLS LOOP_UNROLL
		#pragma HLS PIPELINE

     	uint32 value = 0;

    	inner: for(uint32 j=0; j<SIZE; j++) {
			#pragma HLS LOOP_UNROLL
			#pragma HLS PIPELINE

    		uint4 neighbours = 0;
    		uint1 i0 = i==0;
    		uint1 j0 = j==0;
    		uint1 imax = i==SIZE-1;
    		uint1 jmax = j==SIZE-1;

    		if(i0 && j0) {
    			neighbours = get_neighbour(i,j+1) + get_neighbour(i+1,j) + get_neighbour(i+1,j+1);
    		} else if(imax && j0) {
    			neighbours = get_neighbour(i-1,j) + get_neighbour(i-1,j+1) + get_neighbour(i,j+1);
    		} else if(i0 && jmax) {
    			neighbours = get_neighbour(i,j-1) + get_neighbour(i+1,j) + get_neighbour(i+1,j-1);
    		} else if(imax && jmax) {
    			neighbours = get_neighbour(i-1,j-1) + get_neighbour(i-1,j) + get_neighbour(i,j-1);
    		} else if(i0) {
    			neighbours = get_neighbour(i,j-1) + get_neighbour(i,j+1) + get_neighbour(i+1,j-1) + get_neighbour(i+1,j) + get_neighbour(i+1,j+1);
    		} else if(imax) {
    			neighbours = get_neighbour(i,j-1) + get_neighbour(i,j+1) + get_neighbour(i-1,j-1) + get_neighbour(i-1,j) + get_neighbour(i-1,j+1);
    		} else if(j0) {
    			neighbours = get_neighbour(i-1,j) + get_neighbour(i+1,j) + get_neighbour(i-1,j+1) + get_neighbour(i,j+1) + get_neighbour(i+1,j+1);
    		} else if(jmax) {
    			neighbours = get_neighbour(i-1,j) + get_neighbour(i+1,j) + get_neighbour(i-1,j-1) + get_neighbour(i,j-1) + get_neighbour(i+1,j-1);
    		} else {
    			neighbours = get_neighbour(i-1,j-1) + get_neighbour(i-1,j) + get_neighbour(i-1,j+1) + get_neighbour(i,j-1) + get_neighbour(i,j+1) + get_neighbour(i+1,j-1) + get_neighbour(i+1,j) + get_neighbour(i+1,j+1);
    		}

    		switch(neighbours) {
				case 2:
		 			value |= ((matrix[i][j] != 0) & 0x1) << j;

					break;
				case 3:
		 			value |= 1 << j;

					break;
    		}
    	}

 		output.write(value);
    }


}
