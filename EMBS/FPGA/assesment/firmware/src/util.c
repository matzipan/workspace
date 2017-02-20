#include "util.h"


// for some reason things would start to break if I would add this to the state struct
u8 distances[12][12];

u32 get_world_id_parameter() {
	u32 number = 0;
	char character;
	u8 count = 5;
	u32 pow = 10000;

	outer_loop: xil_printf("\n\rEnter a world id (0 padded, decimal, 0 to 99999, default=0):\r\n");
		
	while(count > 0) {
		character = XUartLite_RecvByte(XPAR_RS232_DTE_BASEADDR);

		if(character == 13) { //enter key, return default
			return 0;
		}

		if(character >= '0' && character <= '9') {
			XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, character);
			 number += (character - '0') * pow;

			 count--;
			 pow /= 10;
		} else {
			xil_printf("Invalid input. Please try again.\n\r");
			number = 0;
			pow = 10000;
			count = 5;
			goto outer_loop;
		}
	}

	XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\n');
	XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\r');

	return number;
}

u8 get_world_size_parameter() {
	char character = 0;
	
	while(1) {
		xil_printf("\n\rSelect the size of the world to request (0=small, 1=medium, 2=large, default=2):\r\n");
		character = XUartLite_RecvByte(XPAR_RS232_DTE_BASEADDR);
		
		if(character == 13) { //enter key, return default
			return 2;
		} 
		
		if(character == '0' || character == '1' || character == '2') {
			XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, character);
			XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\n');
			XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\r');
			return (u8) (character - '0');
		} else {
			xil_printf("Invalid input. Please try again.\n\r");
			continue;
		}
	}
	
}

u8 get_ignores_walls_parameter() {
	char character = 0;
	
	while(1) {
		xil_printf("\n\rDo you want to ignore walls? (0=don't ignore walls, 1=ignore walls, default=0):\r\n");
		character = XUartLite_RecvByte(XPAR_RS232_DTE_BASEADDR);
		
		if(character == 13) { //enter key, return default
			return 0;
		} 
		
		if(character == '0' || character == '1') {
			XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, character);
			XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\n');
			XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\r');
			return (u8) (character - '0');
		} else {
			xil_printf("Invalid input. Please try again.\n\r");
			continue;
		}
	}
}

void write_response(struct world_state* state) {
	if(state->response == 0) {
		xil_printf("Solution is CORRECT.\n\r");
	}

	if(state->response == 1) {
		xil_printf("Solution is TOO LONG.\n\r");
	}

	if(state->response == 2) {
		xil_printf("Solution is TOO SHORT.\n\r");
	}
}

u8 hex_to_binary(char hex_char) {
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

// this function indicates what is the next step to make when reconstructing the path
// the cursor parameter indicates how many of the options have been rolled back 
// they can be rolled back in case the next step indicated was a wall, for example
//
// for example, if West was taken, but a wall was found there, then it will roll back
// with a cursor value of 1, which will now make it go North. If this fails, then it
// will roll back with a cursor value of 2, which will make it go East etc...
// 
// it assumes there will always be at least one vlaid path available.
struct pos new_path(struct world_state* state, struct pos current, int source, int cursor) {
	int current_distance = state->paths[source][current.x][current.y];
	current.length++;

	if(current.x > 0 && state->paths[source][current.x - 1][current.y] == current_distance -1) {
		if(cursor == 0) {
			current.x = current.x-1;

			return current;
		} else {
			cursor--;
		}
	}

	if(current.y > 0 && state->paths[source][current.x][current.y -1] == current_distance -1) {
		if(cursor == 0) {
			current.y = current.y-1;

			return current;
		} else {
			cursor--;
		}
	}

	if(current.x < state->width - 1 && state->paths[source][current.x + 1][current.y] == current_distance -1) {
		if(cursor == 0) {
			current.x = current.x+1;

			return current;
		} else {
			cursor--;
		}
	}

	if(current.y < state->height - 1 && state->paths[source][current.x][current.y + 1] == current_distance -1) {
		if(cursor == 0) {
			current.y = current.y+1;

			return current;
		} else {
			// this should never happen

			cursor--;
		}
	}
}

// similar to new_path, except it only returns a boolean value to indicate whether there are still any steps to take
int path_available(struct world_state* state, struct pos current, int source, int cursor) {
	int current_distance = state->paths[source][current.x][current.y];

	if(current.x > 0 && state->paths[source][current.x - 1][current.y] == current_distance -1) {
		if(cursor == 0) {
			return 1;
		} else {
			cursor--;
		}
	}

	if(current.y > 0 && state->paths[source][current.x][current.y -1] == current_distance -1) {
		if(cursor == 0) {
			return 1;
		} else {
			cursor--;
		}
	}

	if(current.x < state->width - 1 && state->paths[source][current.x + 1][current.y] == current_distance -1) {
		if(cursor == 0) {
			return 1;
		} else {
			cursor--;
		}
	}

	if(current.y < state->height - 1 && state->paths[source][current.x][current.y + 1] == current_distance -1) {
		if(cursor == 0) {
			return 1;
		} else {
			cursor--;
		}
	}

	return 0;
}
