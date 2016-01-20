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
 	I2C_M_SETUP_Type MSetupCfg;

 	MSetupCfg.sl_addr7bit = slave;
 	MSetupCfg.tx_data = tx_data_buf;
 	MSetupCfg.tx_length = tx_buf_length;
 	MSetupCfg.rx_data = rx_data_buf;
 	MSetupCfg.rx_length = rx_buf_length;
 	MSetupCfg.retransmissions_max = 1;
 
 	*status = I2C_MasterTransferData(LPC_I2C1, &MSetupCfg, I2C_TRANSFER_POLLING);

 	// *status = MSetupCfg.status;
}

void main(void)
{
	serial_init();
	write_usb_serial_blocking("Hello World\n\r", 14);

	i2c_init();

	write_usb_serial_blocking("I2C Init\n\r", 11);

	uint32_t slave_address=0;
	uint32_t tx_length = 1;
	uint8_t* tx_buf = malloc(tx_length*sizeof(uint8_t));
	*tx_buf = 0;
	uint32_t rx_length = 1;
	uint8_t* rx_buf = malloc(rx_length*sizeof(uint8_t));
	*rx_buf = 0;
	uint32_t* status = malloc(sizeof(uint32_t));
	int count = 0;

	char* s = malloc(32 * sizeof(char));


	while(slave_address < 128) {
		sprintf(s, "Attempting : %d \n\r", slave_address);
		write_usb_serial_blocking((char*)s,strlen((char*)s));
		
		i2c_send(slave_address,tx_buf,tx_length,rx_buf,rx_length,status);

		sprintf(s, "Status : %d \n\r", *status);
		write_usb_serial_blocking((char*)s,strlen((char*)s));
		
		if(*status == 1) { 
			count++;

			sprintf(s, "%d found! \n\r", slave_address);
			write_usb_serial_blocking((char*)s,strlen((char*)s));
		} else {
			sprintf(s, "%d not found! \n\r", slave_address);
			write_usb_serial_blocking((char*)s,strlen((char*)s));
		}

		slave_address++;
	}


	sprintf(s, "Device count: %d \n\r", count);

	write_usb_serial_blocking(s,strlen(s));

	while(1);
}