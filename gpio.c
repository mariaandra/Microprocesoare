#include "gpio.h"

#define PIN_A (12)

#define RED_LED_PIN (18)
#define GREEN_LED_PIN (19)
#define BLUE_LED_PIN (1)

void Buzzer_Init(void)
{
	
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	PORTA->PCR[PIN_A] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[PIN_A] |= PORT_PCR_MUX(1);
	
	GPIOA->PDDR |= (1<<PIN_A);
	GPIOA->PCOR |= (1<<PIN_A);
}

void Led_Init(void)
{
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	
	PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(1);
	
	GPIOB_PDDR |= (1<<RED_LED_PIN);
	GPIOB_PSOR |= (1<<RED_LED_PIN);
	
	PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(1);
	
	GPIOB_PDDR |= (1<<GREEN_LED_PIN);
	GPIOB_PSOR |= (1<<GREEN_LED_PIN);
	
	PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(1);
	
	GPIOD_PDDR |= (1<<BLUE_LED_PIN);
	GPIOD_PSOR |= (1<<BLUE_LED_PIN);
}

void Buzzer_Start(void)
{
	GPIOA->PSOR |= (1<<PIN_A);
}

void Buzzer_Stop(void)
{
		GPIOA->PCOR |= (1<<PIN_A);
}

void changeLED(int val)
{
		GPIOB_PSOR |= (1<<RED_LED_PIN);
		GPIOD_PSOR |= (1<<BLUE_LED_PIN);
		GPIOB_PSOR |= (1<<GREEN_LED_PIN);
	
	if (val == 1) {
		GPIOB_PCOR |= (1<<RED_LED_PIN);
	} else if (val == 2) {
		GPIOD_PCOR |= (1<<BLUE_LED_PIN);
	} else if (val == 3) {
		GPIOB_PCOR |= (1<<GREEN_LED_PIN);
	} else if (val == 4) {
		GPIOB_PCOR |= (1<<RED_LED_PIN);
		GPIOD_PCOR |= (1<<BLUE_LED_PIN);
	} else if (val == 5) {
		GPIOD_PCOR |= (1<<BLUE_LED_PIN);
		GPIOB_PCOR |= (1<<GREEN_LED_PIN);
	} else if (val == 6) {
		GPIOB_PCOR |= (1<<RED_LED_PIN);
		GPIOB_PCOR |= (1<<GREEN_LED_PIN);
	} else if (val == 7) {
		GPIOB_PCOR |= (1<<RED_LED_PIN);
		GPIOD_PCOR |= (1<<BLUE_LED_PIN);
		GPIOB_PCOR |= (1<<GREEN_LED_PIN);
	}
}
