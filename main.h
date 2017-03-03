#ifndef PARAMS_H_

typedef unsigned int Uint32;
typedef unsigned short Uint16;
typedef unsigned char Uint8;

typedef struct {
    short x;
    short y;
    short cols;
    short rows;
} COORDS;

typedef struct {
    short x;
    short y;
} XY;

typedef struct {
	float x;
	float y;
} MASS;

typedef struct {
    Uint16 NumPix;
	Uint8  Color;
	Uint8  Num;
    Uint32 SumBright;
    Uint16 left;
    Uint16 up;
    Uint16 right;
    Uint16 down;
    Uint32 SumBrightX;
    Uint32 InvSumBrightX;
    Uint32 SumBrightY;
    Uint32 InvSumBrightY;
}
BinaryZone;

typedef struct {
	Uint16 j;
	Uint16 i;
	Uint16 def;
}
RECT;

//ФУНКЦИИ
//GPIO
extern int GpioInit();
extern int GpioBlink(int);
extern int GpioSet(int, Uint16);
//EDMA
extern void EdmaEventCheck(Uint32);
extern int Edma3Init();
extern void R1(Uint32, Uint32, Uint16, Uint16, Uint16, Uint16);
extern void R6(Uint32, Uint32, Uint16, Uint16, Uint16, Uint16);
//ПРОТОКОЛ
extern void CommandWrite(Uint32);
extern void InterpretCom();
extern interrupt void CommandRead();
extern void CommandTake();

//СИСТЕМНЫЕ ФУНКЦИИ
extern void IntInit();
extern int EmifaInit();
extern void PllInit();
extern void Timer_Init();
extern void TimerReset();

//АЛГОРИТМЫ
extern void Start();
extern int Energy();
extern void Color();
extern void AirCont();
extern void shift_average(unsigned int, short, Uint16, unsigned int, short);
extern void CheckStrobe(unsigned int, short, short, short, short , short, short, unsigned int);
extern inline Uint32 checkLine(Uint8 * strobPtr, Uint32 stWidth, Uint32 stHeight, float k, float b, Uint32 eth, Uint8 mode, Uint16 lVal, Uint16 rVal);
extern Uint16 horizonFilter(Uint8 * strobPtr, Uint32 stWidth, Uint32 stHeight, Uint32 eth, Uint16 avgH);
extern int CleanMemory(Uint32, Uint32);

//мин и макс возможные размеры эталона
#define BorderCols 	16
#define BorderRows 	8
#define RowMin 		5
#define RowMax 		128
#define ColMin		10
#define ColMax		256
#define FrameCols   720


#define MaxStack 	0x400
#define MaxCadr 	0x10000//(ColMax + (BorderCols << 1) + 1) * (RowMax + (BorderRows << 1) + 1)

//МАССИВЫ
//стробы по полукадрам
extern Uint8 C10[MaxCadr];
extern Uint8 G10[MaxCadr];
extern Uint8 Cbuf[MaxCadr];
extern Uint8 Etalon[MaxCadr];
extern Uint8 Etalon1[MaxCadr];
extern RECT stack[MaxStack];
extern RECT stack1[MaxStack];
extern BinaryZone Bz[256];


extern XY xy;			//координаты эталона в стробе нечетный
extern COORDS coordsEt, coordsEt1;


extern Uint16 MassCor[BorderRows * 2 + 1][BorderCols * 2 + 1];
extern Uint16 MassCorR[BorderRows * 2 + 1][BorderCols * 2 + 1];

//ПЕРЕМЕННЫЕ
extern Uint32 RowStrob, ColStrob;	//размеры строба
extern int XStrob, YStrob;			//смещение строба
extern MASS Mxy;			//координаты центров масс
extern Uint32 colsStEt;			//столбцов в стробе эталоне
extern Uint32 tresh;			//порог контурирования
extern float Kkor;					//коэф корреляции полукадра
extern Uint32 strobAddr; 			//адрес текущий строб
extern Uint32 strobAddrG; 			//адрес текущий строб
extern Uint16 CadrN;				//номер полученного кадра
extern Uint16 CadrMem;
//extern Uint16 treshmult;
extern Uint16 MaxCor, MinCor;
extern Uint16 NPixSeaOb;
extern BinaryZone EtZone;
extern int ObjType;


//КОНСТАНТЫ
extern short UstavX, UstavY;	//уставка
extern const volatile Uint32 fields[2]; //поля во внешней памяти с кадрами
extern const Uint32 fieldsG[2]; //поля градаций серого во внешней памяти с кадрами

//АДРЕСА

typedef struct{
	int Strob_is_calculation_area	:1;
	int ARU_en						:1;
	int Contour_median_en			:1;
	int Errosion_and_Delatation_en	:1;
	int Strob_is_output_area		:1;
	int GrayScale_median_en			:1;
	int ARU_in_Strob_en				:1;
	int res2						:1;
	int TPV_en						:1;
	int Invert_1st_channel			:1;
	int Invert_2nd_channel			:1;
	int res0 						:21;
	int res1;
}
Altera_Input_control_type;

typedef struct{
	Uint8 min;
	Uint8 max;
	short res0;
	int res1;
}
Altera_Zone_Count_type;

typedef struct{
	Uint32 rx_422_rdy :1;
	Uint32 rx_232_rdy :1;
	Uint32 rx_com_rdy :1;
	Uint32 rx_usb_rdy :1;
	Uint32 tx_422_full :1;
	Uint32 tx_232_full :1;
	Uint32 tx_com_full :1;
	Uint32 tx_usb_full :1;
	Uint8 r0;
	Uint16 r1;
	Uint32 r2;
}
Altera_ports_type;

typedef struct {
	Altera_Input_control_type _00_Input_control;
	unsigned long long _01_Gradient_threshold;
	unsigned long long r02_03[2];
	unsigned long long _04_1st_Bright_max;//зоны чет кадр
	unsigned long long _05_1st_Bright_min;//зоны нечет
	unsigned long long _06_2nd_Bright_max;
	unsigned long long _07_2nd_Bright_min;
	unsigned long long r08_09[2];
	unsigned long long _0A_ARU_drop_pixels;
	unsigned long long r0b_0f[5];
	unsigned long long _10_Strob_Coords;
	unsigned long long _11_Target_Center;
	unsigned long long r12_33[0x22];
	unsigned long long _34_port_rs422;
	unsigned long long _35_port_rs232;
	unsigned long long _36_port_com;
	unsigned long long r37;
	unsigned long long _38_port_usb;
}
Altera_regs_write_type;

typedef struct {
	unsigned long long r0;
	unsigned long long _01_Gradient_Max;
	unsigned long long r2;
	unsigned long long _03_No_TV_Signal;
	Altera_Zone_Count_type _04_1st_zone_count_even;//зоны чет кадр
	Altera_Zone_Count_type _05_1st_zone_count_odd;//зоны нечет
	Altera_Zone_Count_type _06_2nd_zone_count_even;
	Altera_Zone_Count_type _07_2nd_zone_count_odd;
	unsigned long long r08_09[2];
	Altera_Zone_Count_type _0A_contour_zone_count;//число зон в контуре
	unsigned long long rb;
	unsigned long long _0C_Cadr_counter;
	unsigned long long _0D_Gradient_Sum;
	unsigned long long _0E_Gradient_Sum_Area_columns;
	unsigned long long _0F_Gradient_Sum_Area_rows;
	unsigned long long r10_33[0x24];
	unsigned long long _34_port_rs422;
	unsigned long long _35_port_rs232;
	unsigned long long _36_port_com;
	Altera_ports_type _37_ports_info;
	unsigned long long _38_port_usb;
}
Altera_regs_read_type;

extern Altera_regs_write_type* Altera_regs_write;
extern Altera_regs_read_type* Altera_regs_read;

extern unsigned long long *CoordsStrobToAltera;
extern unsigned long long  *CoordsCenterToAltera;
extern unsigned short  *ContTreshToAltera;
extern unsigned short  *MedCamToAltera;
extern unsigned short  *MinMaxBrt;
extern Uint8 *ProtocolFromToAltera;
extern Uint8 *ProtocolInfoFromToAltera;

#define CadrInfoAddr (Uint16*)(0xA0000000 + (0x200C << 3));//адрес данных о кадре

//ФЛАГИ
extern volatile Uint32 Sync;		//синхронизация полукадра
extern volatile Uint32 IntHalfCadr;	//сигнал о приходе полукадра
extern volatile Uint32 AsOn;		//включение автосопровождения
extern volatile Uint32 Capture, freeze, failtim;			//цель потеряна
extern volatile Uint32 TvTpv;		//тип камеры 0-тв, 1-тпв
extern volatile Uint32 CadrFinish;	//завершение обработки кадра
extern volatile Uint32 CorGray;		//синхронизация полукадра
extern volatile Uint32 AlgNum;
extern volatile Uint32 ProtocolRdy;
extern volatile Uint32 BinarInv;
extern volatile Uint32 flagCopyStarted;		//флаг запуска EDMA




#endif
