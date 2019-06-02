/*
* buzzer_module_defines.h
*
* Created: 9/12/2018 6:04:31 PM
*  Author: gheorghita.brasovean
*/


#ifndef BUZZER_MODULE_DEFINES_H_
#define BUZZER_MODULE_DEFINES_H_

#include <avr/io.h>
#include "stdutils.h"

typedef struct{
	
	volatile uint8_t *BuzzerPort;
	unsigned char BITx;
	
} BuzzerPin;

BuzzerPin Init;

/**
 * \brief				<< Used to set the buzzer pin or any other pin direction >>
 *
 * \param PORT			Port address
 * \param BIT			Select the Bit
 * \param STATE			* Initiate the direction of Pin
 * 							- INPUT 0  -> Pin is configured as an input Pin.
 * 							- OUTPUT 1 -> Pin is configured as an output Pin.
 * 
 * \return void
 */
void bitDirectionInit(volatile uint8_t *PORT, unsigned char BIT, unsigned char STATE);


/**
 * \brief				Initialization PWM buzzer method CTC with prescaler of 8
 * 
 * \return void
 */
void buzzerPWM_init();  


#endif /* BUZZER_MODULE_DEFINES_H_ */