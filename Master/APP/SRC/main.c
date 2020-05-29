/*
 * main.h
 *
 * Created: 5/29/2020 05:18:11 AM
 *  Author: mohammed awwad
 */ 
#include "main.h"

int main(void)
{
	LCD_init();
	initSlaves();
	SPI_initMaster();
	ADC_init();
	LCD_goToRowColumn(0,0);
	LCD_displayString("** MASTER ECU **");
	LCD_goToRowColumn(1,0);
	LCD_displayString("** NOO ACTION **");
	
	while(1)
	{
		enter_reading = ADC_readChannel(ENTER_LDR);
		exit_reading = ADC_readChannel(EXIT_LDR);
		if(enter_reading < LDR_THESHOLD_VALUE)
		{
			if (!(Flags & (1<<ENTER_LDR_BIT)))
			{
				Flags |= (1<<ENTER_LDR_BIT);
				selectSlave(SLAVE_1);
				SPI_sendByte(CAR_COMES);
				unselectSlave();
				LCD_clearScreen();
				LCD_goToRowColumn(0,0);
				LCD_displayString("Car Enters      ");
			}
		}
		else
		{
			if ((Flags & (1<<ENTER_LDR_BIT)))
			{
				Flags &=~ (1<<ENTER_LDR_BIT);
				selectSlave(SLAVE_1);
				SPI_sendByte(CAR_LEFT);
				unselectSlave();
				LCD_clearScreen();
				LCD_goToRowColumn(0,0);
				LCD_displayString("Car Entered");
				numer_of_cars++;
			}
		}
		
		if(exit_reading < LDR_THESHOLD_VALUE)
		{
			if (!(Flags & (1<<EXIT_LDR_BIT)))
			{
				if (numer_of_cars!=0)
				{
					Flags |= (1<<EXIT_LDR_BIT);
					selectSlave(SLAVE_2);
					SPI_sendByte(CAR_COMES);
					unselectSlave();
					LCD_clearScreen();
					LCD_goToRowColumn(1,0);
					LCD_displayString("Car Leaves  ");
				}
				
				
				
			}
		}
		else
		{
			if ((Flags & (1<<EXIT_LDR_BIT)))
			{
				if (numer_of_cars!=0)
				{
					Flags &=~ (1<<EXIT_LDR_BIT);
					selectSlave(SLAVE_2);
					SPI_sendByte(CAR_LEFT);
					unselectSlave();
					LCD_clearScreen();
					LCD_goToRowColumn(1,0);
					LCD_displayString("Car Left   ");
					numer_of_cars--;
				}
			}
		}
	}
}
