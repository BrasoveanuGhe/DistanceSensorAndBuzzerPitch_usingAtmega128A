/*
* buzzer_func.c
*
* Created: 9/12/2018 6:04:57 PM
*  Author: gheorghita.brasovean
*/


#include "buzzer_defines.h"
#include "timers.h"
#include "ultrasonic_module_defines.h"


// Used to set the buzzer pin or any other pin direction >>
void bitDirectionInit(volatile uint8_t *PORT, unsigned char BIT, unsigned char STATE)
{
	Init.BuzzerPort = PORT;
	Init.BITx = BIT;
	
	if (STATE == OUTPUT)
	{
		*(Init.BuzzerPort-1) |= (1 << Init.BITx);
		
	}else
	
		*(Init.BuzzerPort-1) &= ~(1 << Init.BITx);
}

// Buzzer PWM
void buzzerPWM_init()
{
	tc3_write_ocom_mode(TC3_OCOMA_TOGGLE);		// Toggle on compare match.
	tc3_set_wgm(TC3_WG_CTC_OCR1A);				// CTC Mode
	tc3_write_clock_source(TC3_CLKSEL_PS_8);	// ClkI/O/8 (From prescaler)
	bitDirectionInit(&PORTE,PINE3,OUTPUT);		
}
