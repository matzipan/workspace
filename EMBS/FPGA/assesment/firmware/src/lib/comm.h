#include "xil_types.h"
#include "../util.h"

#ifndef COMM_H_
#define COMM_H_

void comm_set_reply_state_reference(struct world_state* state);

void comm_set_request_world_message(u8 * message_buffer, struct world_state* state);

int comm_get_reply_world_frame(u8* recv_buffer, int message_type);

void comm_set_solve_world_message(u8 * message_buffer, struct world_state* state);

int comm_get_solution_reply_frame(u8* recv_buffer, int message_type);

#endif
