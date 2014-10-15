/*************************************************
*  Switch_Menu
*    vPushSwitch_init()  ----- 初期化
*    vSwitch1Check() ----- switch5 チェック＆repeat処理
*    vSwitch1UserHandling() ----- switch5が押された時の本体処理
*    vSwitch7Check() ----- switch7 チェック＆repeat処理
*    vSwitch7UserHandling() ----- switch7が押された時の本体処理
*************************************************/
#define SWITCH_MENU_LIB

#include <xc.h>         // XC8 General Include File
#include "mcc_generated_files/mcc.h"
#include "vInteger.h"
#include "vSwitch_menu.h"
#include "vLED.h"
#include "vClock01.h"
#include "vBuzzer_pwm.h"

SWITCHS SW1;
SWITCHS SW2;

static unsigned char cCountDownTime = d3min;

/*****************************
*  Initialize
*****************************/
void vPushSwitch_init(void)
{
//	ANSEL  = 0x00;				// すべてデジタルに設定
//	CMCON0 = 0x07;				// コンパレータ無効化
//	GPPU   = 1;					// プルアップ無効化
//	WPU    = 0x0;				// プルアップビット指定
//	TRISIO = 0x08;				// GP3入力、他は出力設定
//	GPIO   = 0x00;				// 全てlow出力設定
	TRISIO3 = 1;				// GP3入力、他は出力設定
}

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
				SW1.OnTime++;
				break;

			case 100:					//10msec*100 wait for the first push
				//repeat
				eMenu_SW1_Status++;
				SW1.OnTime = 100 - 30; 	//10msec*30 wait for repeat
				break;

			default:
				break;
		}
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
				SW2.OnTime++;
				break;

			case 100:					//10msec*100 wait for the first push
				//repeat
				eMenu_SW2_Status++;
				SW2.OnTime = 100 - 30; 	//10msec*30 wait for repeat
				break;

			default:
				break;
		}
	}else{
		SW2.OnTime = 0;
	}
}


/*****************************
* eMenu_SW2_Status clear
*****************************/
void vModeStatusClr(void)
{
	eMenu_SW1_Status = eMenu_SW2_Start;
}

/*****************************
* Menu mode control
*****************************/
void vModeControl01(void)
{
	switch (eMenu_SW1_Status) {
		case  	eMenu_SW1_Start :
			vLEDClear();				//LED CLEAR
			vClock01_Clear();			//CLOCK 初期化

			eMenu_SW1_Status++;				//次へ進む
			break;

		case  	eMenu_SW1_Pre_CountDown :
			vClock01_Clear();				//CLOCK 初期化
			cMinCountDown = cCountDownTime;	//カウントダウンタイマ初期化
			vStopBuzzer();					//ブザーストップ
			eMenu_SW1_Status++;					//次へ進む
			break;

		case  	eMenu_SW1_CountDown :		//カウントダウン
			if (cMinCountDown <= 0) {	//Time Up
				eMenu_SW1_Status++;
			}
			vLEDOutput(cMinCountDown);
			break;

		case  	eMenu_SW1_Pre_Melody :
			vClock01_Clear();			//CLOCK 初期化
			usGakufuIchi = 0;			//楽譜位置初期化
			eMenu_SW1_Status++;
			break;

		case  	eMenu_SW1_Melody :			//音楽演奏
			vMelody01();

			if (ucMin01 > 10 && usGakufuIchi == 0) {			//音楽が10分以上経過し演奏が終わったら停止
				eMenu_SW1_Status = eMenu_SW1_Sleep;
			}

			break;

		case  	eMenu_SW1_Wait :
			//Wait
	//		vStopBuzzer();				//音楽停止
	//		vLEDClear();				//LED CLEAR
			eMenu_SW1_Status = eMenu_SW1_Sleep;
			break;

		case  	eMenu_SW1_Go_Timer_Start :
	//		vStopBuzzer();					//音楽停止
			eMenu_SW1_Status = eMenu_SW1_Start;	//先頭処理へ戻る
			break;

		// ---------------------------------------------------
		case  	eMenu_SW1_Sleep :
			vStopBuzzer();				//音楽停止
			vLEDClear();				//LED CLEAR

			IOC3	= 1;				// GPIO3の割込み許可
			GPIF	= 0;				// io_pin全体の割込みフラグのクリア
			INTERRUPT_PeripheralInterruptEnable();
			INTERRUPT_GlobalInterruptEnable();
			SLEEP();
			NOP();
			GPIF	= 0;				// io_pin全体の割込みフラグのクリア
			IOC3	= 0;				// GPIO3の割込み許可

		// wake up 時の戻り先
	//		eMenu_SW1_Status = eMenu_SW1_Start;	//先頭処理へ戻る
			eMenu_SW1_Status = eMenu_SW1_Wait;	//TimerSet処理へ戻る
			break;

		default:
			eMenu_SW1_Status = eMenu_SW1_Start;
	}

	// ---------------------------------------------------
	switch (eMenu_SW2_Status) {
		case  	eMenu_SW2_Start :
			vClock01_Clear();
			vStopBuzzer();
			switch (cCountDownTime) {
			case  	WAIT3MIN :
				eMenu_SW2_Status = eMenu_SW2_Start3min ;
			break;
			case  	WAIT5MIN :
				eMenu_SW2_Status = eMenu_SW2_Start5min ;
			break;
			case  	WAIT10MIN :
				eMenu_SW2_Status = eMenu_SW2_Start10min ;
			break;
			default:
				eMenu_SW2_Status = eMenu_SW2_Start3min ;
			}
			break;
		case  	eMenu_SW2_Start3min :
			cCountDownTime = WAIT3MIN;		//カウントダウン時間を3分に設定
			vLEDClear();				//LED CLEAR
			LED3min_ON();				//出力low
			break;

		case  	eMenu_SW2_Start5min :
			cCountDownTime = WAIT5MIN;		//カウントダウン時間を5分に設定
			vLEDClear();				//LED CLEAR
			LED5min_ON();				//出力low
			break;

		case  	eMenu_SW2_Start10min :
			cCountDownTime = WAIT10MIN;	//カウントダウン時間を10分に設定
			vLEDClear();				//LED CLEAR
			LED10min_ON();				//出力low
			break;

		case	eMenu_SW2_ReturnToSet3min:
			eMenu_SW2_Status = eMenu_SW2_Start3min;
			break;

		case	eMenu_SW2_Wait:
			break;

		default:
			eMenu_SW2_Status = eMenu_SW2_Start;
	}

}



