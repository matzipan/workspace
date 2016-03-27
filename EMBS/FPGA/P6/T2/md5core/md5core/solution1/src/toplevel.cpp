#include "toplevel.h"

uint32 h0, h1, h2, h3, a, b, c, d, f, g, temp;
uint32 new_length, offset, initial_length;
uint32 w[16];
uint8 msg[320]; // 256 + 448/8 + 8

// Constants are the integer part of the sines of integers (in radians) * 2^32.
const uint32 k[64] = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
		0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,
		0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681,
		0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5,
		0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0,
		0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

// r specifies the per-round shift amounts
const uint8 r[] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
		5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
		21, 6, 10, 15, 21, 6, 10, 15, 21 };

uint32 inline left_rotate(uint32 x, uint32 c) {
	#pragma HLS INLINE

    return (x << c) | (x >> (32 - c));
}

void inline to_bytes_big_endian(uint32 val, uint8 *bytes) {
	#pragma HLS INLINE

    bytes[0] = (uint8) val;
    bytes[1] = (uint8) (val >> 8);
    bytes[2] = (uint8) (val >> 16);
    bytes[3] = (uint8) (val >> 24);
}

uint32 inline to_int32_big_endian(const uint8 *bytes) {
	#pragma HLS INLINE

    return (uint32) bytes[0]
        | ((uint32) bytes[1] << 8)
        | ((uint32) bytes[2] << 16)
        | ((uint32) bytes[3] << 24);
}

uint32 inline pack_little_endian(const uint8 *bytes) {
	#pragma HLS INLINE

	return ((uint32) bytes[0] << 24)
	        | ((uint32) bytes[1] << 16)
	        | ((uint32) bytes[2] << 8)
	        | (uint32) bytes[3];
}

uint32 inline big_endian_to_little_endian(uint32 val) {
	#pragma HLS INLINE

	return ((val & 0xFF) << 24)
		| ((val & 0xFF00) << 8)
		| ((val & 0xFF0000) >> 8)
		| ((val & 0xFF000000) >> 24);
}

//Top-level function
void toplevel(hls::stream<uint32> &input, hls::stream<uint32> &output) {
#pragma HLS ARRAY_PARTITION variable=msg cyclic factor=4 dim=1
#pragma HLS RESOURCE variable=input core=AXI4Stream
#pragma HLS RESOURCE variable=output core=AXI4Stream
#pragma HLS INTERFACE ap_ctrl_none port=return

	initial_length = 0;

    loop_read: for(int i = 0; i < 16; i++) {
		#pragma HLS PIPELINE

		uint32 byte_packet = input.read();

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
			msg[initial_length] = (byte_packet & 0xFF);
			initial_length++;
		}
	}

	// Initialize variables - simple count in nibbles:
	h0 = 0x67452301;
	h1 = 0xefcdab89;
	h2 = 0x98badcfe;
	h3 = 0x10325476;

	//Pre-processing:
	//append "1" bit to message
	//append "0" bits until message length in bits ≡ 448 (mod 512)
	//append length mod (2^64) to message

	loop_448: for (new_length = initial_length + 1; new_length % (512/8) != 448/8; new_length++) {
#pragma HLS LOOP_TRIPCOUNT min=300 max=300 avg=300

	}

	msg[initial_length] = 0x80; // append the "1" bit; most significant bit is "first"
	loop_zero: for (offset = initial_length + 1; offset < new_length; offset++) {
#pragma HLS LOOP_TRIPCOUNT min=448 max=448 avg=448
		msg[offset] = 0; // append "0" bits
	}

	// append the len in bits at the end of the buffer.
	to_bytes_big_endian(initial_length*8, msg + new_length);

	// initial_len>>29 == initial_len*8>>32, but avoids overflow.
	to_bytes_big_endian(initial_length>>29, msg + new_length + 4);

	// Process the message in successive 512-bit chunks:
	//for each 512-bit chunk of message:
	loop_md5: for(offset=0; offset<new_length; offset += (512/8)) {
#pragma HLS LOOP_TRIPCOUNT min=100 max=100 avg=100
		// break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
		loop_break_chunks: for (uint8 i = 0; i < 16; i++) {
			#pragma HLS UNROLL
			w[i] = to_int32_big_endian(msg + offset + i*4);
		}

		// Initialize hash value for this chunk:
		a = h0;
		b = h1;
		c = h2;
		d = h3;

		// Main loop:
		loop_main: for(uint8 i = 0; i<64; i++) {
#pragma HLS UNROLL factor=3

			if (i < 16) {
				f = (b & c) | ((~b) & d);
				g = i;
			} else if (i < 32) {
				f = (d & b) | ((~d) & c);
				g = (5*i + 1) % 16;
			} else if (i < 48) {
				f = b ^ c ^ d;
				g = (3*i + 5) % 16;
			} else {
				f = c ^ (b | (~d));
				g = (7*i) % 16;
			}

			temp = d;
			d = c;
			c = b;
			b = b + left_rotate((a + f + k[i] + w[g]), (uint32) r[i]);
			a = temp;

		}

		// Add this chunk's hash to result so far:
		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;

	}

	output.write(big_endian_to_little_endian(h0));
	output.write(big_endian_to_little_endian(h1));
	output.write(big_endian_to_little_endian(h2));
	output.write(big_endian_to_little_endian(h3));

}
