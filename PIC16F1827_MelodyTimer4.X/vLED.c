/*************************************************
*  LED output
*    vLcd_cmd(cmd)  ----- コマンド出力
*    vLcd_data(data) ----- １文字表示出力
*    cDataTrans(data) ----- I2Cデータ出力共通関数
*************************************************/
#define vLED_LIB

#include <xc.h>         // XC8 General Include File
#include "vLED.h"
#include "vClock01.h"

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
			if (cMinTime <= d3min) {
					LED3min_ON();
			}else if (cMinTime <= d5min) {
					LED5min_ON();
			}else{
					LED10min_ON();
			}
		}else{
			vLEDClear();			//LED all clear
		}
}
