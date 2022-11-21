#include "Pit.h"
#include "Uart.h"

uint32_t timer_value;
int flag;

void PIT_Init(void)
{	
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;

	PIT_MCR &= ~PIT_MCR_MDIS_MASK;

	PIT->MCR |= PIT_MCR_FRZ_MASK;

	PIT->CHANNEL[0].LDVAL = 0x9FFFFF;
	
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;
	
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
	
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_SetPriority(PIT_IRQn,5);
	NVIC_EnableIRQ(PIT_IRQn);
	
	flag = 0;
}

void PIT_IRQHandler(void)
{	
	if(PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
		timer_value++;
		flag = 1;
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
	}
}