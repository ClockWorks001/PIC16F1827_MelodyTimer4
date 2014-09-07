/*************************************************
*  Switch_Menu処理ヘッダファイル
*    vPushSwitch_init()  ----- 初期化
*    vSwitch1Check() ----- switch5 チェック＆repeat処理
*    vSwitch1UserHandling() ----- switch5が押された時のユーザ処理を記述する
*    char cSwitch1ON() ----- switch5の状態を返信する。フラグをクリアする。
*    vSwitch7Check() ----- switch7 チェック＆repeat処理
*    vSwitch7UserHandling() ----- switch5が押された時のユーザ処理を記述する
*************************************************/


//******************************************************************************
//  User define
//******************************************************************************

//pushbuttons define
#define SW1_ON		IO_RA4_GetValue() == 0
#define SW1_OFF		IO_RA4_GetValue() == 1
#define SW2_ON		IO_RA5_GetValue() == 0
#define SW2_OFF		IO_RA5_GetValue() == 1

#define SWITCH_ON 		1
#define SWITCH_OFF 		0


#define 3MIN			3	//wait time
#define 5MIN			5	//wait time
#define 10MIN			10	//wait time

//******************************************************************************
//  Propertis
//******************************************************************************
typedef struct {
	WORD  OnTime = 0;
//	BYTE  flag = 0;
} SWITCHS;

#if defined SWITCH_MENU_LIB
	enum eMenu_SW1 {
		eMenu_SW1_Timer,
			eMenu_SW1_Pre_CountDown,
			eMenu_SW1_CountDown,
			eMenu_SW1_Pre_Melody,
			eMenu_SW1_Melody,
			eMenu_SW1_Wait,
			eMenu_SW1_Go_Timer_Start,

		eMenu_SW1_Sleep,
		eMenu_SW1_end
		};
	enum eMenu_SW1 eMenu_SW1_status;

	enum eMenu_SW2 {
		eMenu_SW2_TimeSet,
			eMenu_sw2_TimeSet3min,
			eMenu_sw2_TimeSet5min,
			eMenu_sw2_TimeSet10min,
			eMenu_sw2_ReturnToSet3min,
			eMenu_sw2_wait,
			eMenu_sw2_end
		};
	enum eMenu_SW2 eMenu_SW2_status;

#else
	//extern char ucTestCount = 0;
#endif


//******************************************************************************
//  Prototype define
//******************************************************************************
void vPushSwitch_init(void);
void vSwitch1Check(void);
void vSwitch1UserHandling(void);
char cSwitch1ON(void);

void vSwitch2Check(void);
void vSwitch2UserHandling(void);
char cSwitch2ON(void);

void vModeControl01(void);
void vModeStatusClr(void);


