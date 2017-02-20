#include "comm.h"
#include "../drivers/eth.h"

struct world_state* comm_state_ref;

void comm_set_reply_state_reference(struct world_state* state) {
	comm_state_ref = state;
}

void comm_set_request_world_message(u8 * message_buffer, struct world_state* state) {
	message_buffer[0] = 0x01;
	message_buffer[1] = state->size;
	message_buffer[2] = (state->world_id >> 24) & 0xFF;
	message_buffer[3] = (state->world_id >> 16) & 0xFF;
	message_buffer[4] = (state->world_id >> 8) & 0xFF;
	message_buffer[5] = state->world_id & 0xFF;
}

// this function is passed as a parameter to the ethernet recieve loop to validate 
// a message, if this function returns -1, then the polling continues, if the
// message is valid, then it is processed and this function returns 1.
//
// returns -1 meaning the polling should continue
// returns 1 meaning the message has been processed
// message_type 1 - only messages to self
// message_type 2 - only broadcast
// message_type 3 - all messages
int comm_get_reply_world_frame(u8* recv_buffer, int message_type) {
	u8 i;
	if(eth_filter_recieved_frame(recv_buffer, message_type)) {
		return -1;
	}

	u8* message_buffer = eth_get_message_pos(recv_buffer);

	if(message_buffer[0] != 0x02) {
		return -1;
	}

	comm_state_ref->width = message_buffer[5];
	comm_state_ref->height = message_buffer[6];
	comm_state_ref->waypoints_count = message_buffer[7];

	for(i = 0; i < comm_state_ref->waypoints_count; i++) {
		comm_state_ref->waypoints[i].x = message_buffer[8 + i * 2];
		comm_state_ref->waypoints[i].y = message_buffer[8 + i * 2 + 1];
	}

	u8 walls_position = 8 + comm_state_ref->waypoints_count * 2;
	comm_state_ref->walls_count = message_buffer[walls_position];

	for(i = 0; i < comm_state_ref->walls_count; i++) {
		comm_state_ref->walls[i].x = message_buffer[walls_position + 1 + i * 4];
		comm_state_ref->walls[i].y = message_buffer[walls_position + 1 + i * 4 + 1];
		comm_state_ref->walls[i].direction = message_buffer[walls_position + 1 + i * 4 + 2];
		comm_state_ref->walls[i].length = message_buffer[walls_position + 1 + i * 4 + 3];
	}

	return 1;
}

// ignores_walls 0 if the solution does not cross walls, 1 if it ignores walls
void comm_set_solve_world_message(u8 * message_buffer, struct world_state* state) {
	message_buffer[0] = 0x03;
	message_buffer[1] = state->size;
	message_buffer[2] = (state->world_id >> 24) & 0xFF;
	message_buffer[3] = (state->world_id >> 16) & 0xFF;
	message_buffer[4] = (state->world_id >> 8) & 0xFF;
	message_buffer[5] = state->world_id & 0xFF;
	message_buffer[6] = state->ignores_walls;
	message_buffer[7] = (state->shortest_path >> 24) & 0xFF;
	message_buffer[8] = (state->shortest_path >> 16) & 0xFF;
	message_buffer[9] = (state->shortest_path >> 8) & 0xFF;
	message_buffer[10] = state->shortest_path & 0xFF;
}

// this function is passed as a parameter to the ethernet recieve loop to validate 
// a message, if this function returns -1, then the polling continues, if the
// message is valid, then it is processed and this function returns 1.
//
// returns -1 meaning the polling should continue
// returns 1 meaning the message has been processed
// message_type 1 - only messages to self
// message_type 2 - only broadcast
// message_type 3 - all messages
int comm_get_solution_reply_frame(u8* recv_buffer, int message_type) {
	if(eth_filter_recieved_frame(recv_buffer, message_type)) {
		return -1;
	}

	u8* message_buffer = eth_get_message_pos(recv_buffer);

	if(message_buffer[0] != 0x04) {
		return -1;
	}

	comm_state_ref->response = message_buffer[1];

	return 1;
}
