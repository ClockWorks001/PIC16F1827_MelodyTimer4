/*************************************************
*   時間計測用ヘッダファイル
*    vClock01() ----- 時間カウントアップ
*************************************************/

/* 定数変数定義*/
#if defined vClock01_LIB
	short sSecc = 0;			// 時間計測用
	char cFlag10mSec = 0;		// 10msed時間計測用
	char cFlagSec = 0;		// 1sec時間計測用
	unsigned char ucSec01, ucMin01, ucHour01;
	char cMinCountDown;

#else
	extern short sSecc;
	extern char cFlag10mSec;
	extern char cFlagSec;
	extern unsigned char ucSec01, ucMin01, ucHour01;
	char cMinCountDown;

#endif

/*****************************
*  Prototypes
*****************************/
void vClock01_Clear();
void vClock01_interrupt();
void vClock01();

