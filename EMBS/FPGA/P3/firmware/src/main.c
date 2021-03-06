#include "xparameters.h"
#include "xemaclite.h"
#include "xuartlite_l.h"

XEmacLite ether;

static u8 eth_mac_address[] = {0x00, 0x11, 0x22, 0x33, 0x00, 0x03};
static u8 eth_destination_mac_address[] = {0x00, 0x11, 0x22, 0x33, 0x00, 0x00};

void eth_debug_frame(u8* buffer, int len) {
	int i;
	xil_printf("[DEBUG DESTINATION] %02x:%02x:%02x:%02x:%02x:%02x\n\r", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);
	xil_printf("[DEBUG SOURCE] %02x:%02x:%02x:%02x:%02x:%02x\n\r", buffer[6], buffer[7], buffer[8], buffer[9], buffer[10], buffer[11]);
	xil_printf("[DEBUG TYPE] %x %x\n\r", buffer[12], buffer[13]);

	int message_length = (buffer[14] << 8) | buffer[15];

	xil_printf("[DEBUG CRC] ");
	for(i = 16+message_length; i < 16+message_length+4; i++) {
		xil_printf("%02x ", buffer[i]);
	}
	xil_printf("\n\r[DEBUG MESSAGE] (%04x) ", message_length);
	for(i = 0; i < message_length; i++) {
		xil_printf("%c", buffer[i+16]);
	}
	xil_printf("\n\r");
}

inline int eth_is_frame_broadcast(u8* recv_buffer) {
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

inline int eth_is_frame_for_self(u8* recv_buffer) {
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

void eth_poll_for_frame(u8* recv_buffer, int message_type, int eth_process_recieved_frame(u8*, int)) {
	//Poll for receive packet. recv_len must be defined as volatile!
	volatile int recv_len = 0;
	while (recv_len == 0)  {
		recv_len = XEmacLite_Recv(&ether, recv_buffer);
		if(recv_len != 0 && eth_process_recieved_frame(recv_buffer, message_type) == 1) {
			break;
		}
	}
}

unsigned int eth_crc32(u8* recv_buffer) {
	// http://www.hackersdelight.org/hdcodetxt/crc.c.txt
	int i, j;
	unsigned int byte, crc, mask;

	i = 0;
	crc = 0xFFFFFFFF;
	while (recv_buffer[i] != 0) {
	  byte = recv_buffer[i];            // Get next byte.
	  crc = crc ^ byte;
	  for (j = 7; j >= 0; j--) {    // Do eight times.
	     mask = -(crc & 1);
	     crc = (crc >> 1) ^ (0xEDB88320 & mask);
	  }
	  i++;
	}
	return ~crc;
}

// returns -1 meaning the polling should continue
// message_type 1 - only messages to self
// message_type 2 - only broadcast
// message_type 3 - all messages
int eth_process_recieved_frame(u8* recv_buffer, int message_type) {
	int i;

	if(recv_buffer[12] != 0x55 || recv_buffer[13] != 0xAA) {
		// this message is noise
		return -1;
	}

	if(eth_is_frame_for_self(recv_buffer)) {
		if(!(message_type&0x1)) {
			return -1;
		} else {
			xil_printf("[RECEIVED] ");
		}
	} else if(eth_is_frame_broadcast(recv_buffer)) {
		if(!(message_type&0x2)) {
			return -1;
		} else {
			xil_printf("[BROADCAST] ");
		}
	} else {
		// the message is noise
		return -1;
	}

	if(eth_crc32(recv_buffer) != 0) {
		xil_printf("[CHECKSUM FAILED]\r\n");
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

void eth_configure_frame(u8* tmit_buffer) {
	int i;
    u8* buffer_position = tmit_buffer;

    //Write the destination MAC address
	for(i = 0; i < 6; i++)
        *buffer_position++ = eth_destination_mac_address[i];

    //Write the source MAC address
    for(i = 0; i < 6; i++)
        *buffer_position++ = eth_mac_address[i];

    //Write the type field
    *buffer_position++ = 0x55;
    *buffer_position++ = 0xAA;
}

void eth_put_message_in_frame(u8* tmit_buffer, u8* message) {
	int i = 0;
	while(*message) {
		tmit_buffer[i+16] = *message++;
		i++;
	}
	tmit_buffer[14] = (i >> 8) & 0xFF;
	tmit_buffer[15] = i & 0xFF;
}

void eth_send_frame(u8 * tmit_buffer) {
    //Send the buffer
    //The size argument is the data bytes + XEL_HEADER_SIZE which is defined
    //as the size of the destination MAC plus the type/length field
    XEmacLite_Send(&ether, tmit_buffer, 10 + XEL_HEADER_SIZE);
}

void eth_setup() {
	//Initialise the driver
    XEmacLite_Config *etherconfig = XEmacLite_LookupConfig(XPAR_EMACLITE_0_DEVICE_ID);
    XEmacLite_CfgInitialize(&ether, etherconfig, etherconfig->BaseAddress);

    XEmacLite_SetMacAddress(&ether, eth_mac_address); //Set our sending MAC address
}

void eth_clear_buffer() {
	XEmacLite_FlushReceive(&ether);
}

u8 ex_to_binary(char hex_char) {
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

int main() {
    // Buffers used for Transmission and Reception of Packets
    u8 * tmit_buffer = (u8*) XPAR_DDR_SDRAM_MPMC_BASEADDR;
	u8 * recv_buffer = (u8*) XPAR_DDR_SDRAM_MPMC_BASEADDR+XEL_MAX_FRAME_SIZE;
	u8 * message_buffer = (u8*) XPAR_DDR_SDRAM_MPMC_BASEADDR+2*XEL_MAX_FRAME_SIZE;
	char current_char;

    eth_setup();

    while(1) {
		xil_printf("\e[2J\e[2;1fEnter the last byte of the destination address %02x:%02x:%02x:%02x:%02x:XX\n\r(hex) ",
				eth_destination_mac_address[0],
				eth_destination_mac_address[1],
				eth_destination_mac_address[2],
				eth_destination_mac_address[3],
				eth_destination_mac_address[4]);

		xil_printf("\e[1m\e[s\e[1;1fNot setup\e[u\e[0m");

		current_char = XUartLite_RecvByte(XPAR_RS232_DTE_BASEADDR);
		XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, current_char);
		eth_destination_mac_address[5] = hex_to_binary(current_char) << 4;

		current_char = XUartLite_RecvByte(XPAR_RS232_DTE_BASEADDR);
		XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, current_char);
		eth_destination_mac_address[5] |= hex_to_binary(current_char);

		XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\n');
		XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\r');

		eth_configure_frame(tmit_buffer);

		while(1) {
			xil_printf("[MESSAGE] ");
			xil_printf("\e[1m\e[s\e[1;1f\e[2KCommunicating with %02x:%02x:%02x:%02x:%02x:%02x \e[u\e[0m",
					eth_destination_mac_address[0],
					eth_destination_mac_address[1],
					eth_destination_mac_address[2],
					eth_destination_mac_address[3],
					eth_destination_mac_address[4],
					eth_destination_mac_address[5]);

			int current_index = 0;
			while(1) {
				current_char = XUartLite_RecvByte(XPAR_RS232_DTE_BASEADDR);
				if(current_char == 0x0d) { // enter key
					message_buffer[current_index] = 0;
					XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\n');
					XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\r');

					break;
				} else {
					if(current_char == 0x7f) { // backspace key
						if(current_index > 0) {
							current_index--;
						}
					} else if(current_char == 0x03) {
						break;
					} else {
						message_buffer[current_index] = current_char;
						current_index++;
					}
					message_buffer[current_index] = 0;

					xil_printf("\e[2K\r[MESSAGE] %s", message_buffer);
				}
			}

			if(current_char == 0x03) {
				break;
			}

			eth_put_message_in_frame(tmit_buffer, message_buffer);
			eth_clear_buffer();
			eth_send_frame(tmit_buffer);
			eth_poll_for_frame(recv_buffer, 1, eth_process_recieved_frame);
		}
    }

    return 0;
}
