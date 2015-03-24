/*************************************************
*  Switch_Menu処理ヘッダファイル
*************************************************/
#if !defined SWITCH_MENU_H
#define SWITCH_MENU_H

#include "vInteger.h"

//******************************************************************************
//  User define
//******************************************************************************

//pushbuttons define
#define SW1_ON		IO_RB0_GetValue() == 0
#define SW1_OFF		IO_RB0_GetValue() == 1
#define SW2_ON		IO_RA4_GetValue() == 0
#define SW2_OFF		IO_RA4_GetValue() == 1

//#define SWITCH_ON 		1
//#define SWITCH_OFF 		0

//******************************************************************************
//  Propertis
//******************************************************************************
typedef struct {
	WORD  OnTime;
//	BYTE  flag = 0;
} SWITCHS;
enum eMenu_SW1 {
        eMenu_SW1_Start,
        eMenu_SW1_CountDown,
        eMenu_SW1_MelodyStart,
        eMenu_SW1_MelodyPlay,
        eMenu_SW1_Wait,
        eMenu_SW1_Wait2,
        eMenu_SW1_ReturnToStart,
        eMenu_SW1_Sleep,
        eMenu_SW1_Sleep2,
        eMenu_SW1_End
        };
enum eMenu_SW2 {
        eMenu_SW2_Start,
        eMenu_SW2_Set3min,
        eMenu_SW2_Set5min,
        eMenu_SW2_Set10min,
        eMenu_SW2_ReturnToSet3min,
        eMenu_SW2_Wait,
        eMenu_SW2_End
        };

#if defined SWITCH_MENU_LIB
	enum eMenu_SW1 eMenu_SW1_Status;
	enum eMenu_SW2 eMenu_SW2_Status;

#else
	//extern char ucTestCount = 0;
#endif


//******************************************************************************
//  Prototype define
//******************************************************************************
void vSW1_Check(void);
void vSW2_Check(void);

void vMenuForSW1(void);          // time count down
void vMenuForSW2(void);          // time setting
//void vModeStatusClr(void);

#endif //SWITCH_MENU_H

