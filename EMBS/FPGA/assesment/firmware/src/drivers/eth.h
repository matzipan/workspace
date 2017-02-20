#include "xparameters.h"
#include "xemaclite.h"
#include "xuartlite_l.h"

#ifndef ETH_H_
#define ETH_H_

static u8 eth_mac_address[] = {0x00, 0x11, 0x22, 0x33, 0x00, 0x03};
static u8 eth_destination_mac_address[] = {0x00, 0x11, 0x22, 0x44, 0x00, 0x50};

void eth_setup();

void eth_clear_recieve_buffer();

void eth_put_message_in_frame(u8* tmit_buffer, u8* message);
void eth_configure_frame(u8* tmit_buffer);

void eth_send_frame(u8 * tmit_buffer);

int eth_filter_recieved_frame(u8* recv_buffer, int message_type);
void eth_poll_for_frame(u8* recv_buffer, int message_type, int eth_process_recieved_frame(u8*, int));
int eth_print_recieved_frame(u8* recv_buffer, int message_type);

void eth_debug_frame(u8* buffer, int len);

void* eth_get_message_pos(u8* buffer);

#endif
