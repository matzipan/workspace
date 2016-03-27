#include "toplevel.h"

int main() {
    hls::stream<uint32> to_hw, from_hw;

    uint32 testdata[NUMTESTS*2] = {20, 2, 28, 7, 10034, 23, 3861, 235, 39316, 384, 20106, 395, 5721, 944, 25, 1, 738, 346, 50205, 19};
	uint32 expectedresults[NUMTESTS] = {10, 4, 436, 16, 102, 50, 6, 25, 2, 2642};

    //Write input data
    for(int i = 0; i < NUMTESTS*2; i++) {
        to_hw.write(testdata[i]);
    }

    //Run the hardware
    toplevel(to_hw, from_hw);

    //Read and report the output

    for(int i = 0; i < NUMTESTS; i++) {
		uint32 result = from_hw.read();
		if(result != expectedresults[i]) {
			printf("Expected %d and got %d\n", (uint) expectedresults[i], (uint) result);
			return 1;
		}
	}

    printf("Succeeded\n");
    return 0;
}
