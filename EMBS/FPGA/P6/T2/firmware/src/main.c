#include <stdio.h>
#include <stdlib.h>
#include "xparameters.h"
#include "xtmrctr.h"
#include "fsl.h"

uint hex_to_binary(char hex_char) {
	if(hex_char >= '0' && hex_char <= '9') {
		return hex_char - '0';
	}
	if(hex_char >= 'A' && hex_char <= 'F') {
		return hex_char - 'A' + 10;
	}
	if(hex_char >= 'a' && hex_char <= 'f') {
		return hex_char - 'a' + 10;
	}

	return 0;
}

int main(void) {
	XTmrCtr timer;
	XTmrCtr_Initialize(&timer, XPAR_TMRCTR_0_DEVICE_ID);

	XTmrCtr_SetResetValue(&timer, 0, 0); // Set the value that the timer resets to (in this case, 0 -second value-)
	XTmrCtr_Reset(&timer, 0); // Reset timer 0
	XTmrCtr_Start(&timer, 0); // Start timer 0

    uint i, j, pack, sent = 0, errored = 0, initial_length = 0, packed_outgoing[16], packed_incoming[16], results[4];
    uint timer_init_val, timer_final_val;
    char str[] = "This is my entry into the EMBS MD5 challenge";
    char expected_result[] = "15b669c0e5490d8d4335ca0d274f2bbb";

    for(i = 0; str[i] != 0; i++) {
    	if(i % 4 == 0) {
    		pack = 0;
    	}

    	pack |= str[i] << ((3 - i%4) * 8);

    	if(i % 4 == 3) {
    		packed_outgoing[sent] = pack;
    		sent++;
    	}
    }

    for(i = sent; i < 16; i++) {
    	packed_outgoing[i] = 0;
    }

    timer_init_val = XTmrCtr_GetValue(&timer, 0);

    for(i = 0; i < 16; i++) {
        putfslx(packed_outgoing[i], 0 , FSL_DEFAULT);
    }

    for(i = 0; i < 4; i++) {
    	uint result;
		getfslx(result, 0, FSL_DEFAULT);

		results[i] = result;
	}

	timer_final_val = XTmrCtr_GetValue(&timer, 0);

	for(i = 0; i < 4; i++) {
			if(0xFF000000 & results[i]) {
				packed_incoming[initial_length] = (results[i] & 0xFF000000) >> 24;
				initial_length++;
			}

			if(0xFF0000 & results[i]) {
				packed_incoming[initial_length] = (results[i] & 0xFF0000) >> 16;
				initial_length++;
			}

			if(0xFF00 & results[i]) {
				packed_incoming[initial_length] = (results[i] & 0xFF00) >> 8;
				initial_length++;
			}
			if(0xFF & results[i]) {
				packed_incoming[initial_length] = results[i] & 0xFF;
				initial_length++;
			}
		}


    for(i = 0; i < 16; i++) {
    	if((char) ((packed_incoming[i] & 0xF0) >> 4) != hex_to_binary(expected_result[2*i]) ||
    	   (char) (packed_incoming[i] & 0xF) != hex_to_binary(expected_result[2*i + 1])) {
    	    xil_printf("Failed\n\r");

    	    for(j=0; j<16; j++) {
				xil_printf("%x%x", (packed_incoming[j] & 0xF0) >> 4, packed_incoming[j] & 0xF);
			}

			xil_printf("\n\r");


			for(j=0; j<16; j++) {
				xil_printf("%x%x", hex_to_binary(expected_result[2*j]), hex_to_binary(expected_result[2*j+1]));
			}

			xil_printf("\n\r");

    		errored = 1;
    		break;
    	}
    }


    if(errored==0) {
        xil_printf("Succeeded\n\r");
    }

    xil_printf("md5core took %d \n\r", timer_final_val-timer_init_val);

    return 0;
}