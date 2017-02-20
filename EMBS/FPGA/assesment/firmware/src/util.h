#include "xbasic_types.h"
#include "xuartlite_l.h"
#include "xparameters.h"

#ifndef UTIL_H_
#define UTIL_H_


u8 hex_to_binary(char hex_char);

u32 get_world_id_parameter();
u8 get_world_size_parameter();
u8 get_ignores_walls_parameter();

struct waypoint {
	u8 x;
	u8 y;
};

struct pos {
	u8 x;
	u8 y;
	u8 length;
};

struct wall {
	u8 x;
	u8 y;
	u8 direction;
	u8 length;
};

#define WALL_DIRECTION_HORIZONTAL 0
#define WALL_DIRECTION_VERTICAL 1

#define WORLD_SIZE_SMALL 0
#define WORLD_SIZE_MEDIUM 1
#define WORLD_SIZE_LARGE 2

#define RESPONSE_CORRECT 0
#define RESPONSE_TOO_LONG 1
#define RESPONSE_TOO_SHORT 2

#pragma  pack(push, 1)

struct world_state {
	u32 world_id;
	u8 size;
	u8 width;
	u8 height;
	u8 waypoints_count;
	struct waypoint waypoints[12];

	u8 walls_count;
	struct wall walls[20];

	// stores the world distance matricx for each of the 12 waypoints
	char paths[12][60][60];
	
	// stores the final shortest length route
	u8 route[12];
	// length of shortest route
	u32 shortest_path;

	u8 ignores_walls;
	u8 response;
};

void write_response(struct world_state* state);

struct pos new_path(struct world_state* state, struct pos current, int destination, int cursor);

int path_available(struct world_state* state, struct pos current, int destination, int cursor);

#endif
