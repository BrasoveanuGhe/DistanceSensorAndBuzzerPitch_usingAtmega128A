/*
* sonic_buzzer_func.c
*
* Created: 8/1/2018 1:53:02 PM
*  Author: Gheorghita.Brasovean
*/

#include "timers.h"
//Timer driver (Timer0, Timer1, Timer3)

#include "ultrasonic_module_defines.h"
//Application related defines and variables

#include "avr_extInterrupt.h"
//External Interrupt Control Register driver

#include "ultrasonic_pins_defines.h"
//Ultrasonic initialization (Ports, Pins)

#include "buzzer_defines.h"
//Buzzer initialization and PWM (Ports, Pins)

char string[10];
float distance;
double freqToDistance;
double buzzerFrequency;
volatile uint32_t count = 0;
bool checkSignalEdge = true;
bool detectFallingEdge = false;
volatile uint32_t TimerOverflow = 0;



inline void risingEdge_duration()
{
	// Represent the time when the echo signal was high
	count = ((TimerOverflow*TIMER_MAX)+tc1_get_current_cValue());	// Counter count
	distance = (count/(CONVERT_TO_CM*CYCLE_PER_US));		// Distance in cm
	
	// If the measured distance is less than 3, it will be 2
	/* MIN : 2 cm */
	if(distance < 3){
		distance = 2;
	}
	//If the measured distance is greater than 400, it will be 400
	/* MAX : 400 cm */
	else if(distance > 400){
		distance = 400;
	}
}


void frequencyBuzzer()
{
	// The maximum distance to which the frequency can be changed
	if(distance >= 100){
		
		distance = 100;
	}
	
	// Frequency change based on distance is defined by the next equation
	freqToDistance = (val_Hz - (MF_Variable * distance));
	// The waveform frequency is defined by the following equation
	buzzerFrequency = (F_CPU / (2 * N * freqToDistance));

	OCR3A = buzzerFrequency;
}


void get_UltrasonicDist()
{
	if(detectFallingEdge == true)
	{
		risingEdge_duration();
		dtostrf(distance, 9, 3, string);	// distance to string
		sprintf(snTelegramaTx, "\n\rDistance: %s cm", string);
		uart1_Transmite(snTelegramaTx, strlen(snTelegramaTx), true);
		detectFallingEdge = false;
		checkSignalEdge = true;
	}
}


ISR(INT5_vect)
{
	// Rising Edge
	if (checkSignalEdge)
	{
		//reset timer -> TCNT = 0
		tc1_set_current_cValue(0);
		TimerOverflow = 0;
		// Reset EICRB register
		reset_extInterrupt_B();
		// No prescaler
		tc1_write_clock_source(TC1_CLKSEL_PS_1);
		/* Wait for falling edge */
		set_extInterrupt(&EICRB,INT5,FALLING_EDGE_5);
		checkSignalEdge = false;
	}
	// Falling edge
	else {
		// Stop Timer
		tc_stopTimer(timer1);
		// Reset EICRB register
		reset_extInterrupt_B();
		detectFallingEdge = true;
		/* Wait for rising edge */
		set_extInterrupt(&EICRB,INT5,RISING_EDGE_5);		
	}
}


ISR(TIMER1_OVF_vect)
{
	//Counter that increments each time TCNT reaches the maximum value
	TimerOverflow ++;
}


