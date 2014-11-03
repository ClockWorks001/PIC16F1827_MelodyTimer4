/*************************************************
*  clock01
*************************************************/
#define vClock01_LIB

#include <xc.h>         // XC8 General Include File
#include "vClock01.h"

/*******************************
*  clear clock01 parameter
*******************************/
void vClock01_Clear()
{
	sSecc = 0;
	cFlagSec = 0;
	ucSec01= ucMin01= ucHour01=0;
}

/*******************************
*  user interrupt work
*  call this work evry 10msec interrupt.
*******************************/
void vClock01_interrupt()
{
    // for Timer1 interrupted
    cFlag10mSec = 1;
    sSecc++;
    if(sSecc >= 100 ){			// 10msec * 100 = 1sec
            sSecc = 0;
            cFlagSec++;
    }
}

/*******************************
*  check & clear 10msec count
*******************************/
char cFlag10mSec_ON()
{
    if(cFlag10mSec == 1){
            cFlag10mSec = 0;
            return 1;
    } else {
            return 0;
    }

}

/*******************************
*  Timer count
*******************************/
void vClock01()
{

	if(cFlagSec) {					// 1sec passing
		ucSec01 += cFlagSec;		// add 1 sec
		cFlagSec = 0;
		if(ucSec01 > 59){			// 1 minute passing
			ucSec01 = 0;
			ucMin01++;				// add 1 minute

			cMinCountDown--;		// count down 1 minute

			if(ucMin01 > 59){
				ucMin01 = 0;
				ucHour01++;			// 1 hour passing
				if(ucHour01 > 23){
					ucHour01 = 0;
				}
			}

		}

	}
}

