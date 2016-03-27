#include "toplevel.h"

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


int main() {
    hls::stream<uint32> to_hw, from_hw;

    //Write input data
    to_hw.write(0x626C6100);
    to_hw.write(0x0);
    to_hw.write(0x0);
    to_hw.write(0x0);
	to_hw.write(0x0);
	to_hw.write(0x0);
	to_hw.write(0x0);
	to_hw.write(0x0);
	to_hw.write(0x0);
	to_hw.write(0x0);
	to_hw.write(0x0);
	to_hw.write(0x0);
	to_hw.write(0x0);
	to_hw.write(0x0);
	to_hw.write(0x0);
	to_hw.write(0x0);

    //Run the hardware
    toplevel(to_hw, from_hw);

    //Read and report the output

    char expected_result[] = "128ecf542a35ac5270a87dc740918404";
	uint initial_length = 0;
	uint msg[16];

    for(int i = 0; i < 4; i++) {
		uint32 byte_packet = from_hw.read();

		if(0xFF000000 & byte_packet) {
			msg[initial_length] = (byte_packet & 0xFF000000) >> 24;
			initial_length++;
		}

		if(0xFF0000 & byte_packet) {
			msg[initial_length] = (byte_packet & 0xFF0000) >> 16;
			initial_length++;
		}

		if(0xFF00 & byte_packet) {
			msg[initial_length] = (byte_packet & 0xFF00) >> 8;
			initial_length++;
		}
		if(0xFF & byte_packet) {
			msg[initial_length] = byte_packet & 0xFF;
			initial_length++;
		}
	}

    for(int i=0; i<16; i++) {
    	if((char) ((msg[i] & 0xF0) >> 4) != hex_to_binary(expected_result[2*i]) ||
    	   (char) (msg[i] & 0xF) != hex_to_binary(expected_result[2*i + 1])) {
    	    printf("Failed\n");

    	    for(int i=0; i<16; i++) {
				printf("%x%x", (msg[i] & 0xF0) >> 4, msg[i] & 0xF);
			}

			printf("\n");


			for(int i=0; i<16; i++) {
				printf("%x%x", hex_to_binary(expected_result[2*i]), hex_to_binary(expected_result[2*i+1]));
			}

    		return 1;
    	}
    }

    printf("Succeeded\n");
    return 0;
}
