/*
 * main.h
 *
 * Created: 5/29/2020 05:18:11 AM
 *  Author: mohammed awwad
 */ 


#ifndef MAIN_H_
#define MAIN_H_



#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"
#include "lcd.h"
#include "spi.h"
#include "adc.h"

#define LDR_THESHOLD_VALUE 300

typedef enum {
	NO_ACTION,
	CAR_DEC,
	CAR_INC,
	CAR_LEFT,
	CAR_COMES
} CarState_t;

#define ENTER_LDR_BIT	0
#define EXIT_LDR_BIT	1

#define SLAVES_PORT	PORTB
#define SLAVES_DDR	DDRB
#define SLAVES_PIN	PINB

#define SLAVE_1_PIN	0
#define SLAVE_2_PIN	1

typedef enum {
	ENTER_LDR,
	EXIT_LDR
} ADC_Channel_t;
typedef enum {
	SLAVE_1=(1<<SLAVE_1_PIN),
	SLAVE_2=(1<<SLAVE_2_PIN)
} slaveSelect_t;

uint16 enter_reading;
uint16 exit_reading;
uint8  data_Buffer;
uint8 Flags=0;
uint8 numer_of_cars=0;

CarState_t Car=NO_ACTION;


void selectSlave(slaveSelect_t slave);
void unselectSlave(void);
void initSlaves(void);

void initSlaves(void)
{
	SLAVES_DDR |= (1<<SLAVE_1_PIN) | (1<<SLAVE_2_PIN);
	SLAVES_PORT |= (1<<SLAVE_1_PIN) | (1<<SLAVE_2_PIN);
}

void selectSlave(slaveSelect_t slave)
{
	SLAVES_PORT &=~ slave;
}

void unselectSlave(void)
{
	SLAVES_PORT |= SLAVE_1 | SLAVE_2;
}



#endif /* MAIN_H_ */