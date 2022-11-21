#include "Uart.h"

char c;
int status;

void UART0_Transmit(uint8_t data)
{
	while(!(UART0->S1 & UART0_S1_TDRE_MASK));
				UART0->D = data;
}

uint8_t UART0_receive(void)
{
	while(!(UART0->S1 & UART0_S1_RDRF_MASK));
				return UART0->D;
}

void UART0_Init(uint32_t baud_rate)
{
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(01);
	
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	PORTA->PCR[1] = ~PORT_PCR_MUX_MASK;
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
	PORTA->PCR[2] = ~PORT_PCR_MUX_MASK;
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
	
	
	
	UART0->C2 &= ~((UART0_C2_RE_MASK) | (UART0_C2_TE_MASK)); 
	
	uint32_t osr = 15;
	
	uint16_t sbr = (uint16_t)((DEFAULT_SYSTEM_CLOCK)/(baud_rate * (osr+1)));
	uint8_t temp = UART0->BDH & ~(UART0_BDH_SBR(0x1F));
	UART0->BDH = temp | UART0_BDH_SBR(((sbr & 0x1F00)>> 8));
	UART0->BDL = (uint8_t)(sbr & UART_BDL_SBR_MASK);
	UART0->C4 |= UART0_C4_OSR(osr);
	
	
	UART0->C1 = 0;
	
	UART0->C2 |= UART0_C2_TIE(0);
	UART0->C2 |= UART0_C2_TCIE(0);
	
	
	UART0->C2 |= UART0_C2_RIE(1);
	
	UART0->C2 |= ((UART_C2_RE_MASK) | (UART_C2_TE_MASK));
	
	NVIC_EnableIRQ(UART0_IRQn);
	
	status = 0;
	
}

void UART0_IRQHandler(void)
{
		if(UART0->S1 & UART0_S1_RDRF_MASK) {
			c = UART0->D;
		}
		
		if(c == '0')
			status = 0;
		else if(c == '1')
			status = 1;
		else if(c == '2')
			status = 2;
		else if(c == '3')
			status = 3;
		else if(c == '4')
			status = 4;
		else if(c == '5')
			status = 5;
		else if(c == '6')
			status = 6;
		else if(c == '7')
			status = 7;
}
