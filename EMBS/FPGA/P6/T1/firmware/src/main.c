#include <stdio.h>
#include <stdlib.h>
#include "xparameters.h"
#include "xtmrctr.h"
#include "fsl.h"

#define NUMTESTS 10

int main(void) {
	XTmrCtr timer;
	XTmrCtr_Initialize(&timer, XPAR_TMRCTR_0_DEVICE_ID);

	XTmrCtr_SetResetValue(&timer, 0, 0); // Set the value that the timer resets to (in this case, 0 -second value-)
	XTmrCtr_Reset(&timer, 0); // Reset timer 0
	XTmrCtr_Start(&timer, 0); // Start timer 0

    int i;
    uint init_val, final_val;
    volatile uint testdata[NUMTESTS*2] = {20, 2, 28, 7, 10034, 23, 3861, 235, 39316, 384, 20106, 395, 5721, 944, 25, 1, 738, 346, 50205, 19};
    volatile uint output[NUMTESTS];
    uint expectedresults[NUMTESTS] = {10, 4, 436, 16, 102, 50, 6, 25, 2, 2642};


    init_val = XTmrCtr_GetValue(&timer, 0);
    for(i = 0; i < NUMTESTS; i++) {
    	output[i] = testdata[i*2] / testdata[i*2+1];
    }
    final_val = XTmrCtr_GetValue(&timer, 0);

    xil_printf("Microblaze took %d ns \n\r", final_val-init_val);

    //Check and print out the results
    for(i = 0; i < NUMTESTS; i++) {
        if(output[i] != expectedresults[i]) {
            xil_printf("ERROR: Expected %d. Calculated %d.\n\r", expectedresults[i], output[i]);
        }
    }

    init_val = XTmrCtr_GetValue(&timer, 0);

    //Write input data
	for(i = 0; i < NUMTESTS*2; i++) {
	    putfslx(testdata[i], 0, FSL_DEFAULT);
	}

	//Read and report the output
	for(i = 0; i < NUMTESTS; i++) {
		uint result;
		getfslx(result, 0, FSL_DEFAULT);
		if(result != expectedresults[i]) {
			xil_printf("Expected %d and got %d (0x%x)\n\r", expectedresults[i], result, result);
		}
	}

    final_val = XTmrCtr_GetValue(&timer, 0);

    xil_printf("Divcore took %d ns \n\r", final_val-init_val);



    return 0;
}