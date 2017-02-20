#include "draw.h"
#include "bitmap_font.h"

extern u8 distances[12][12];

// draws a character from the bitmap font from the bitmap_font.h file
void inline draw_character(unsigned int x, unsigned int y, char character, u8 colour) {
	int i,j;
	char *map = bitmap_font[character];

	for(j = 0; j < BITMAP_WIDTH; j++) {
		char current_column = map[j];

		for(i = 0; i < BITMAP_HEIGHT; i++) {
			if((current_column >> (i)) & 1) {
				vga_set_pixel(x + i, y + j, colour);
			}
		}
	}
}

// reconstructs the path given a start waypoint and a destination waypoint
int draw_path(struct world_state* state, int square_width, int square_height, int source, int destination, struct pos current) {
	int cursor;

	const int dot_size = (square_width % 2 == 0) ? 2 : 3;

	if(current.x == state->waypoints[source].x && current.y == state->waypoints[source].y) {
		return 1;
	}

	cursor = 0;

	while (path_available(state, current, source, cursor)) {
		struct pos new = new_path(state, current, source, cursor);

		int ret = draw_path(state, square_width, square_height, source, destination, new);

		if(ret == 1) {
			vga_draw_rect(square_width * current.x + square_width / 2 - 1,
									square_height * current.y + square_height / 2 - 1,
									dot_size, dot_size, VGA_YELLOW, VGA_FILL_SOLID);

			return 1;
		} else {
			cursor++;
		}
	}

	return -1;
}

void inline draw_world(struct world_state* state) {
	int i, j;

	vga_clear_screen();

	int square_width = VGA_WIDTH/state->width;
	int square_height = VGA_HEIGHT/state->height;

	for(i = 0; i < state->waypoints_count; i++) {
		draw_character(state->waypoints[i].x * square_width + square_width/2 - 4, state->waypoints[i].y * square_height + square_height/2 -4, i%10, i == 0 ? VGA_GREEN : VGA_RED);
	}

	for(i = 0; i < state->walls_count; i++) {
		int x = state->walls[i].x * square_width;
		int y = state->walls[i].y * square_height;

		for(j = 0; j < state->walls[i].length; j++) {
			if (state->walls[i].direction == WALL_DIRECTION_HORIZONTAL) {
				if(state->walls[i].x + j >= state->width) {
					break;
				}
				
				x = state->walls[i].x * square_width + j * square_width;
			} else {
				if(state->walls[i].y + j >= state->height) {
					break;
				}
				
				y = state->walls[i].y * square_height + j * square_height;
			}

			vga_draw_rect(x , y, square_width, square_height, VGA_MAGENTA, VGA_FILL_CHEQUERS);
		}
	}

	vga_set_pixel(0, 0, VGA_CYAN);

	for(i = 0; i < state->width; i++) {
		vga_set_pixel(square_width * (i + 1) -1, 0, VGA_CYAN);
		
		draw_character(i * square_width, 1, i%10, VGA_WHITE);

		for(j = 0; j < state->height; j++) {
			if(i == 0) {
				vga_set_pixel(0, square_height * (j + 1) -1, VGA_CYAN);
			}

			if(j != 0) {
				draw_character(1, j * square_height, j%10 , VGA_WHITE);
			}

			vga_set_pixel(square_width * (i + 1) -1, square_height * (j + 1) -1, VGA_CYAN);
		}
	}

}


void inline draw_solution(struct world_state* state) {
	int i, j;

	int square_width = VGA_WIDTH/state->width;
	int square_height = VGA_HEIGHT/state->height;

	for(i = 0; i < state->waypoints_count - 1; i++) {
		int source = state->route[i];
		int destination = state->route[i+1];
		struct pos first = { state->waypoints[destination].x, state->waypoints[destination].y, 0 };

		draw_path(state, square_width, square_height, source, destination, first);
	}

	int source = state->route[state->waypoints_count - 1];
	int destination = state->route[0];
	struct pos first = { state->waypoints[0].x, state->waypoints[0].y, 0 };

	draw_path(state, square_width, square_height, source, destination, first);
}


