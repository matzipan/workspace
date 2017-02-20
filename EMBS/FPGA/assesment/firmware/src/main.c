#include <stdio.h>
#include "drivers/vga.h"
#include "drivers/eth.h"
#include "drivers/led.h"
#include "drivers/core.h"
#include "lib/comm.h"
#include "lib/draw.h"
#include "util.h"

struct world_state state;

u8 comm_buffer[XEL_MAX_FRAME_SIZE];

int main(void) {
#ifdef SHOW_LEDS
	led_clear_all();
#endif

	comm_set_reply_state_reference(&state);

	// this pointer indicates where the message starts in the read/write buffer
	u8* message_buffer = eth_get_message_pos(comm_buffer);

	vga_init();
	vga_clear_screen();
    vga_enable_output();

    eth_setup();

#ifdef SHOW_LEDS
	led_set_value(0,1);
#endif

    while(1) {
    	state.size = get_world_size_parameter();
		state.world_id = get_world_id_parameter();
		state.ignores_walls = get_ignores_walls_parameter();

		comm_set_request_world_message(message_buffer, &state);
		eth_configure_frame(comm_buffer);
		eth_clear_recieve_buffer();
		eth_send_frame(comm_buffer);
		eth_poll_for_frame(comm_buffer, 1, comm_get_reply_world_frame);

		send_to_core(&state);
		draw_world(&state);

		get_from_core(&state);
		draw_solution(&state);

		comm_set_solve_world_message(message_buffer, &state);
		eth_configure_frame(comm_buffer);
		eth_clear_recieve_buffer();
		eth_send_frame(comm_buffer);
		eth_poll_for_frame(comm_buffer, 1, comm_get_solution_reply_frame);
		write_response(&state);
    }

    return 0;
}
