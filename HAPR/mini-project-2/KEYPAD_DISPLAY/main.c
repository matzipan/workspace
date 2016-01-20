#include "lpc17xx_uart.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"
#include "lpc_types.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//int key_map[5][5] = { { 'x','D', 'C', 'B', 'A' }, { 'x','#', '9', '6', '3' }, { 'x','0', '8', '5', '2' }, { 'x','*', '7', '4', '1' } };
int key_map[4][5] = { { 0b11111000, 0b11000100, 0b11000011, 0b11000010 ,0b11000001 }, 
						{ 0b11111000, 0b10100011, 0b10111001, 0b10110110, 0b10110011}, 
						{ 0b11111000, 0b10110000, 0b10111000, 0b10110101, 0b10110010}, 
						{ 0b11111000, 0b10101010, 0b10110111, 0b10110100, 0b10110001 } };

int read_usb_serial_none_blocking(char *buf,int length)
{
	return(UART_Receive((LPC_UART_TypeDef *)LPC_UART0, (uint8_t *)buf, length, NONE_BLOCKING));
}

int write_usb_serial_blocking(char *buf,int length)
{
	return(UART_Send((LPC_UART_TypeDef *)LPC_UART0,(uint8_t *)buf,length, BLOCKING));
}

void serial_init()
{
	UART_CFG_Type 		UARTConfigStruct;	// UART Configuration structure variable
	UART_FIFO_CFG_Type 	UARTFIFOConfigStruct;	// UART FIFO configuration Struct variable
	PINSEL_CFG_Type 	PinCfg;			// Pin configuration for UART

	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 2;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 3;
	PINSEL_ConfigPin(&PinCfg);

	UARTConfigStruct.Baud_rate = 9600;
	UARTConfigStruct.Databits = 8;
	UARTConfigStruct.Stopbits = 1;
	UARTConfigStruct.Parity = UART_PARITY_NONE;

	UART_ConfigStructInit(&UARTConfigStruct);

	UARTFIFOConfigStruct.FIFO_DMAMode = DISABLE;
	UARTFIFOConfigStruct.FIFO_Level	= UART_FIFO_TRGLEV0;
	UARTFIFOConfigStruct.FIFO_ResetRxBuf = ENABLE;
	UARTFIFOConfigStruct.FIFO_ResetTxBuf = ENABLE;

	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

	UART_Init((LPC_UART_TypeDef *)LPC_UART0, &UARTConfigStruct);

	UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART0, &UARTFIFOConfigStruct);

	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0, ENABLE);
}

void i2c_init() {
	PINSEL_CFG_Type 	PinCfg;

	PinCfg.Funcnum = 3;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;

	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 1;
	PINSEL_ConfigPin(&PinCfg);

	uint32_t clockrate = 100000;

	I2C_Init(LPC_I2C1, clockrate);

	I2C_Cmd(LPC_I2C1, ENABLE);
	I2C_IntCmd(LPC_I2C1, DISABLE);
}


void i2c_send(uint32_t slave, uint8_t* tx_data_buf, uint32_t tx_buf_length, uint8_t* rx_data_buf, uint32_t rx_buf_length, uint32_t* status) {
	char* s = malloc(32 * sizeof(char));
	int i;

	sprintf(s, "\n\rSending: ");
	write_usb_serial_blocking((char*)s,strlen((char*)s));

 	for(i=0; i<tx_buf_length; i++) {
		sprintf(s, "%x", tx_data_buf[i]);
		write_usb_serial_blocking((char*)s,strlen((char*)s));
 	}

 	I2C_M_SETUP_Type MSetupCfg;

 	MSetupCfg.sl_addr7bit = slave;
 	MSetupCfg.tx_data = tx_data_buf;
 	MSetupCfg.tx_length = tx_buf_length;
 	MSetupCfg.rx_data = rx_data_buf;
 	MSetupCfg.rx_length = rx_buf_length;
 	MSetupCfg.retransmissions_max = 3;
 
 	*status = I2C_MasterTransferData(LPC_I2C1, &MSetupCfg, I2C_TRANSFER_POLLING);

 	sprintf(s, " Recieved: ");
	write_usb_serial_blocking((char*)s,strlen((char*)s));


 	for(i=0; i<rx_buf_length; i++) {
		sprintf(s, "%x", rx_data_buf[i]);
		write_usb_serial_blocking((char*)s,strlen((char*)s));
 	}

	sprintf(s, " Status : %d", (int)*status);
	write_usb_serial_blocking((char*)s,strlen((char*)s));

	free(s);
}

int send_lcd_packet(uint8_t* tx_data_buf, uint32_t tx_length, uint8_t* rx_data_buf, uint32_t rx_length, uint32_t* status) {
	uint32_t slave_address=0x3B;

	i2c_send(slave_address,tx_data_buf,tx_length,rx_data_buf,rx_length,status);

	return *status;
}


void lcd_init() {
	uint32_t rx_length = 2;
	uint8_t* rx_buf = malloc(rx_length*sizeof(uint8_t));

	uint32_t* status = malloc(sizeof(uint32_t));

	uint32_t tx_length = 12;
	uint8_t* tx_buf = malloc(tx_length*sizeof(uint8_t));

    tx_buf[0] = 0x00; // Control byte for Instruction
    tx_buf[1] = 0x34; // DL: 8 bits, M:  16 by two line  display, SL: 1:18, H: normal instruction set
    tx_buf[2] = 0x0C; // D: Display on, C: curser off, B: blink off
    tx_buf[3] = 0x06; // I/D: increment, S: no shift
    tx_buf[4] = 0x35; // DL: 8 bits, M: 16 by two line, SL: 1:18, H: extended instruction set
    tx_buf[5] = 0x04; // P: left to right, Q: top to bottom
    tx_buf[6] = 0x10; // TC1: 0, TC2: 0
    tx_buf[7] = 0x42; // HV Stages 3
    tx_buf[8] = 0x9f; // set Vlcd, store to VA
    tx_buf[9] = 0x34; // DL: 8 bits, M:  two line, SL: 1:18, H: normal instruction set
    tx_buf[10] = 0x80; // DDRAM Address set to 00hex
    tx_buf[11] = 0x02; // return home
    send_lcd_packet(tx_buf,tx_length,rx_buf,rx_length,status);

    free(tx_buf);
	free(rx_buf);

	int i=0;
	while(i<100000) {
		i++;
	}
}

int send_keypad_packet(uint8_t* tx_data_buf, uint32_t tx_length, uint8_t* rx_data_buf, uint32_t rx_length, uint32_t* status) {
	uint32_t slave_address=0x21;

	i2c_send(slave_address,tx_data_buf,tx_length,rx_data_buf,rx_length,status);

	int i=0;
	while(i<1000) {
		i++;
	}

	return *status;
}

int send_keypad_key_read(uint8_t* tx_data_buf, uint32_t tx_length, uint8_t* rx_data_buf, uint32_t rx_length, uint32_t* status) {
	*tx_data_buf = ~(*tx_data_buf) | 0x0F;

	send_keypad_packet(tx_data_buf,tx_length, rx_data_buf, rx_length, status);

	*rx_data_buf = ~((*rx_data_buf) & 0x0F);

	char* s = malloc(32 * sizeof(char));

	sprintf(s, " Keypad : %x", rx_data_buf[0]);
	write_usb_serial_blocking((char*)s,strlen((char*)s));

	free(s);

	*tx_data_buf = ~(*tx_data_buf & 0xF0);

	return *status;
}

void lcd_clear() {
	uint32_t rx_length = 2;
	uint8_t* rx_buf = malloc(rx_length*sizeof(uint8_t));

	uint32_t* status = malloc(sizeof(uint32_t));

	uint32_t tx_length = 2;
	uint8_t* tx_buf = malloc(tx_length*sizeof(uint8_t));
	

	tx_buf[0] = 0x00;
	tx_buf[1] = 0x01;

	send_lcd_packet(tx_buf,tx_length,rx_buf,rx_length,status);

	free(rx_buf);
	free(status);
	free(tx_buf);

	int i =0;
	while(i<10000) {
		i++;
	}
}

void lcd_send_char(char character) {
	uint32_t rx_length = 2;
	uint8_t* rx_buf = malloc(rx_length*sizeof(uint8_t));

	uint32_t* status = malloc(sizeof(uint32_t));

	uint32_t tx_length = 2;
	uint8_t* tx_buf = malloc(tx_length*sizeof(uint8_t));

	tx_buf[0] = 0x40;
	tx_buf[1] = character;

	send_lcd_packet(tx_buf,tx_length,rx_buf,rx_length,status);

	free(rx_buf);
	free(status);
	free(tx_buf);
}

void lcd_send_first_char(char character) {
	uint32_t rx_length = 2;
	uint8_t* rx_buf = malloc(rx_length*sizeof(uint8_t));

	uint32_t* status = malloc(sizeof(uint32_t));

	uint32_t tx_length = 2;
	uint8_t* tx_buf = malloc(tx_length*sizeof(uint8_t));

	tx_buf[0] = 0x00;
	tx_buf[1] = 0x02;

	send_lcd_packet(tx_buf,tx_length,rx_buf,rx_length,status);

	free(rx_buf);
	free(status);
	free(tx_buf);

	lcd_send_char(character);
}

void main(void)
{
	char* s = malloc(32 * sizeof(char));

	serial_init();
	write_usb_serial_blocking("Hello World\n\r", 14);

	i2c_init();

	write_usb_serial_blocking("I2C Init\n\r", 11);

	lcd_init();
	lcd_clear();

	write_usb_serial_blocking("LCD Init\n\r", 11);

	uint32_t* status = malloc(sizeof(uint32_t));
 
	uint32_t tx_length = 1;
	uint8_t* tx_buf = malloc(tx_length*sizeof(uint8_t));

	uint32_t rx_length = 1;
	uint8_t* rx_buf = malloc(rx_length*sizeof(uint8_t));
	*rx_buf = 0x00;

	int key_row, key_column;

	while(1) {
		*tx_buf = 0x10;
		key_column= 0;

		while(1) {
			*tx_buf = (*tx_buf)|0x0F;

			send_keypad_key_read(tx_buf,tx_length,rx_buf,rx_length,status);

			key_row=0;

			if(((*rx_buf) & 0x0F) != 0) {
				*rx_buf = (*rx_buf) & 0x0F;

				key_row++;
				*rx_buf = (*rx_buf) >> 1;

				while (*rx_buf) { 
					key_row++;
					*rx_buf = (*rx_buf) >> 1;
				}
			}

			sprintf(s, " Key indices: %d, %d, %c", key_column, key_row,key_map[key_column][key_row]);
			write_usb_serial_blocking((char*)s,strlen((char*)s));

			if(key_row > 0) {
				lcd_send_first_char(key_map[key_column][key_row]);
			}


			if((*tx_buf) == 0x8F) {
				break;
			} else { 
				*tx_buf = ((*tx_buf)&0xF0)<<1;
				key_column++;
			}
			
		}
	}

	free(s);
}