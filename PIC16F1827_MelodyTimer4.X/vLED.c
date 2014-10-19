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
#include "vLED.h"
#include "vSwitch_menu.h"

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
void vLEDOutput(char cMinTime)
{
		if (sSecc < 6) {			//LED Blink
			if (cMinTime <= WAIT3MIN) {
					LED3min_ON();
			}else if (cMinTime <= WAIT5MIN) {
					LED5min_ON();
			}else{
					LED10min_ON();
			}
		}else{
			vLEDClear();			//LED all clear
		}
}
