/*************************************************
*  Switch_Menu
*    Switch1 is status for Main routin.
*    Switch2 is status for Timer setting.
*************************************************/
#define SWITCH_MENU_LIB

#include <xc.h>         // XC8 General Include File
#include "mcc_generated_files/mcc.h"
#include "vBuzzer_pwm.h"
#include "vClock01.h"
#include "vLED.h"
#include "vSwitch_menu.h"

SWITCHS SW1;
SWITCHS SW2;

static unsigned char cCountDownTime = WAIT3MIN;


//******************************************************************************
//  Switch SW1
//    push SW1 on/off check function
//    this function should be called at intervals 10msec.
//    SW1 go forward the eMenu_SW1_Status.
//******************************************************************************
void vSW1_Check(void)
{
	if(SW1_ON){
		switch(SW1.OnTime){
			case 0:
				eMenu_SW1_Status++;
				break;

			case 100:			//10msec*100 wait for the first push
				//repeat
				eMenu_SW1_Status++;
				SW1.OnTime = 100 - 30; 	//10msec*30 wait for repeat
				break;

			default:
				break;
		}
		SW1.OnTime++;
	}else{
		SW1.OnTime = 0;
	}
}

//******************************************************************************
//  Switch SW2
//    push SW2 on/off check function
//    this function should be called at intervals 10msec.
//    SW2 go forward the eMenu_SW2_Status.
//******************************************************************************
void vSW2_Check(void)
{
	if(SW2_ON){
		switch(SW2.OnTime){
			case 0:
				eMenu_SW2_Status++;
				break;

			case 100:			//10msec*100 wait for the first push
				//repeat
				eMenu_SW2_Status++;
				SW2.OnTime = 100 - 30; 	//10msec*30 wait for repeat
				break;

			default:
				break;
		}
		SW2.OnTime++;
	}else{
		SW2.OnTime = 0;
	}
}

/*****************************
* eMenu_SW2_Status clear
*****************************/
/*void vModeStatusClr(void)
{
	eMenu_SW1_Status = eMenu_SW1_Wait;
	eMenu_SW2_Status = eMenu_SW2_Start;
}
*/

/*****************************
* Menu for SW1
*****************************/
void vMenuForSW1(void)
{
	switch (eMenu_SW1_Status) {
		case  	eMenu_SW1_Start :
			vLEDClear();	
			vClock01_Clear();

			eMenu_SW1_Status++;
			break;

		case  	eMenu_SW1_Pre_CountDown :
			vClock01_Clear();		
			cMinCountDown = cCountDownTime;	//カウントダウンタイマ初期化
			vStopBuzzer();			
			eMenu_SW1_Status++;		
			break;

		case  	eMenu_SW1_CountDown :		
			if (cMinCountDown <= 0) {	//IF Time Up
				eMenu_SW1_Status++;
			}
			vLEDOutput(cMinCountDown);
			break;

		case  	eMenu_SW1_Pre_Melody :
			vClock01_Clear();
			usGakufuIchi = 0;		//set start point of a Melody data.
			eMenu_SW1_Status++;
			break;

		case  	eMenu_SW1_Melody :		//play a melody
			vMelody01();

			if (ucMin01 > 10 && usGakufuIchi == 0) {	//音楽が10分以上経過し演奏が終わったら停止
				eMenu_SW1_Status = eMenu_SW1_Sleep;
			}

			break;

		// ---------------------------------------------------
		case  	eMenu_SW1_Wait :
                        vMenuForSW2();                       //time setting
                        // sleep判定を入れる
                        break;

		case  	eMenu_SW1_Go_Timer_Start :
	//		vStopBuzzer();					//音楽停止
			eMenu_SW1_Status = eMenu_SW1_Start;	//先頭処理へ戻る
			break;

		// ---------------------------------------------------
		case  	eMenu_SW1_Sleep :
			vStopBuzzer();				//音楽停止
			vLEDClear();				//LED CLEAR

//			IOC3	= 1;				// GPIO3の割込み許可
//			GPIF	= 0;				// io_pin全体の割込みフラグのクリア
			INTERRUPT_PeripheralInterruptEnable();
			INTERRUPT_GlobalInterruptEnable();
			SLEEP();
			NOP();
//			GPIF	= 0;				// io_pin全体の割込みフラグのクリア
//			IOC3	= 0;				// GPIO3の割込み許可

		// wake up 時の戻り先
	//		eMenu_SW1_Status = eMenu_SW1_Start;	//先頭処理へ戻る
			eMenu_SW1_Status = eMenu_SW1_Wait;	//TimerSet処理へ戻る
			break;
		default:
			eMenu_SW1_Status = eMenu_SW1_Start;
	}

}

/*****************************
* Menu for SW2 (time setting)
*****************************/
void vMenuForSW2(void)
{
	switch (eMenu_SW2_Status) {
		case  	eMenu_SW2_Start :
			vClock01_Clear();
			vStopBuzzer();
			switch (cCountDownTime) {
			case  	WAIT3MIN :
				eMenu_SW2_Status = eMenu_SW2_Set3min ;
			break;
			case  	WAIT5MIN :
				eMenu_SW2_Status = eMenu_SW2_Set5min ;
			break;
			case  	WAIT10MIN :
				eMenu_SW2_Status = eMenu_SW2_Set10min ;
			break;
			default:
				eMenu_SW2_Status = eMenu_SW2_Set3min ;
			}
                        eMenu_SW2_Status++;
			break;
		case  	eMenu_SW2_Set3min :
			cCountDownTime = WAIT3MIN;		//カウントダウン時間を3分に設定
			vLEDClear();				//LED CLEAR
			LED3min_ON();				//出力low
			break;

		case  	eMenu_SW2_Set5min :
			cCountDownTime = WAIT5MIN;		//カウントダウン時間を5分に設定
			vLEDClear();				//LED CLEAR
			LED5min_ON();				//出力low
			break;

		case  	eMenu_SW2_Set10min :
			cCountDownTime = WAIT10MIN;	//カウントダウン時間を10分に設定
			vLEDClear();				//LED CLEAR
			LED10min_ON();				//出力low
			break;

		case	eMenu_SW2_ReturnToSet3min:
			eMenu_SW2_Status = eMenu_SW2_Set3min;
			break;

		case	eMenu_SW2_Wait:
			break;

		default:
			eMenu_SW2_Status = eMenu_SW2_Start;
	}

}



