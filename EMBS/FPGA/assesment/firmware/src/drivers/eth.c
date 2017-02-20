#include "eth.h"

XEmacLite ether;

void eth_debug_frame(u8* buffer, int len) {
	int i;

	xil_printf("[DEBUG DESTINATION] %02x:%02x:%02x:%02x:%02x:%02x\n\r", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);
	xil_printf("[DEBUG SOURCE] %02x:%02x:%02x:%02x:%02x:%02x\n\r", buffer[6], buffer[7], buffer[8], buffer[9], buffer[10], buffer[11]);
	xil_printf("[DEBUG TYPE] %x %x\n\r", buffer[12], buffer[13]);

	int message_length = (buffer[14] << 8) | buffer[15];

	xil_printf("\n\r[DEBUG MESSAGE]\n\r");
	for(i = 14; i < len; i++) {
		xil_printf("%x ", buffer[i]);
		if((i-14) % 32 == 31) {
			xil_printf("\n\r");
		}
	}
	xil_printf("\n\r");
}

// checks whether an eth frame is broadcast
inline int eth_is_frame_broadcast(u8 recv_buffer[XEL_MAX_FRAME_SIZE]) {
	int i;

	for(i=0; i < 6; i++) {
		if(recv_buffer[i] != 0xFF) {
			return 0;
		}
		if(i == 5) {
			return 1;
		}
	}

	return 0;
}

// checks whether an eth frame has been sent to the address of this device
inline int eth_is_frame_for_self(u8 recv_buffer[XEL_MAX_FRAME_SIZE]) {
	int i;

	for(i=0; i < 6; i++) {
		if(recv_buffer[i] != eth_mac_address[i]) {
			return 0;
		}
		if(i == 5) {
			return 1;
		}
	}

	return 0;
}

void eth_poll_for_frame(u8 recv_buffer[XEL_MAX_FRAME_SIZE], int message_type, int eth_process_recieved_frame(u8*, int)) {
	//Poll for receive packet. recv_len must be defined as volatile
	volatile int recv_len = 0;
	while (recv_len == 0)  {
		recv_len = XEmacLite_Recv(&ether, recv_buffer);
		if(recv_len != 0 && eth_process_recieved_frame(recv_buffer, message_type) == 1) {
			break;
		} else {
			recv_len = 0;
		}
	}
}

// returns 1 means the message has been caught by the filter
// returns 0 means the message is good to be processed
int eth_filter_recieved_frame(u8 recv_buffer[XEL_MAX_FRAME_SIZE], int message_type) {
	if(recv_buffer[12] != 0x55 || recv_buffer[13] != 0xAB) {
		// this message is noise
		return 1;
	}

	if(eth_is_frame_for_self(recv_buffer)) {
		if(!(message_type&0x1)) {
			return 1;
		} else {
			// xil_printf("[RECEIVED] ");
		}
	} else if(eth_is_frame_broadcast(recv_buffer)) {
		if(!(message_type&0x2)) {
			return 1;
		} else {
			// xil_printf("[BROADCAST] ");
		}
	} else {
		// the message is noise
		return 1;
	}

	return 0;
}

// this function is passed as a parameter to the ethernet recieve loop to validate 
// a message, if this function returns -1, then the polling continues, if the
// message is valid, then it is processed and this function returns 1.
//
// it is overridden by functions in comm.c
//
// returns -1 meaning the polling should continue
// returns 1 meaning the message has been processed
// message_type 1 - only messages to self
// message_type 2 - only broadcast
// message_type 3 - all messages
int eth_print_recieved_frame(u8 recv_buffer[XEL_MAX_FRAME_SIZE], int message_type) {
	int i;

	if(eth_filter_recieved_frame(recv_buffer, message_type)) {
		return -1;
	}

	//We have a frame. Note that recv_len may be LONGER than the frame
	//that was sent. (Ethernet is weird, and that is why we need length
	//bytes in our protocols.)
	int message_length = (recv_buffer[14] << 8) | recv_buffer[15];
	for(i = 0; i < message_length; i++) {
		XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, recv_buffer[i+16]);
	}

	XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\n');
	XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\r');

	return 1;
}


void eth_configure_frame(u8 tmit_buffer[XEL_MAX_FRAME_SIZE]) {
	int i, current_pos = 0;

    //Write the destination MAC address
	for(i = 0; i < 6; i++)
		tmit_buffer[current_pos + i] = eth_destination_mac_address[i];

	current_pos += i;

    //Write the source MAC address
    for(i = 0; i < 6; i++)    // Set VGA core frame buffer location
    	tmit_buffer[current_pos + i] = eth_mac_address[i];

    current_pos += i;
    //Write the type field
    tmit_buffer[current_pos++] = 0x55;
    tmit_buffer[current_pos++] = 0xAB;
}

void* eth_get_message_pos(u8* buffer) {
	return buffer+14;
}

void eth_send_frame(u8 tmit_buffer[XEL_MAX_FRAME_SIZE]) {
    //Send the buffer
    //The size argument is the data bytes + XEL_HEADER_SIZE which is defined
    //as the size of the destination MAC plus the type/length field
    XEmacLite_Send(&ether, tmit_buffer, 11 + XEL_HEADER_SIZE);
}

void eth_setup() {
	//Initialise the driver
    XEmacLite_Config *etherconfig = XEmacLite_LookupConfig(XPAR_EMACLITE_0_DEVICE_ID);
    XEmacLite_CfgInitialize(&ether, etherconfig, etherconfig->BaseAddress);

    XEmacLite_SetMacAddress(&ether, eth_mac_address); //Set our sending MAC address
}

void eth_clear_recieve_buffer() {
	XEmacLite_FlushReceive(&ether);
}
