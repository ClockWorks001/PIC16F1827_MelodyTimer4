/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "mcc_generated_files/mcc.h"
#include "user.h"          /* User funct/params, such as InitApp */
#include "vClock01.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

#define SWITCH1_ON  IO_RA4_GetValue() == 0
#define SWITCH1_OFF IO_RA4_GetValue() == 1
#define SWITCH2_ON  IO_RA5_GetValue() == 0
#define SWITCH2_OFF IO_RA5_GetValue() == 1
#define LED1_ON()	IO_RB0_SetHigh()
#define LED1_OFF()	IO_RB0_SetLow()
#define LED2_ON()	IO_RB1_SetHigh()
#define LED2_OFF()	IO_RB1_SetLow()
#define LED3_ON()	IO_RB2_SetHigh()
#define LED3_OFF()	IO_RB2_SetLow()

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
	SYSTEM_Initialize();

    /* Configure the oscillator for the device */
    OSCILLATOR_Initialize();

    /* Initialize I/O and Peripherals for application */
    InitApp();

	// Start Peripherals
	INTERRUPT_PeripheralInterruptEnable();
	INTERRUPT_GlobalInterruptEnable();
	TMR1_StartTimer();
	TMR2_StartTimer();
    // User add cording
    vClock01_Clear();

    while(1)
    {
        /* TODO <INSERT USER APPLICATION CODE HERE> */
		vClock01();

		if(SWITCH1_ON){
			LED1_ON();
		} else {
			LED1_OFF();
		}

		if(SWITCH2_ON){
			LED2_ON();
		} else {
			LED2_OFF();
		}

		if((ucSec01 % 2) == 0){
			LED3_ON();
		} else {
			LED3_OFF();
		}
		
	}

}

