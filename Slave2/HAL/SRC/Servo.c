
#include "Servo.h"


void SERVO_Init(void)
{
	
	SET_BIT(DDRD,PD5); // OC1A
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER0_SCALER_8,OCRA_NON_INVERTING,OCRB_DISCONNECTED);
	ICR1 =19999; // Ttotal = 20000usec
}

void SERVO_SetAngle(uint8 angle)
{
	OCR1A=(999+(((uint32)angle*1000)/180));
}

