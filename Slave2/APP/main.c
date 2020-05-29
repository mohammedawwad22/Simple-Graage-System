/*
 * main.c
 *
 * Created: 5/29/2020 05:38:58 AM
 * Author : mohammed awwad
 */ 

#include "lcd.h"
#include "uart.h"
#include "spi.h"
#include "Servo.h"



typedef enum {
	NO_ACTION,
	CAR_DEC,
	CAR_INC,
	CAR_LEFT,
	CAR_COMES
} CarState_t;

typedef enum {
	DOOR_CLOSED,
	DOOR_OPEN=90
} doorState_t;

uint8  received_Buffer_SPI;
doorState_t door=DOOR_CLOSED;
CarState_t Car=NO_ACTION;
uint8 number_of_cars=0;



int main(void)
{
	/* Replace with your application code */
	LCD_init();
	UART_init();
	SPI_initSlave();
	SERVO_Init();
	LCD_goToRowColumn(0,0);
	LCD_displayString("*** LEFT GATE ***");
	LCD_goToRowColumn(1,0);
	LCD_intgerToString(number_of_cars);
	sei();
	while (1)
	{
		LCD_goToRowColumn(1,0);
		LCD_intgerToString(number_of_cars);
		
		received_Buffer_SPI = SPI_recieveByte();
		
		if (received_Buffer_SPI == CAR_COMES)
		{
			if (door == DOOR_CLOSED)
			{
				door=DOOR_OPEN;
				SERVO_SetAngle(DOOR_OPEN);
			}
		}
		else if (received_Buffer_SPI == CAR_LEFT)
		{
			if (door == DOOR_OPEN)
			{
				door=DOOR_CLOSED;
				SERVO_SetAngle(DOOR_CLOSED);
				if (number_of_cars!=0)
				{
					number_of_cars--;
					UART_sendByte(CAR_DEC);

				}
				
			}
		}
		
	}
}

ISR(USART_RXC_vect)
{
	if (UDR == CAR_INC)
	{
		number_of_cars++;
		LCD_goToRowColumn(1,0);
		LCD_intgerToString(number_of_cars);
	}
}

