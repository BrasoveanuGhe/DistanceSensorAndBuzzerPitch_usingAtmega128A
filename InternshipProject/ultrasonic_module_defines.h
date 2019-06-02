/*
* Sonic_buzzer_defines.h
*
* Created: 8/1/2018 1:52:23 PM
*  Author: Gheorghita.Brasovean
*/


#ifndef SONIC_BUZZER_DEFINES_H_
#define SONIC_BUZZER_DEFINES_H_

#ifndef L_BUF_TX
#define  L_BUF_TX 128
#endif

#ifndef F_CPU
#define F_CPU  7372800UL	
#endif

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//int PINx;
extern char snTelegramaTx[L_BUF_TX];

#define TIMER_MAX 65535 // 65535 for 16 bit timer

/***********************************************
* Time taken for a pulse to travel to an object and
bounce back 1 centimeter is 58.31 microseconds.
<< OR >>
#define SPEED_OF_SOUND  343
#define CONVERT_TO_CM ((10000*2)/SPEED_OF_SOUND)
****************************************************/
#define CONVERT_TO_CM 58.31
#define CYCLE_PER_US (F_CPU/1000000)	// Instructions per microsecond
#define N 8				// The N variable represents the prescaler factor
#define MF_Variable 5.5			// The variable MF represents the value used to obtain the frequency
#define val_Hz 1000			// Represents the maximum value of hertz


extern char string[10];
extern float distance;
extern bool checkSignalEdge;
extern bool detectFallingEdge;
extern double freqToDistance;
extern double buzzerFrequency;
extern volatile uint32_t count;
extern volatile uint32_t TimerOverflow;


/**
 * \brief		Function that changes the frequency of the buzzer depending on the distance
 *				(2 cm - 1000hz -> and the higher it grows -> 100 cm - 450hz)
 *  
 * \return void
 */
void frequencyBuzzer();

//Gets value for distance and displays it on the series
void get_UltrasonicDist();

// The function calculates the time the signal received by echo was high
void risingEdge_duration();

void uart1_Transmite(char *sTransmis,
					unsigned int nLungime,
					bool bAsteptareTxAnterioara);

#endif /* SONIC_BUZZER_DEFINES_H_ */
