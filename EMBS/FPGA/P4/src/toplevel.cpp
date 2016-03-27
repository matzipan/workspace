#include "toplevel.h"

//Input data storage
int32 inputdata[NUMDATA];

//Prototypes
int32 addall(int32 *data);
int32 subfromfirst(int32 *data);

//Top-level function
void toplevel(hls::stream<uint32> &input, hls::stream<uint32> &output) {
#pragma HLS ARRAY_PARTITION variable=inputdata complete dim=1
#pragma HLS RESOURCE variable=input core=AXI4Stream
#pragma HLS RESOURCE variable=output core=AXI4Stream
#pragma HLS INTERFACE ap_ctrl_none port=return

    //Read in NUMDATA items
    readloop: for(int i = 0; i < NUMDATA; i++) {
#pragma HLS UNROLL
        inputdata[i] = input.read();
    }

    int32 val1 = addall(inputdata);
    output.write(val1);
    int32 val2 = subfromfirst(inputdata);
    output.write(val2);
}

int32 addall(int32 *data) {
#pragma HLS INLINE
    int32 total = 0;
    addloop: for(int i = 0; i < NUMDATA; i++) {
#pragma HLS UNROLL
        total = total + data[i];
    }
    return total;
}

int32 subfromfirst(int32 *data) {
#pragma HLS INLINE
    int32 total = data[0];
    subloop: for(int i = 1; i < NUMDATA; i++) {
#pragma HLS UNROLL
        total = total - data[i];
    }
    return total;
}
