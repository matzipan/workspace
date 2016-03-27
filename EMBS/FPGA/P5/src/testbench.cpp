#include "toplevel.h"

int main() {
    hls::stream<uint32> to_hw, from_hw;

    int inputgrid[SIZE][SIZE] = {
            {1,0,0,0,0,0,0,0,1,0},
            {0,0,0,0,0,0,0,0,1,1},
            {0,0,0,0,0,0,0,0,0,0},
            {1,1,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,0,0,0,0,0},
            {0,0,0,1,1,1,0,0,0,0},
            {0,0,0,1,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,1,1,1,0}
    };

    int outputgrid[SIZE][SIZE];
    memset(outputgrid, 0, sizeof(int)*SIZE*SIZE);

    int expectedgrid[SIZE][SIZE] = {
    		{0,0,0,0,0,0,0,0,1,1},
			{0,0,0,0,0,0,0,0,1,1},
			{0,0,0,0,0,0,0,0,0,0},
			{1,1,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,0,0,0,0},
			{0,0,1,1,0,1,0,0,0,0},
			{0,0,0,1,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,1,0,0},
			{0,0,0,0,0,0,0,1,0,0}
    };

    for(int i = 0; i < SIZE; i++) {
    	uint value = 0;
    	for(int j=0; j<SIZE; j++) {
    		value |= inputgrid[i][j] << j;
    	}
    	to_hw.write(value);
    }

    toplevel(to_hw, from_hw);

    for(int i=0; i<SIZE; i++) {
		uint32 value = from_hw.read();

		for(int j=0; j<SIZE; j++) {
			outputgrid[i][j] = (value >> j) & 0x1;
		 }
	}

    for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			printf("%i ", outputgrid[i][j]);
		}
		printf("\n");
    }

    int failed = 0;
    for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			if(outputgrid[i][j] != expectedgrid[i][j]) {
				printf("Mismatch at %i, %i: expected %i, found %i\n", i, j, expectedgrid[i][j], outputgrid[i][j]);
				failed = 1;
			}
		}
    }

    if(failed == 0) {
    	printf("Everything succeeded\n");
    }

    return failed;
}
