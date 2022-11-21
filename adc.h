#include "MKL25Z4.h"

enum ADC_Low_Power {
    ADC_Low_Power_OFF=0,
    ADC_Low_Power_ON=1
};
enum ADC_Size {
    ADC_Size_8bits = 0,
    ADC_Size_12bits = 1,
    ADC_Size_10bits = 2,
    ADC_Size_16bits = 3
};

enum ADC_Sample_Time {
    ADC_Sample_Time_Minimal=0,
    ADC_Sample_Time_20_Extra_cycles=0x10,
    ADC_Sample_Time_12_Extra_cycles=0x11,
    ADC_Sample_Time_6_Extra_cycles=0x12,
    ADC_Sample_Time_2_Extra_cycles=0x13
};

enum ADC_Avg {
    ADC_No_Avg=0,
    ADC_Avg_4_Samples_Avg=0x10,
    ADC_Avg_8_Samples_Avg=0x11,
    ADC_Avg_16_Samples_Avg=0x12,
    ADC_Avg_32_Samples_Avg=0x13
};

void adcInit(enum ADC_Low_Power lp, enum ADC_Size size, enum ADC_Sample_Time sampleTime,enum ADC_Avg avg );
void ADCInitMaxSpeed(void);
int adcSelectTemp(void);
int adcSelectBandgapRef(void);
int adcSelectVref(void);
uint16_t adcRead(int channel);
int adcSelect(void);
