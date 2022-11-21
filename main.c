#include "Uart.h"
#include "gpio.h"
#include "adc.h"
#include "Pit.h"

extern uint32_t timer_value;
extern int status;
extern int flag;

void UTILS_Print(uint32_t value)
{	
	uint8_t aux[4];
	
	aux[3] = (uint8_t)value;
	aux[2] = (uint8_t)(value>>=8);
	aux[1] = (uint8_t)(value>>=8);
	aux[0] = (uint8_t)(value>>=8);
	
	UART0_Transmit(aux[0]);
	UART0_Transmit(aux[1]);
	UART0_Transmit(aux[2]);
	UART0_Transmit(aux[3]);
	
	UART0_Transmit(0x0A);
	UART0_Transmit(0x0D);
}

int main()
{
	
	UART0_Init(115200);
	Buzzer_Init();
	Led_Init();
	adcInit(ADC_Low_Power_OFF,ADC_Size_10bits,ADC_Sample_Time_6_Extra_cycles,ADC_Avg_4_Samples_Avg);
	PIT_Init();
	
	uint32_t val_A0, val_Temp, val_Vref;
	uint32_t aux_timer;
	int aux_status;
	
	aux_status = status;
	
	while(1) {
		
		if(aux_status != status) {
			
			changeLED(status);
			aux_status = status;
		}
			
		if(flag == 1) {
			val_A0 = adcRead(adcSelect());
			
			if(val_A0 != 0) {
				UTILS_Print(val_A0);
				
				if(val_A0 > 0x00000010) {
					
					Buzzer_Start();
					aux_timer = timer_value;
					while(timer_value < aux_timer + 3);
					Buzzer_Stop();
				}
			}
			
			flag = 0;
		}
	}
}