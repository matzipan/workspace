#include "lpc17xx_uart.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"
#include "lpc_types.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

	sprintf(s, "Sending : %x%x ", tx_data_buf[0], tx_data_buf[1]);
	write_usb_serial_blocking((char*)s,strlen((char*)s));

 	I2C_M_SETUP_Type MSetupCfg;

 	MSetupCfg.sl_addr7bit = slave;
 	MSetupCfg.tx_data = tx_data_buf;
 	MSetupCfg.tx_length = tx_buf_length;
 	MSetupCfg.rx_data = rx_data_buf;
 	MSetupCfg.rx_length = rx_buf_length;
 	MSetupCfg.retransmissions_max = 1;
 
 	*status = I2C_MasterTransferData(LPC_I2C1, &MSetupCfg, I2C_TRANSFER_POLLING);

	sprintf(s, "Recieved : %x%x ", rx_data_buf[0], rx_data_buf[1]);
	write_usb_serial_blocking((char*)s,strlen((char*)s));

	sprintf(s, "Status : %d \n\r", *status);
	write_usb_serial_blocking((char*)s,strlen((char*)s));

	free(s);
}

void send_lcd_packet(uint8_t* tx_data_buf, uint32_t tx_length, uint8_t* rx_data_buf, uint32_t rx_length, uint32_t* status) {
	uint32_t slave_address=0x3B;

	i2c_send(slave_address,tx_data_buf,tx_length,rx_data_buf,rx_length,status);

	int count = 0;
	while(count < 100000000) {
		count++;
	}

	return status;
}

void main(void)
{
	serial_init();
	write_usb_serial_blocking("Hello World\n\r", 14);

	i2c_init();

	write_usb_serial_blocking("I2C Init\n\r", 11);

	uint32_t rx_length = 2;
	uint8_t* rx_buf = malloc(rx_length*sizeof(uint8_t));
	*rx_buf = 0;

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

    tx_length = 2;
	tx_buf = malloc(tx_length*sizeof(uint8_t));

	// tx_buf[0] = 0x00;
	// tx_buf[1] = 0x20;
	// send_lcd_packet(tx_buf,tx_length,rx_buf,rx_length,status);

	// tx_buf[0] = 0x0E;
	// tx_buf[1] = 0x06;
	// send_lcd_packet(tx_buf,tx_length,rx_buf,rx_length,status);

	tx_buf[0] = 0x40;
	tx_buf[1] = 0x50;

	send_lcd_packet(tx_buf,tx_length,rx_buf,rx_length,status);

	/*send_lcd_packet(0x01);
	send_lcd_packet(0x00);
	send_lcd_packet(0x80);
	send_lcd_packet(0x40);
	send_lcd_packet(0x64);*/

	while(1);
}