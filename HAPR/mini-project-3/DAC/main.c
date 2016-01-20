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

#define PI 3.14159265

float dac_amplitude;
float dac_frequency;
float dac_radian_value;

int read_usb_serial_none_blocking(char *buf,int length)
{
        return(UART_Receive((LPC_UART_TypeDef *)LPC_UART0, (uint8_t *)buf, length, NONE_BLOCKING));
}

int write_usb_serial_blocking(char *buf,int length)
{
        return(UART_Send((LPC_UART_TypeDef *)LPC_UART0,(uint8_t *)buf,length, BLOCKING));
}

void TIMER0_IRQHandler(void)
 {
         if(TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)== SET) {
                NVIC_DisableIRQ(TIMER0_IRQn);
                TIM_ClearIntPending(LPC_TIM0,TIM_MR0_INT);
                TIM_ResetCounter(LPC_TIM0);

                dac_radian_value = fmod(dac_radian_value + 0.1, 2*PI); // 
                
                DAC_UpdateValue(LPC_DAC,dac_amplitude/3.3 *(1.0+sin(dac_radian_value))/2.0*1023.0);

                NVIC_EnableIRQ(TIMER0_IRQn);
        }
 }

void serial_init()
{
        UART_CFG_Type                 UARTConfigStruct;        // UART Configuration structure variable
        UART_FIFO_CFG_Type         UARTFIFOConfigStruct;        // UART FIFO configuration Struct variable
        PINSEL_CFG_Type         PinCfg;                        // Pin configuration for UART

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
        UARTFIFOConfigStruct.FIFO_Level        = UART_FIFO_TRGLEV0;
        UARTFIFOConfigStruct.FIFO_ResetRxBuf = ENABLE;
        UARTFIFOConfigStruct.FIFO_ResetTxBuf = ENABLE;

        UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

        UART_Init((LPC_UART_TypeDef *)LPC_UART0, &UARTConfigStruct);

        UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART0, &UARTFIFOConfigStruct);

        UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0, ENABLE);
}

void dac_init() {
        PINSEL_CFG_Type         PinCfg;                        // Pin configuration for UART

        PinCfg.Funcnum = 2;
        PinCfg.OpenDrain = 0;
        PinCfg.Pinmode = 0;
        PinCfg.Portnum = 0;
        PinCfg.Pinnum = 26;
        PINSEL_ConfigPin(&PinCfg);

        DAC_Init(LPC_DAC);
}

void timer_init() {
        PINSEL_CFG_Type PinCfg;
    TIM_TIMERCFG_Type TIM_ConfigStruct;

        // Conifg P1.28 as MAT0.0
        PinCfg.Funcnum = 3;
        PinCfg.OpenDrain = 0;
        PinCfg.Pinmode = 0;
        PinCfg.Portnum = 1;
        PinCfg.Pinnum = 28;
        PINSEL_ConfigPin(&PinCfg);

        TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
        TIM_ConfigStruct.PrescaleValue  = 10; //10us = 0.01ms

        TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);
}

void generate_sine(float amplitude, float frequency) {
        dac_amplitude = amplitude;
        dac_frequency = frequency;

    TIM_MATCHCFG_Type TIM_MatchConfigStruct;

        // use channel 0, MR0
        TIM_MatchConfigStruct.MatchChannel = 0;
        // Disable interrupt when MR0 matches the value in TC register
        TIM_MatchConfigStruct.IntOnMatch   = TRUE;
        //Enable reset on MR0: TIMER will reset if MR0 matches it
        TIM_MatchConfigStruct.ResetOnMatch = TRUE;
        //Stop on MR0 if MR0 matches it
        TIM_MatchConfigStruct.StopOnMatch  = FALSE;
        //Toggle MR0.0 pin if MR0 matches it
        TIM_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_NOTHING;
        // Set Match value
        TIM_MatchConfigStruct.MatchValue   = (int)(1500.0/frequency);

        TIM_ConfigMatch(LPC_TIM0,&TIM_MatchConfigStruct);
        TIM_Cmd(LPC_TIM0,ENABLE);
        
        NVIC_EnableIRQ(TIMER0_IRQn);
}



void main(void)
{
        serial_init();
        write_usb_serial_blocking("Hello World\n\r", 14);

        dac_init();
        write_usb_serial_blocking("DAC Init\n\r", 11);

        timer_init();
        write_usb_serial_blocking("TIMER Init\n\r", 13);

        generate_sine(3,10.0);

        while(1);
}