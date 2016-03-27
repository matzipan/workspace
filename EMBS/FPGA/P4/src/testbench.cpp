#include "toplevel.h"

int main() {
    hls::stream<uint32> to_hw, from_hw;
    uint32 testdata[NUMDATA];

    //Create input data
    for(int i = 0; i < NUMDATA; i++) {
        testdata[i] = i;
    }
    testdata[0] = 2000;
    //Write input data
    for(int i = 0; i < NUMDATA; i++) {
        to_hw.write(testdata[i]);
    }

    //Run the hardware
    toplevel(to_hw, from_hw);

    //Read and report the output
    int sum = from_hw.read();
    int sub = from_hw.read();
    printf("Sum of input: %d\n", sum);
    printf("Values 1 to %d subtracted from value 0: %d\n", NUMDATA-1, sub);

    //Check values
    if(sum == 2780 && sub == 1220) {
        return 0;
    } else {
        return 1; //An error!
    }
}
