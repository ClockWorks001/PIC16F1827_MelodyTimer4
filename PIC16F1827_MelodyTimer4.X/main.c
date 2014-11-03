/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "mcc_generated_files/mcc.h"
#include "user.h"          /* User funct/params, such as InitApp */
#include "vClock01.h"
#include "vLED.h"
#include "vSwitch_menu.h"


/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

//#define SW1_ON  IO_RA4_GetValue() == 0
//#define SW1_OFF IO_RA4_GetValue() == 1
//#define SW2_ON  IO_RA5_GetValue() == 0
//#define SW2_OFF IO_RA5_GetValue() == 1

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
                if (cFlag10mSec_ON){
                    vSW1_Check();
                    vSW2_Check();
                    vMenuForSW1();
                }

//		if(SW1_ON){
//			LED1_ON();
//		} else {
//			LED1_OFF();
//		}
//
//		if(SW2_ON){
//			LED2_ON();
//		} else {
//			LED2_OFF();
//		}
//
//		if((ucSec01 % 2) == 0){
//			LED3_ON();
//		} else {
//			LED3_OFF();
//		}
		
    }

}

