/*************************************************
*  Making music module by PWM
*************************************************/
#define BUZZER_PWM_LIB

#include <xc.h>         // XC8 General Include File
#include "mcc_generated_files/mcc.h"
#include "vBuzzer_pwm.h"

/*******************************
*  stop buzzer
*******************************/
void vBuzzerStop(void)
{
    // CCP2M P2AP2Chi_P2BP2Dhi; P2M halfbridge; DC2B 16;
    CCP2CON = 0x00;     // PWM clear
    PORTAbits.RA6= 0;   // PWM output pin is low
    PORTAbits.RA7= 0;   // PWM output pin is low
    TMR2_StopTimer();	// Timer2 stop
}

/*******************************
*  restart buzzer
*******************************/
void vBuzzerReStart(void)
{
    EPWM2_Initialize();     // PWM initialize
    TMR2_StartTimer();		// Timer2 start
}

/*******************************
*  vBuzzerSetPWM
*******************************/
unsigned char ucTenkai, ucOnkaiNum;
void vBuzzerSetPWM(AMELODY_DATA* pAMD)
{
    ucTenkai = ucTenkaiTBL[(pAMD->uAM.F.ucScale >> 4) & 0b00000111];
    ucOnkaiNum = pAMD->uAM.F.ucScale & 0b00001111;

    if(ucOnkaiNum == 0){
        vBuzzerStop();			//PWM_OFF
    }else{
        T2CONbits.T2CKPS = (ucTenkai >> 1);
        PR2 = ucOnkaiTBL[ucTenkai & 0b00000001][ucOnkaiNum] - 1;
        CCPR2L	= PR2 / 2;		//rate 50%
//		CCPR2H	= 0x00;
        vBuzzerReStart();
    }
}

/*******************************
*  cSetAMusicData01
*******************************/
char cSelectAMusicData01(AMELODY_DATA* pAMD)
{
    pAMD->uspMusic =  (unsigned short *) usMusicData;
	return 0;
}
/*******************************
*  cBuzzerClearAMelodyData
*******************************/
char cBuzzerClearAMelodyData(AMELODY_DATA* pAMD)
{
    pAMD->ucMusicPosition = 0;
    pAMD->uAM.usAMelody = usMusicData[pAMD->ucMusicPosition];
    vBuzzerReStart();
	return 0;
}

/*******************************
*  cBuzzerGetAMelodyData
*   return: 1:Playing 0:End of Music
*   input : AMELODY_DATA
*   output: return, AMELODY_DATA
*******************************/
char cBuzzerGetAMelodyData(AMELODY_DATA* pAMD)
{
//    pAMD->uAM.usAMelody = usMusicData[pAMD->ucMusicPosition];
    pAMD->uAM.usAMelody = *(pAMD->uspMusic + pAMD->ucMusicPosition );
    pAMD->usLength = pAMD->uAM.F.ucLength * BASIC_LENGTH;
    pAMD->ucMusicPosition ++;
	if(pAMD->uAM.usAMelody == 0xFFFF){
		return 0;
	} else {
		return 1;
	}
}

/*******************************
*  cBuzzerWaitALength
*   return: 1:Waiting 0:End of Length
*   input : AMUUSICDATA
*   output: return, AMELODY_DATA
*******************************/
char cBuzzerWaitALength(AMELODY_DATA* pAMD)
{
    pAMD->usLength--;
	if(pAMD->usLength == 0){
		return 0;
	} else if(pAMD->usLength <= GAP_LENGTH) { //音の切れ目を作る
		vBuzzerStop();			//PWM_OFF
		return 1;
	} else {
		return 1;
	}
}

/*******************************
*  vMenuForMelody
*   return: -
*   input : -
*   output: Melody
*******************************/
void vMenuForMelody(void)
{
    switch (eMenu_Melody_Status) {

        case    eMenu_Melody_Start :
                cSelectAMusicData01(&sAMD);               //select a music.
                cBuzzerClearAMelodyData(&sAMD);        //set start point of a Melody data.
                eMenu_Melody_Status++;
                break;

    //Play melody loop start from here------------------------------
        case    eMenu_Melody_get_a_Data :               // get a Melody data
                if(cBuzzerGetAMelodyData(&sAMD)){
                    eMenu_Melody_Status++;
                }else{
                    eMenu_Melody_Status=eMenu_Melody_Start;
                }
//                            vLEDBlink01();
                break;

        case    eMenu_Melody_set_a_Beep :               //set a scale to a PWM peripheral
                vBuzzerSetPWM(&sAMD);
                eMenu_Melody_Status++;
                break;

        case    eMenu_Melody_wait_a_Tone :               //wait a melody longth
                if(cBuzzerWaitALength(&sAMD)){
                    //wait!
                }else{
                    eMenu_Melody_Status=eMenu_Melody_get_a_Data;
                }
                break;
    //Play melody loop end------------------------------------------
        case    eMenu_Melody_stop :               //wait a musical note
            vBuzzerStop();
    //            eMenu_Melody_Status = eMenu_Melody_get_a_Data;
                break;
        default:
                eMenu_Melody_Status = eMenu_Melody_Start;
    }

}

/*******************************
*  ucMusicPosition
*   return: ucMusicPosition
*******************************/
unsigned char ucMusicPosition(void)
{
    return (sAMD.ucMusicPosition);
}
