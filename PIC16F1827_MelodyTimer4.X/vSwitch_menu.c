/*************************************************
*  Switch_Menu
*    Switch1 is status for Main routin.
*    Switch2 is status for Timer setting.
*************************************************/
#define SWITCH_MENU_LIB

#include <xc.h>         // XC8 General Include File
#include "mcc_generated_files/mcc.h"
#include "vClock01.h"
#include "vLED.h"
#include "vSwitch_menu.h"
#include "vBuzzer_pwm.h"

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

                        case 100:                       //10msec*100 wait for the first push
                                //repeat
                                eMenu_SW1_Status++;
                                SW1.OnTime = 100 - 30;  //10msec*30 wait for repeat
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

                        case 100:                       //10msec*100 wait for the first push
                                //repeat
                                eMenu_SW2_Status++;
                                SW2.OnTime = 100 - 30;  //10msec*30 wait for repeat
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
* Melody stop
*****************************/
void vMelodyStop(void)
{
    eMenu_Melody_Status = eMenu_Melody_stop;
    eMenu_LED_Status = eMenu_LED_ALL_OFF;
}


/*****************************
* Menu for SW1
*****************************/
void vMenuForSW1(void)
{
        switch (eMenu_SW1_Status) {
                case    eMenu_SW1_Start :
                        eMenu_SW2_Status = eMenu_SW2_Wait;
                        vMelodyStop();
                        vClock01_Clear();
                        vSetMinCountDownTime(cCountDownTime); //clear the CountDown variable. カウントダウンタイマ初期化
                        eMenu_SW1_Status++;
                        break;

                case    eMenu_SW1_CountDown :
//                        if (cGetMinCountDownTime() <= 0) {   //IF Time is up
                        if (cIsMinCountDownTimeZero()) {       //IF Time is up
                            eMenu_SW1_Status++;
                        }
                        eMenu_LED_Status = eMenu_LED_CountDown;

                        break;

                case    eMenu_SW1_MelodyStart :              //play a melody
                        eMenu_Melody_Status = eMenu_Melody_Start;
                        eMenu_LED_Status = eMenu_LED_Melody;
                        vClock01_Clear();                   //countdown start for sleep
                        eMenu_SW1_Status++;
                        break;
                case    eMenu_SW1_MelodyPlay :              //playing a melody
                        if (ucGetMin01() >= 5 && ucMusicPosition() == 0) {        //音楽が5分以上経過し演奏が終わったら停止
                                eMenu_SW1_Status = eMenu_SW1_Sleep;
                        }
                        break;

                // ---------------------------------------------------
                case    eMenu_SW1_Wait :
                        vMelodyStop();
                        vClock01_Clear();                   //countdown start for sleep
                        eMenu_SW1_Status++;
                        break;
                case    eMenu_SW1_Wait2 :
                        // sleep判定を入れる
                        if (ucGetMin01() >= 1 ) {        //1分以上経過したら停止
                                eMenu_SW1_Status = eMenu_SW1_Sleep;
                        }
                        break;
                case    eMenu_SW1_ReturnToStart :
                        eMenu_SW1_Status = eMenu_SW1_Start;
                        break;

                // ---------------------------------------------------
                case    eMenu_SW1_Sleep :
                        vMelodyStop();
                        eMenu_SW2_Status = eMenu_SW2_Wait;
                        eMenu_SW1_Status++;
                        break;

                case    eMenu_SW1_Sleep2 :
//                        INTERRUPT_PeripheralInterruptEnable();
//                        INTERRUPT_GlobalInterruptEnable();
                        TMR1_StopTimer();
                        TMR2_StopTimer();
                        INTCONbits.INTF = 0;
                        INTCONbits.INTE = 1;
//                        INTCONbits.IOCIF = 0;
//                        INTCONbits.IOCIE = 1; //INTERRUPT-ON-CHANGE needs system clock. It can't wake up from sleep.
//                        IOCBPbits.IOCBP0 = 1;
//                        IOCBNbits.IOCBN0 = 1;

                        SLEEP();
                        NOP();
                        INTCONbits.INTF = 0;
                        INTCONbits.INTE = 0;
//                        IOCBFbits.IOCBF0 = 0;
//                        INTCONbits.IOCIF = 0;
//                        INTCONbits.IOCIE = 0;
                        TMR1_StartTimer();
                        TMR2_StartTimer();
//
                // wake up 時の戻り先
                        eMenu_SW1_Status = eMenu_SW1_Start;
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
                case    eMenu_SW2_Start :
                        eMenu_SW1_Status = eMenu_SW1_Wait;
                        vMelodyStop();
                        vClock01_Clear();
                        switch (cCountDownTime) {
                        case    WAIT3MIN :
                                eMenu_SW2_Status = eMenu_SW2_Set3min ;
                            break;
                        case    WAIT5MIN :
                                eMenu_SW2_Status = eMenu_SW2_Set5min ;
                            break;
                        case    WAIT10MIN :
                                eMenu_SW2_Status = eMenu_SW2_Set10min ;
                            break;
                        default:
                                eMenu_SW2_Status = eMenu_SW2_Set3min ;
                        }
//                        eMenu_SW2_Status++;
                        break;
                case    eMenu_SW2_Set3min :
                        cCountDownTime = WAIT3MIN;              //カウントダウン時間を3分に設定
                        eMenu_LED_Status = eMenu_LED_LED3min_ON;
                        break;

                case    eMenu_SW2_Set5min :
                        cCountDownTime = WAIT5MIN;              //カウントダウン時間を5分に設定
                        eMenu_LED_Status = eMenu_LED_LED5min_ON;
                        break;

                case    eMenu_SW2_Set10min :
                        cCountDownTime = WAIT10MIN;     //カウントダウン時間を10分に設定
                        eMenu_LED_Status = eMenu_LED_LED10min_ON;
                        break;

                case    eMenu_SW2_ReturnToSet3min:
                        eMenu_SW2_Status = eMenu_SW2_Set3min;
                        break;

                case    eMenu_SW2_Wait:
                        break;

                case    eMenu_SW2_End:
                default:
                        eMenu_SW2_Status = eMenu_SW2_Start;
        }

}



