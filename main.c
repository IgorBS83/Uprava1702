#include "main.h"

//�������

//������ �� ����������
Uint8 C10[MaxCadr];
Uint8 G10[MaxCadr];
Uint8 Cbuf[MaxCadr];
Uint8 Etalon[MaxCadr];
Uint8 Etalon1[MaxCadr];

Uint16 MassCor[(BorderRows << 1) + 1][(BorderCols << 1) + 1];
Uint16 MassCorR[(BorderRows << 1) + 1][(BorderCols << 1) + 1];

RECT stack[MaxStack];
RECT stack1[MaxStack];

BinaryZone Bz[256];

XY xy;			//���������� ������� � ������ ��������
COORDS coordsEt, coordsEt1;			//���������� ������� � ������ ������

//����������

MASS Mxy;			//���������� ������� ����
float Kkor;				//���� ���������� ������� ���������
Uint32 strobAddr; 			//����� ������� �����
Uint32 strobAddrG; 			//����� ������� �����
Uint16 CadrN = 0;			//����� ����������� ����� 0,1,2,3
Uint16 CadrMem;
Uint32 colsStEt;			//�������� � ������ �������
//Uint16 treshmult = 7;
Uint16 MaxCor, MinCor;
Uint16 NPixSeaOb;
BinaryZone EtZone;
int ObjType;
Uint32 RowStrob = 128, ColStrob = 256;	//������� ������
int XStrob = 0, YStrob = 0;	//�������� ������
short UstavX = 0, UstavY = 0;	//�������


//���������
const volatile Uint32 fields[2] = {//���� �� ������� ������ � �������
		0xD0040000,
		0xD0140000};
const Uint32 fieldsG[2] = { //���� �������� ������ �� ������� ������ � �������
		0xD0000000,
		0xD0100000};

Uint32 tresh = 1000;			//����� ��������������


//�����
volatile Uint32 CadrFinish;		//���������� ��������� �����
volatile Uint32 IntHalfCadr = 0;	//������ � ������� ���������
volatile Uint32 AsOn = 0;			//����� ������
volatile Uint32 Capture = 1, freeze = 0, failtim = 0;			//���� ��������
volatile Uint32 TvTpv = 0;		//��� ������ 0-��, 1-���
volatile Uint32 Sync = 0;		//������������� ���������
volatile Uint32 CorGray = 0;		//���������� �� ������
volatile Uint32 AlgNum;
volatile Uint32 ProtocolRdy = 0;
volatile Uint32 BinarInv = 2;
volatile Uint32 flagCopyStarted = 0;		//���� ������� EDMA

//������

Altera_regs_write_type* Altera_regs_write = (Altera_regs_write_type*)(0xA0000000 + (0x2000 << 3));
Altera_regs_read_type* Altera_regs_read = (Altera_regs_read_type*)(0xA0000000 + (0x2000 << 3));

unsigned long long  *CoordsStrobToAltera = (unsigned long long*) 0xA0010080;
unsigned long long  *CoordsCenterToAltera = (unsigned long long*) 0xA0010088;
unsigned short  *ContTreshToAltera = (Uint16*)(0xA0000000 + (0x2001 << 3));//2033
Uint32  *ContTreshToAlteraMed = (Uint32*)(0xA0000000 + (0x200D << 3));
unsigned short  *MedCamToAltera = (Uint16*)(0xA0000000 + (0x2000 << 3));//2031 0 ��� 1-��/0-���, 1 ��� ������� 1-���/0-����
extern unsigned short  *MinMaxBrt = (Uint16*)(0xA0000000 + (0x2002 << 3));
Uint8 *ProtocolFromToAltera = (Uint8*)(0xA0000000 + (0x2036 << 3));
Uint8 *ProtocolInfoFromToAltera = (Uint8*)(0xA0000000 + (0x2037 << 3));
Uint8 *SignalOff = (Uint8*)(0xA0000000 + (0x2003 << 3));
unsigned short  *StrobColsAltera = (Uint16*)(0xA0000000 + (0x200E << 3));//2031 0 ��� 1-��/0-���, 1 ��� ������� 1-���/0-����
unsigned short  *StrobRowsAltera = (Uint16*)(0xA0000000 + (0x200F << 3));//2031 0 ��� 1-��/0-���, 1 ��� ������� 1-���/0-����

//Uint32 *EMR = (Uint32*)0x02A00300;
//Uint32 *EMCR = (Uint32*)0x02A00308;

#define ArrGradN 100
Uint16 ArrGrad[ArrGradN];

volatile  Uint32 mult = 25;

void neverreturns(){

	static int tresh = 200;			//����� ��������������

	strobAddr = (Uint32)&C10;
	strobAddrG = (Uint32)&G10;

	for(;;)
	{
		TimerReset();

		tresh = ((tresh << 4) - tresh + (Altera_regs_read->_01_Gradient_Max * mult / 100)) >> 4;
		Altera_regs_write->_01_Gradient_threshold = tresh;

		if(ProtocolRdy == 1)
		{
			ProtocolRdy = 0;
			CommandTake();
		}
		if((AsOn > 0) && (*SignalOff == 0)) //��������
		{
			if(IntHalfCadr == 1)//�������� ����� ��� �����������
			{
				IntHalfCadr = 0;
				Start();
			}
			EdmaEventCheck(0);
			if(flagCopyStarted == 2)//�������� ����������
			{
				flagCopyStarted = 0;
				if(Capture == 1)
				{
					if(AlgNum == 3)	Energy();
					else
					{
						GpioSet(7, 1);
						AirCont();
						GpioSet(7, 0);
					}
				}
				if(Sync > 1) CommandWrite(0);
			}
		}
		else
		{
			GpioSet(12, 0);
			Sync = 0;
			freeze = 0;
			failtim = 0;
		}

	}
}

void delay(int delay){
	volatile int i = 0;
	while(i++ < delay);
}

int main(void) {
	delay(0x100000);

	PllInit();
	GpioInit();
	EmifaInit();
	Edma3Init();
	IntInit();
	GpioSet(6, 0);	GpioSet(7, 0);	GpioSet(12, 0);	GpioSet(13, 0);
	Timer_Init();

	Altera_regs_write->_04_1st_Bright_max = 255;
	Altera_regs_write->_05_1st_Bright_min = 225;
	Altera_regs_write->_06_2nd_Bright_max = 255;
	Altera_regs_write->_07_2nd_Bright_min = 225;

	Altera_regs_write->_0A_ARU_drop_pixels = 100;

#pragma FUNC_NEVER_RETURNS (neverreturns);
	neverreturns();
	return 0;
}
/*
void shift_average(unsigned int movingAverageArray, short size, Uint16 newGradient, unsigned int result, short isWeighted)
{
       int i, k;
       Uint32 buf;

       Uint16 * buffer = (Uint16 *) movingAverageArray;
       Uint16 * movingAverage = (Uint16 *) result;

       // ������� ������ �������� ��������� �� ���� ������
       for(i = size - 1; i > 0; i--){
             *(buffer + i) = *(buffer + i - 1);
       }

       // ��������� ����� �������� � ������� ������
       *buffer = newGradient;

       buf = 0.0;
       k = 0;

       // ���� ��������� ���������� �������
       if(isWeighted == 1){
             for(i = 0; i < size; i++){
                    buf += *(buffer + i) * (size - i);

                    if(*(buffer + i) - 0.0 < 0.000001){
                           k++;
                    }
             }

       // ���� ������ ������ size ������, � ������ ��� �� ��������
             if( k > 0 ){
                    *movingAverage = *buffer;
             }

             else{
                    // ��������� ���������
                    *movingAverage = ( 2.0 * buf ) / ( size * (size + 1) );
             }
       }

       // ���� ��������� ������� ���������� �������
       else {
             for(i = 0; i < size; i++){
                    buf += buffer[i];

                    if(buffer[i] - 0.0 > 0.000001){
                           k++;
                    }
             }
             // ��������� ���������
             *movingAverage = buf / k;
       }
}

*/
