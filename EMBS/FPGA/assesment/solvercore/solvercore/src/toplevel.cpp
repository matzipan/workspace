#include "toplevel.h"

u8 waypoint_distances[12][12];
u8 waypoint_y[12];
u8 waypoint_x[12];

u6 world_width;
u6 world_height;
u4 waypoints_count;
i9 world[60][60];
u32 best_distance;
u4 best_route[12];
u4 current_route[12];
u1 ignore_walls;

u32 p(u8 x, u8 y, i9 distance) {
	u32 data = 0;

	data |= ((u32) x) << 24;
	data |= ((u32) y) << 16;
	data |= distance;

	return data;
}

u6 get_x(u32 value) {
	return ((u8) (value >> 24));
}

u6 get_y(u32 value) {
	return ((u8) (value >> 16));
}

i9 get_distance(u32 value) {
	return ((i9) value);
}

void calculate_distances(u4 current_waypoint) {
	hls::stream<u32> visit_queue;

	visit_queue.write(p(waypoint_x[current_waypoint], waypoint_y[current_waypoint], 0));

	lee_loop: while (!visit_queue.empty()) {
		u32 current_value = visit_queue.read();

		u8 current_x = get_x(current_value);
		u8 current_y = get_y(current_value);
		i9 current_distance = get_distance(current_value);
		i9 cell_value = world[current_x][current_y];

		if (cell_value == WORLD_WALL) {
			continue; // ignore walls
		}

		if (IS_WAYPOINT(cell_value) &&
				waypoint_distances[current_waypoint][WAYPOINT_INDEX(cell_value)] == 0 &&
				cell_value != WAYPOINT_ID(current_waypoint)) {
			waypoint_distances[current_waypoint][WAYPOINT_INDEX(cell_value)] = current_distance;
		}

		if (cell_value == 1 || IS_WAYPOINT(cell_value)) {
			if (current_x > 0) {
				visit_queue.write(p(current_x - 1, current_y, current_distance + 1));
			}

			if (current_y > 0) {
				visit_queue.write(p(current_x, current_y - 1, current_distance + 1));
			}

			if (current_x < world_width - 1) {
				visit_queue.write(p(current_x + 1, current_y, current_distance + 1));
			}

			if (current_y < world_height - 1) {
				visit_queue.write(p(current_x, current_y + 1, current_distance + 1));
			}

			if (cell_value != WAYPOINT_ID(current_waypoint)) {
				world[current_x][current_y] = current_distance+WORLD_EMPTY;
			}
		}
	}

	world[waypoint_x[current_waypoint]][waypoint_y[current_waypoint]] = WORLD_EMPTY;
}

void check_route() {
	u32 current_distance = 0;

	// this loop depends on distances[0][0] being 0
	summing_loop: for (u4 i = 0; i < 11; i++) {
		current_distance += waypoint_distances[current_route[i]][current_route[i + 1]];
	}

	if(waypoints_count == 12) {
		current_distance += waypoint_distances[current_route[waypoints_count - 1]][0];
	}

	if (current_distance < best_distance) {
		best_distance = current_distance;

		best_route_copy: for (u4 i = 0; i < 12; i++) {
			best_route[i] = current_route[i];
		}
	}
}

void permute() {

	// the summing loop depends on perm[i], where i>n being 0.
	for(u4 i = 0; i < 12; i++) {
		current_route[i] = 0;
	}
	permutation_init: for (u4 i = 0; i < waypoints_count; i++) {
		current_route[i] = i;
	}

	while (1) {
		if(current_route[1] < current_route[waypoints_count-1]) {
			check_route();
		}

		int k = -1;
		k_find: for (u4 i = 1; i < waypoints_count - 1; i++) {
			if (current_route[i] < current_route[i + 1]) {
				k = i;
			}
		}
		if (k == -1) {
			break;
		}

		u4 l;
		l_find: for (u4 i = k + 1; i < waypoints_count; i++) {
			if (current_route[k] < current_route[i]) {
				l = i;
			}
		}

		u4 aux = current_route[k];
		current_route[k] = current_route[l];
		current_route[l] = aux;

		reverse: for (u4 i = 0; i < (waypoints_count - (k + 1)) / 2; i++) {
			u4 aux = current_route[k + 1 + i];
			current_route[k + 1 + i] = current_route[waypoints_count - 1 - i];
			current_route[waypoints_count - 1 - i] = aux;
		}
	}
}

void toplevel(hls::stream<u32> &input, hls::stream<u32> &output) {
		world_width = input.read();
		world_height = input.read();
		waypoints_count = input.read();
		ignore_walls = input.read().range(0,0);

		world_init: for (u6 t = 0; t < 60; t++) {
			for (u6 j = 0; j < 60; j++) {
				world[t][j] = WORLD_EMPTY;
			}
		}

		waypoints_loop: for (u4 i = 0; i < 12; i++) {
			for(u6 j = 0; j < 12; j++) {
				waypoint_distances[i][j] = 0;
			}
			waypoint_x[i] = input.read().range(7,0);
			waypoint_y[i] = input.read().range(7,0);
		}

		walls_loop: for (u6 i = 0; i < 60; i++) {
			u8 x_coord = input.read().range(7,0);
			u8 y_coord = input.read().range(7,0);
			u1 orientation = input.read().range(0,0);
			u8 length = input.read().range(7,0);

			if(!ignore_walls) {
				walls_loop_inner: for (u6 t = 0; t < length; t++) {
					if (orientation == 0) { // horizontal
						if(x_coord + t > world_width) {
							break;
						}

						world[x_coord + t][y_coord] = WORLD_WALL;
					} else { // vertical
						if(y_coord + t > world_height) {
							break;
						}

						world[x_coord][y_coord + t] = WORLD_WALL;
					}
				}
			}
		}

		distance_calculation_loop: for (u4 i = 0; i < waypoints_count; i++) {
			map_reset: for (u6 t = 0; t < world_width; t++) {
				for (u6 j = 0; j < world_width; j++) {
					if (world[t][j] != WORLD_WALL) {
						world[t][j] = WORLD_EMPTY;
					}
				}
			}

			waypoint_reset: for (u4 t = 0; t < waypoints_count; t++) {
				world[waypoint_x[t]][waypoint_y[t]] = WAYPOINT_ID(t);
			}

			output.write(waypoint_x[i]);
			output.write(waypoint_y[i]);

			calculate_distances(i);

			map_output: for (u6 t = 0; t < world_width; t++) {
				map_output_inner: for (u6 j = 0; j < world_height; j++) {
					output.write(world[t][j]);
				}
			}
		}

		distance_output_loop: for (u4 i = 0; i < waypoints_count; i++) {
			distance_output_inner: for (u4 j = 0; j < waypoints_count; j++) {
				output.write(waypoint_distances[i][j]);
			}
		}

		best_distance = ~0;

		permute();

		output.write(best_distance);

		route_output_loop: for (u4 j = 0; j < waypoints_count; j++) {
			output.write(best_route[j]);
		}
}
