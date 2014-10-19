//******************************************************************************
//  LED define
//******************************************************************************

//******************************************************************************
//* User define
//******************************************************************************

//output LED define
#define LED1_ON()		IO_RB0_SetHigh()
#define LED1_OFF()		IO_RB0_SetLow()
#define LED2_ON()		IO_RB1_SetHigh()
#define LED2_OFF()		IO_RB1_SetLow()
#define LED3_ON()		IO_RB2_SetHigh()
#define LED3_OFF()		IO_RB2_SetLow()

#define LED3min_ON()            IO_RB0_SetHigh()
#define LED3min_OFF()           IO_RB0_SetLow()
#define LED5min_ON()            IO_RB1_SetHigh()
#define LED5min_OFF()           IO_RB1_SetLow()
#define LED10min_ON()           IO_RB2_SetHigh()
#define LED10min_OFF()          IO_RB2_SetLow()

//#define d3min		3	//wait time
//#define d5min		5	//wait time
//#define d10min		10	//wait time

//******************************************************************************
//  Prototype define
//******************************************************************************
void vLEDClear(void);
void vLEDOutput(char cMinTime);

