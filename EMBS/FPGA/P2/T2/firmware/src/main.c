#include "stdio.h"
#include "stdlib.h"
#include "xparameters.h"
#include "xuartlite_l.h"

#define STATE_ENTER_FIRST 1
#define STATE_FIRST 2
#define STATE_ENTER_OPERATOR 3
#define STATE_OPERATOR 4
#define STATE_ENTER_SECOND 5
#define STATE_SECOND 6
#define STATE_ENTER_COMPUTE 7

int main() {
    char current_char;
    int state = STATE_ENTER_FIRST;
    int operands[2];
    int operand_index;
    char operator;

    while(1)  {
        if(state == STATE_ENTER_COMPUTE) {
            XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\r');
            XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\n');
            XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '=');
            XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, ' ');

            switch(operator) {
                case '+':
                    putnum(operands[0]+operands[1]);
                    break;
                case '*':
                    putnum(operands[0]*operands[1]);
                    break;
                case '/':
                    putnum(operands[0]/operands[1]);
                    break;
                case '-':
                    putnum(operands[0]-operands[1]);
                    break;
            }

            XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\r');
            XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\n');
            state = STATE_ENTER_FIRST;
        }

        if(state == STATE_ENTER_FIRST) {
            operand_index = 0;
            operands[operand_index] = 0;
            state = STATE_FIRST;
        }

        if(state == STATE_ENTER_SECOND) {
            operand_index = 1;
            operands[operand_index] = 0;
            state = STATE_SECOND;
        }

        if(state == STATE_ENTER_OPERATOR) {
            state = STATE_OPERATOR;
        }


        current_char = XUartLite_RecvByte(XPAR_RS232_DTE_BASEADDR);
        XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, current_char);

        if(current_char == 3) {
            state = STATE_ENTER_FIRST;
            XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\r');
            XUartLite_SendByte(XPAR_RS232_DTE_BASEADDR, '\n');
            continue;
        }

        if(state == STATE_OPERATOR) {
        	if(current_char == ' ') {
        		state = STATE_ENTER_SECOND;
        		continue;
        	} else if(current_char == '+' || current_char == '*' || current_char == '-' || current_char == '/') {
            	operator = current_char;
        	}
        }

        if(state == STATE_FIRST || state == STATE_SECOND) {
            if(current_char == ' ') {
                switch(state) {
                    case STATE_FIRST:
                        state = STATE_ENTER_OPERATOR;
                        break;
                    case STATE_SECOND:
                        state = STATE_ENTER_COMPUTE;
                        break;
                }

                continue;
            } else if(current_char >= '0' && current_char < '9') {
                operands[operand_index] = operands[operand_index]*10 + (current_char-'0');
            }
        }
    }

    return 0;
}
