/*************************************************
*  Switch_Menu処理ヘッダファイル
*    vSwitch1Check() ----- switch5 チェック＆repeat処理
*    vSwitch1UserHandling() ----- switch5が押された時のユーザ処理を記述する
*    char cSwitch1ON() ----- switch5の状態を返信する。フラグをクリアする。
*    vSwitch7Check() ----- switch7 チェック＆repeat処理
*    vSwitch7UserHandling() ----- switch5が押された時のユーザ処理を記述する
*************************************************/

#include "vInteger.h"

//******************************************************************************
//  User define
//******************************************************************************

//pushbuttons define
#define SW1_ON		IO_RA4_GetValue() == 0
#define SW1_OFF		IO_RA4_GetValue() == 1
#define SW2_ON		IO_RA5_GetValue() == 0
#define SW2_OFF		IO_RA5_GetValue() == 1

//#define SWITCH_ON 		1
//#define SWITCH_OFF 		0

//******************************************************************************
//  Propertis
//******************************************************************************
typedef struct {
	WORD  OnTime;
//	BYTE  flag = 0;
} SWITCHS;

#if defined SWITCH_MENU_LIB
	enum eMenu_SW1 {
		eMenu_SW1_Start,
			eMenu_SW1_Pre_CountDown,
			eMenu_SW1_CountDown,
			eMenu_SW1_Pre_Melody,
			eMenu_SW1_Melody,
			eMenu_SW1_Wait,
			eMenu_SW1_Go_Timer_Start,

		eMenu_SW1_Sleep,
		eMenu_SW1_End
		};
	enum eMenu_SW1 eMenu_SW1_Status;

	enum eMenu_SW2 {
		eMenu_SW2_Start,
			eMenu_SW2_Set3min,
			eMenu_SW2_Set5min,
			eMenu_SW2_Set10min,
			eMenu_SW2_ReturnToSet3min,
			eMenu_SW2_Wait,
		eMenu_SW2_End
		};
	enum eMenu_SW2 eMenu_SW2_Status;

#else
	//extern char ucTestCount = 0;
#endif


//******************************************************************************
//  Prototype define
//******************************************************************************
void vSwitch1Check(void);
void vSwitch1UserHandling(void);
char cSwitch1ON(void);

void vSwitch2Check(void);
void vSwitch2UserHandling(void);
char cSwitch2ON(void);

void vModeControl01(void);
//void vModeStatusClr(void);


