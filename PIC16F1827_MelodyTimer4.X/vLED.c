/*************************************************
*  LED output
*    vLcd_cmd(cmd)  ----- コマンド出力
*    vLcd_data(data) ----- １文字表示出力
*    cDataTrans(data) ----- I2Cデータ出力共通関数
*************************************************/
#define vLED_LIB

#include <xc.h>         // XC8 General Include File
#include "mcc_generated_files/mcc.h"
#include "vClock01.h"
#include "vBuzzer_pwm.h"
#include "vLED.h"


//******************************************************************************
//  LED Clear
//******************************************************************************
void vLEDClear(void)
{
	LED3min_OFF();			//出力low
	LED5min_OFF();			//出力low
	LED10min_OFF();			//出力low
}

//******************************************************************************
//  LED output
//******************************************************************************
void vLED_Melody(AMELODY_DATA* pAMD)
{
        switch ((pAMD->ucMusicPosition)%3) {			//LED Blink
	case  	0 :
		LED3min_ON();			//出力low
		break;

	case  	1 :
		LED5min_ON();			//出力low
		break;

	case  	2 :
	default:
		LED10min_ON();			//出力low
		break;

	}
}

//******************************************************************************
//  LED output
//******************************************************************************
void vLED_CountDown(char cMinCountDownTime)
{
        if (sSecc < 60) {			//LED Blink
                if (cMinCountDownTime <= WAIT3MIN) {
                    LED3min_ON();
                }else if (cMinCountDownTime <= WAIT5MIN) {
                    LED5min_ON();
                }else{
                    LED10min_ON();
                }
        }else{
                vLEDClear();			//LED all clear
        }
}

static char cWk1State = 0;
/*****************************
* LED Blink 01
* 曲に合わせてLEDを点滅させる。
*****************************/
void vLEDBlink01(void)
{
        vLEDClear();			//LED all clear
	switch (eMenu_LED_Status) {
	case  	eMenu_LED_LED3min_ON :
		LED3min_ON();			//出力low
		break;

	case  	eMenu_LED_LED5min_ON :
		LED5min_ON();			//出力low
		break;

	case  	eMenu_LED_LED10min_ON :
		LED10min_ON();			//出力low
		break;

	case  	eMenu_LED_Melody :
                vLED_Melody(&sAMD);
		break;

	case  	eMenu_LED_CountDown :
                vLED_CountDown(cMinCountDown);
		break;

	case  	eMenu_LED_ALL_OFF :
        	LED3min_OFF();			//出力low
                LED5min_OFF();			//出力low
                LED10min_OFF();			//出力low
		break;

	default:
		eMenu_LED_Status = eMenu_LED_ALL_OFF;
	}
}

