#include "toplevel.h"

u8 wp_sequence_small[] = { 2, 0, 7, 2, 2, 3, 6, 5 };

u8 wall_sequence_small[] = { 0, 8, 0, 1, 5, 3, 1, 3, 9, 4, 1, 2, 3, 2, 0, 4, 4,
		5, 1, 4, 3, 8, 1, 1 };

void testcase_small() {
	hls::stream<u32> to_hw, from_hw;
	u32 value;

	to_hw.write(0x0A); // width
	to_hw.write(0x0A); // height
	to_hw.write(0x04); // number of waypoints
	to_hw.write(0); // don't ignore walls

	for (int i = 0; i < 4; i++) {
		to_hw.write(wp_sequence_small[2 * i]);
		to_hw.write(wp_sequence_small[2 * i + 1]);
	}

	for (int i = 0; i < 8; i++) {
		to_hw.write(0);
		to_hw.write(0);
	}

	for (int i = 0; i < 6; i++) {
		to_hw.write(wall_sequence_small[4 * i]);
		to_hw.write(wall_sequence_small[4 * i + 1]);
		to_hw.write(wall_sequence_small[4 * i + 2]);
		to_hw.write(wall_sequence_small[4 * i + 3]);
	}

	for (int i = 0; i < 54; i++) {
		to_hw.write(0);
		to_hw.write(0);
		to_hw.write(0);
		to_hw.write(0);
	}

	toplevel(to_hw, from_hw);

	for (int t = 0; t < 4; t++) {
		from_hw.read();
		from_hw.read();

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				printf("%3d ", (uint) from_hw.read());

			}
			printf("\n");
		}
		printf("\n");

	}

	for (int t = 0; t < 4; t++) {
		for (int i = 0; i < 4; i++) {
			printf("%3d", (uint) from_hw.read());
		}
		printf("\n");

	}

	value = from_hw.read();

	printf("Small result: %d (correct 26)\nRoute: ", (uint) value);

	for (int i = 0; i < 4; i++) {
		printf("%3d ", (uint) from_hw.read());
	}
	printf("\n");
	fflush(stdout);
}

u8 wp_sequence_big1[] = { 26, 14, 30, 4, 57, 53, 1, 48, 8, 48, 7, 39, 15, 42,
		50, 37, 19, 11, 13, 57, 9, 8, 53, 36 };

u8 wall_sequence_big1[] = { 38, 35, 1, 6, 1, 29, 1, 16, 42, 7, 0, 8, 51, 49, 0,
		15, 58, 1, 0, 3, 16, 0, 1, 15, 44, 3, 1, 2, 10, 2, 1, 15, 10, 6, 0, 16,
		13, 24, 0, 15, 3, 41, 0, 15, 6, 49, 1, 3, 46, 16, 0, 18, 34, 35, 0, 14,
		36, 42, 0, 18, 57, 14, 0, 7, 24, 2, 0, 9, 1, 39, 1, 3, 54, 9, 0, 17, 58,
		38, 1, 2 };

void testcase_big1() {
	hls::stream<u32> to_hw, from_hw;
	u32 value;

	to_hw.write(60); // width
	to_hw.write(60); // height
	to_hw.write(12); // number of waypoints
	to_hw.write(0); // don't ignore walls

	for (int i = 0; i < 12; i++) {
		to_hw.write(wp_sequence_big1[2 * i]);
		to_hw.write(wp_sequence_big1[2 * i + 1]);
	}

	for (int i = 0; i < 8; i++) {
		to_hw.write(0);
		to_hw.write(0);
	}

	for (int i = 0; i < 20; i++) {
		to_hw.write(wall_sequence_big1[4 * i]);
		to_hw.write(wall_sequence_big1[4 * i + 1]);
		to_hw.write(wall_sequence_big1[4 * i + 2]);
		to_hw.write(wall_sequence_big1[4 * i + 3]);
	}

	for (int i = 0; i < 40; i++) {
		to_hw.write(0);
		to_hw.write(0);
		to_hw.write(0);
		to_hw.write(0);
	}

	toplevel(to_hw, from_hw);

	for (int t = 0; t < 12; t++) {
		from_hw.read();
		from_hw.read();

		for (int i = 0; i < 60; i++) {
			for (int j = 0; j < 60; j++) {
				printf("%3d ", (int) from_hw.read());

			}
			printf("\n");
		}

		printf("\n");
		printf("\n");
	}
	printf("\n");
	printf("\n");

	for (int t = 0; t < 12; t++) {
		for (int i = 0; i < 12; i++) {
			printf("%3d ", (uint) from_hw.read());
		}
		printf("\n");

	}

	value = from_hw.read();

	printf("Big result 1: %d (correct 268)\nRoute: ", (uint) value);

	for (int i = 0; i < 12; i++) {
		printf("%3d ", (uint) from_hw.read());
	}
	printf("\n");
}

u8 wp_sequence_big2[] = { 21, 31, 24, 54, 25, 25, 12, 47, 36, 50, 28, 35, 38,
		29, 28, 20, 34, 4, 23, 40, 19, 6, 16, 16 };

u8 wall_sequence_big2[] = { 12, 26, 1, 5, 22, 42, 0, 7, 57, 16, 0, 17, 19, 35,
		1, 1, 40, 15, 1, 12, 23, 37, 0, 16, 57, 4, 1, 15, 4, 54, 1, 4, 21, 53,
		0, 19, 41, 59, 0, 17, 50, 50, 1, 2, 6, 39, 1, 11, 0, 22, 0, 13, 58, 29,
		1, 18, 39, 29, 1, 4, 15, 14, 1, 8, 49, 53, 0, 10, 21, 4, 0, 13, 7, 1, 0,
		14, 44, 36, 1, 14 };

void testcase_big2() {
	hls::stream<u32> to_hw, from_hw;
	u32 value;

	to_hw.write(60); // width
	to_hw.write(60); // height
	to_hw.write(12); // number of waypoints
	to_hw.write(0); // don't ignore walls

	for (int i = 0; i < 12; i++) {
		to_hw.write(wp_sequence_big2[2 * i]);
		to_hw.write(wp_sequence_big2[2 * i + 1]);
	}

	for (int i = 0; i < 8; i++) {
		to_hw.write(0);
		to_hw.write(0);
	}

	for (int i = 0; i < 20; i++) {
		to_hw.write(wall_sequence_big2[4 * i]);
		to_hw.write(wall_sequence_big2[4 * i + 1]);
		to_hw.write(wall_sequence_big2[4 * i + 2]);
		to_hw.write(wall_sequence_big2[4 * i + 3]);
	}

	for (int i = 0; i < 40; i++) {
		to_hw.write(0);
		to_hw.write(0);
		to_hw.write(0);
		to_hw.write(0);
	}

	toplevel(to_hw, from_hw);

	for (int t = 0; t < 12; t++) {
		from_hw.read();
		from_hw.read();

		for (int i = 0; i < 60; i++) {
			for (int j = 0; j < 60; j++) {
				from_hw.read();

			}
		}
	}

	for (int t = 0; t < 12; t++) {
		for (int i = 0; i < 12; i++) {
			printf("%3d", (uint) from_hw.read());
		}
		printf("\n");

	}

	value = from_hw.read();

	printf("Big result 2: %d (correct 202)\nRoute: ", (uint) value);

	for (int i = 0; i < 12; i++) {
		printf("%3d ", (uint) from_hw.read());
	}
	printf("\n");
}

int main() {
	testcase_small();
	//testcase_big1();
	//	 testcase_big2();

	return 0;
}
