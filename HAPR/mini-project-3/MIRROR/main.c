#include "LPC17xx.h"
#include "lpc_types.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_timer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

void dac_init() {
	PINSEL_CFG_Type 	PinCfg;			// Pin configuration for UART

	PinCfg.Funcnum = 2;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 26;
	PINSEL_ConfigPin(&PinCfg);

	DAC_Init(LPC_DAC);
}


void adc_init (){
	PINSEL_CFG_Type 	PinCfg;

	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;

	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 23;
	PINSEL_ConfigPin(&PinCfg);

	uint32_t clockrate = 200000;

	ADC_Init(LPC_ADC, clockrate);
	ADC_BurstCmd (LPC_ADC, DISABLE);

	ADC_IntConfig(LPC_ADC, ADC_ADINTEN0, SET);

   	ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_0, ENABLE);

}

void adc_trigger_sample() {
  	NVIC_EnableIRQ(ADC_IRQn);
	ADC_StartCmd (LPC_ADC, ADC_START_NOW);
}

void ADC_IRQHandler ()
{
  	NVIC_DisableIRQ(ADC_IRQn);



	if(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_0,ADC_DATA_DONE) == SET) {
  		DAC_UpdateValue(LPC_DAC,ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_0)>>2);

  		adc_trigger_sample();
		return; 
	}

}



void main(void)
{
	serial_init();
	write_usb_serial_blocking("Hello World\n\r", 14);

	dac_init();
	write_usb_serial_blocking("DAC Init\n\r", 11);

	adc_init();
	write_usb_serial_blocking("ADC Init\n\r", 11);

	adc_trigger_sample();

	while(1);
}