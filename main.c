#include "Uart.h"
#include "gpio.h"
#include "Adc.h"
#include "Pit.h"

volatile extern uint32_t timer_value;
volatile extern int status;
volatile extern float measured_voltage;
volatile extern uint16_t analog_input;

void UTILS_Print(float value)
{	
	uint8_t parte_zecimala = (uint8_t) value;
	uint8_t parte_fractionara1 = ((uint8_t)(value * 10)) % 10;
	uint8_t parte_fractionara2 = ((uint8_t)(value * 100)) % 10;
	UART0_Transmit('V');
	UART0_Transmit('o');
	UART0_Transmit('l');
	UART0_Transmit('t');
	UART0_Transmit('a');
	UART0_Transmit('g');
	UART0_Transmit('e');
	UART0_Transmit(' ');
	UART0_Transmit('=');
	UART0_Transmit(' ');
	UART0_Transmit(parte_zecimala + 0x30);
	UART0_Transmit('.');
	UART0_Transmit(parte_fractionara1 + 0x30);
	UART0_Transmit(parte_fractionara2 + 0x30);
	UART0_Transmit('V');
	UART0_Transmit(0x0A);
	UART0_Transmit(0x0D);
}

int main()
{
	
	UART0_Init(115200);
	Buzzer_Init();
	Led_Init();
	PIT_Init();
	ADC0_Init();
	
	uint32_t aux_timer;
	int aux_status;
	
	aux_status = status;
	
	while(1) {
		if(aux_status != status) {	
			changeLED(status);
			aux_status = status;
		}
		
		analog_input = ADC0_Read();
		measured_voltage = (analog_input * 3.3f) / 65535;
		UTILS_Print(measured_voltage);		
		
		if(measured_voltage > 0.4) {
			UTILS_Print(measured_voltage);
			Buzzer_Start();
			aux_timer = timer_value;
			while(timer_value < aux_timer + 3);
			Buzzer_Stop();
		}
	}
}