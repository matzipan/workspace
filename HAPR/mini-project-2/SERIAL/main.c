#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"
#include "lpc_types.h"

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

void main(void)
{
	serial_init();
	write_usb_serial_blocking("Hello World\n\r",14);
	while(1);
}