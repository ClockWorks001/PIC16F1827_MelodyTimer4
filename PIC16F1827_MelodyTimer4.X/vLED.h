//******************************************************************************
//  LED define
//******************************************************************************

//output LED define
#define LED1_ON()		IO_RB1_SetHigh()
#define LED1_OFF()		IO_RB1_SetLow()
#define LED2_ON()		IO_RB2_SetHigh()
#define LED2_OFF()		IO_RB2_SetLow()
#define LED3_ON()		IO_RB3_SetHigh()
#define LED3_OFF()		IO_RB3_SetLow()

#define LED3min_ON()            IO_RB1_SetHigh()
#define LED3min_OFF()           IO_RB1_SetLow()
#define LED5min_ON()            IO_RB2_SetHigh()
#define LED5min_OFF()           IO_RB2_SetLow()
#define LED10min_ON()           IO_RB3_SetHigh()
#define LED10min_OFF()          IO_RB3_SetLow()
enum eMenu_LED {
    eMenu_LED_LED3min_ON,
    eMenu_LED_LED5min_ON,
    eMenu_LED_LED10min_ON,
    eMenu_LED_Melody,
    eMenu_LED_CountDown,
    eMenu_LED_ALL_OFF,
    eMenu_LED_End
    };

#if defined vLED_LIB
    enum eMenu_LED eMenu_LED_Status;

#else
	//extern unsigned char ucNagasa[];
    extern enum eMenu_LED eMenu_LED_Status;

#endif

//******************************************************************************
//  Prototype define
//******************************************************************************
//void vLEDClear(void);
//void vLED_Melody(AMELODY_DATA* pAMD);
//void vLED_CountDown(char cMinCountDownTime);
void vLEDBlink01(void);

