#include "adc.h"

#define PIN_C (2)
#define CHANNELS_A_SHIFT	(5)

void adcInit(enum ADC_Low_Power lp, enum ADC_Size size, enum ADC_Sample_Time sampleTime, enum ADC_Avg avg)
{    
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

    if(lp==ADC_Low_Power_ON)
        ADC0->CFG1 = ADC_CFG1_ADLPC_MASK;
    if(sampleTime>0){
        ADC0->CFG1 |= ADC_CFG1_ADLSMP_MASK;        
        ADC0->CFG2 = ADC_CFG2_ADLSTS(sampleTime&3);
    }

    ADC0->CFG1 |=ADC_CFG1_ADIV(1)
               | ADC_CFG1_MODE(size)
               | ADC_CFG1_ADICLK(0);

		ADC0->CFG2 = (uint32_t)((ADC0->CFG2 & (uint32_t)~(uint32_t)(
               ADC_CFG2_ADHSC_MASK |
               ADC_CFG2_ADLSTS(0x03)
              )) | (uint32_t)(
               ADC_CFG2_ADACKEN_MASK
              ));

    if(avg>0)
    ADC0->SC3 = ADC_SC3_AVGE_MASK
              | ADC_SC3_AVGS(avg&3);
}

void ADCInitMaxSpeed(void)
{
    adcInit(ADC_Low_Power_ON,ADC_Size_8bits,ADC_Sample_Time_Minimal,ADC_No_Avg);
    ADC0->CFG1 &=~ADC_CFG1_ADIV_MASK;
}

int adcSelect(void)
{
    int channel=-1;
		
		SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
		PORTC->PCR[PIN_C]&= ~PORT_PCR_MUX_MASK;
		channel=11;   
    
		return channel;
}
int adcSelectTemp(void)
{
    return 26;
}

int adcSelectVref(void)
{
    return 29;
}
uint16_t adcRead(int channel)
{
    if(channel>=0){
			ADC0->SC1[0] = ADC_SC1_ADCH(channel & ~(1 << CHANNELS_A_SHIFT));

			while ((ADC0->SC1[0] & ADC_SC1_COCO_MASK) != ADC_SC1_COCO_MASK);

			return (uint16_t)ADC0->R[0];
    }
    return 0;
}
