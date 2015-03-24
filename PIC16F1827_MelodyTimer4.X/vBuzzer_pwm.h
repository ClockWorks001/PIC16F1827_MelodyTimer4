/*************************************************
*  pwm出力による buzzer制御ヘッダファイル
*    vBuzzerInit()  ----- PWM初期化
*    vBuzzerStop() ----- PWM shatdown
*    vBuzzerReStart() ----- PWM shatdown clear
*    vBeep() ----- Beep the buzzer
*************************************************/
#if !defined BUZZER_PWM_H
#define BUZZER_PWM_H
/*****************************
** 定数変数定義
*****************************/
// 楽譜 music sheet / music chart
// 音階 scale
// 音の長さ length

/*
typedef struct {
unsigned char 	ucLength, ucScale;	// 1Byte Scale(音階), 1Byte Length(長さ)
} AMELODY_FACTER;
*/
typedef union {
    unsigned short 	usAMelody;		// 2Byte data
    struct AMELODY_FACTER{
        unsigned char 	ucLength, ucScale;	// 1Byte Scale(音階), 1Byte Length(長さ)
    } F ;
} AMELODY;

typedef struct {
        unsigned short* uspMusic;
	unsigned char ucMusicPosition;		//music position
	unsigned short usLength;		// 2Byte Length(長さ)
	AMELODY uAM;
} AMELODY_DATA;

enum eMenu_Melody {
//typedef enum eMenu_Melody{
    eMenu_Melody_Start,
    eMenu_Melody_get_a_Data,
    eMenu_Melody_set_a_Beep,
    eMenu_Melody_wait_a_Tone,
    eMenu_Melody_stop,
    eMenu_Melody_End
    } EMENU_MELODY;

#if defined BUZZER_PWM_LIB
    enum eMenu_Melody eMenu_Melody_Status;
//    EMENU_MELODY eMenu_Melody_Status;
    AMELODY_DATA sAMD;

    //----------------------------------------------------------------------------------------------
    //音楽データ　Melody data -> PWM parameter cheange table

    //wavelength ratio for 2 octaves // 2オクターブ分の波長比
    const unsigned char ucOnkaiTBL[2][16] = {
            {0, 238, 225, 212, 200, 189, 178, 168, 159, 150, 142, 134, 126},
            {0, 119, 112, 106, 100, 94, 89, 84, 79, 75, 71, 67, 63}
    } ;

    //Timer Prescaler change table //オクターブからTimerのPrescaler値への変換テーブル。
    const unsigned char ucTenkaiTBL[6] = {0B100, 0B101, 0B010, 0B011, 0B000, 0B001};
    //１音の基本長さ
    #define BASIC_LENGTH	30
    #define GAP_LENGTH          7

    //----------------------------------------------------------------------------------------------
    //Music Data
    //音楽データ　ウサギのだんす　
    const unsigned short usMusicData[128]={
4108, 5380, 6156, 6660, 6156, 5636, 5388, 4868, 4364, 4868, 5388, 6148, 6668, 5380, 6160,
4108, 5380, 6156, 5380, 6156, 6660, 8460, 8964, 9484, 8452, 8972, 8452, 7180, 6660, 6160,
4108, 6148, 9484, 9476, 8972, 8452, 7180, 6660, 6156, 5380, 6156, 5380, 6156, 6660, 6160,
4108, 5380, 6156, 5380, 6156, 6660, 8460, 8964, 9484, 6148, 6668, 6148, 6668, 8964, 8464,
4112, 4112, 4112, 4112,
        0xFFFF
} ;

/*
    //音楽データ　かもめの水兵さん２
    const unsigned short usMusicData[128]={
8464,9488,10264,10760,10252,9476,8460,9476,10256,8208,10768,12560,13080,13576,13068,12548,
10764,10244,10768,8208,12552,13060,12548,10764,10244,10760,12548,10756,10252,9476,10248,
10756,10244,9484,8964,9496,8200,8460,8964,9484,10244,10764,10244,12556,10756,10248,10756,
10244,9484,8964,8472,8200,8208,8208,8208,8208,8208,8208,12304,12304,
0xFFFF
} ;
*/

/*
    //音楽データ　かもめの水兵さん１
    const unsigned short usMusicData[128]={
4368, 5392, 6168, 6664, 6156, 5380, 4364, 5380, 6160, 4112, 6672, 8464, 8984, 9480, 8972,
8452, 6668, 6148, 6672, 4112, 8456, 8964, 8452, 6668, 6148, 6664, 8452, 6660, 6156, 5380,
6152, 6660, 6148, 5388, 4868, 5400, 4104, 4364, 4868, 5388, 6148, 6668, 6148, 8460, 6660,
6152, 6660, 6148, 5388, 4868, 4376, 4104, 4112, 4112, 4112, 4112, 4112, 4112, 8208, 8208,
0xFFFF
} ;
*/

#else
    //extern unsigned char ucNagasa[];
    extern enum eMenu_Melody eMenu_Melody_Status;
    //extern EMENU_MELODY eMenu_Melody_Status;
    extern AMELODY_DATA sAMD;
#endif

/*****************************
*  プロトタイプ定義ファイル
*****************************/
//void vBuzzerStop(void);
//void vBuzzerReStart(void);
//void vBuzzerSetPWM(AMELODY_DATA* pAMD);
//char cBuzzerClearAMelodyData(AMELODY_DATA* pAMD);
//char cBuzzerGetAMelodyData(AMELODY_DATA* pAMD);
//char cBuzzerWaitALength(AMELODY_DATA* pAMD);
void vMenuForMelody(void);
unsigned char ucMusicPosition(void);

#endif //BUZZER_PWM_H
