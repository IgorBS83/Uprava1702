#include "main.h"
#include <string.h>

Uint32 FlagCommand = 0;		//флаг команды
Uint32 DataNum = 0;			//кол-во слов данных в посылке
Uint32 DataCount = 0;		//счетчик слов данных в посылке
Uint8 ComData[31];			//флаг команды
Uint8 CheckSum = 0;			//контрольная сумма
Uint8 Comtmp;

void CommandWrite(Uint32 Answer){
	Uint8 c[14];
	Uint8 checksum = 0;
	int i;
	short y;

	if(Answer == 1)//ответное сообщение
	{
//		c[0] = 0x01;
		*ProtocolFromToAltera = 0x01;

		c[1] = Comtmp | 1;
		c[2] = c[1];

		#pragma MUST_ITERATE(2);
		for(i = 1; i < 3; i++)
			*ProtocolFromToAltera = c[i];

	}
	else//сообщение сопровождения
	{
		GpioBlink(12);

		*CoordsStrobToAltera = _dpack2(((YStrob + RowStrob - BorderRows) << 16) | (YStrob + BorderRows), ((XStrob + ColStrob - BorderCols) << 16) | (XStrob + BorderCols));
		*CoordsCenterToAltera = _dpack2(Mxy.y, Mxy.x);

		* (Uint8*)(0xA0000000 + (0x2038 << 3)) = 0xFF;
/*
		MassCorR[0][0] = tresh & 254;
		MassCorR[0][1] = (tresh >> 8) & 254;

 	 	Uint8 j, a;
		for(i = 0; i < 15; i++)
			for(j = 0; j < 25; j++)
			{
				a = (Uint8)MassCorR[i][j];
				if(a == 255) a = 254;
				* (Uint8*)(0xA0000000 + (0x2038 << 3)) = a;
			}

*/
	//	c[0] = 0x0D;
		*ProtocolFromToAltera = 0x0D;
		c[1] = (Comtmp & 0xF7) | (Capture << 4) | (Capture << 3);

		if(Capture == 0)
			for(i = 2; i <= 13; i++)
				c[i] = 0;
		else
		{
			//слова параметров
			c[2] = (ColStrob - (BorderCols << 1) - 1) >> 1;					//1
			c[3] = RowStrob - (BorderRows << 1) - 1;						//2
			y = XStrob + BorderCols + UstavX - (TvTpv * 9);
			c[4] = y & 0xFF;					//3
			c[5] = y >> 8;					//4
			y = ((YStrob + BorderRows) << 1)  + UstavY;

			if((AlgNum == 3) && ((CadrN & 1) == 1)) y -= 1;

			c[6] = y & 0xFF;						//5
			c[7] = y >> 8;							//6

			y = (short)((Mxy.x + UstavX - 360 - (TvTpv * 9)) * 32);

			c[10] = y & 0xFF;	//9
			c[11] = y >> 8;		//10

			y = (short)((Mxy.y * 2 + UstavY - 288) * 32);

			c[12] = y & 0xFF;						//11
			c[13] = y >> 8;							//12
		}
		c[8] = (CadrN - CadrMem)& 0xFF;					//7
		c[9] = (CadrN - CadrMem) >> 8;						//8

		#pragma MUST_ITERATE(13);
		for(i = 1; i < 14; i++)
		{
			*ProtocolFromToAltera = c[i];
			checksum += c[i];
		}
		*ProtocolFromToAltera = checksum;
	}
}

unsigned long long a, b, c;
unsigned short d;

interrupt void CommandRead(){

	a = *(unsigned long long*)(0xA0000000 + (0x2010 << 3));
	b = *(unsigned long long*)(0xA0000000 + (0x2011 << 3));
	c = *(unsigned long long*)(0xA0000000 + (0x2012 << 3));
	d = *(unsigned long long*)(0xA0000000 + (0x2013 << 3));
	ProtocolRdy = 1;
}

void CommandTake(){
	if(AsOn == 1)
	{
		AsOn = (c & 0x08) >> 3;
	}
	else
	{
		Comtmp = c & 0xFF;
		AlgNum = c & 0x7;
		TvTpv = (c & 0x20) >> 5;
		*MedCamToAltera = (TvTpv << 8) | (1 << 10);//твтпв | 2 поле инверсное
		AsOn = (c & 0x08) >> 3;
		Capture = 1;
		ColStrob = (b & 0xFF) << 1;
		RowStrob = b >> 8;
		XStrob = a & 0xFFFF;
		YStrob = (a >> 17) & 0xFFFF;

		UstavX = (short)((a >> 32) & 0xFFFF);
		UstavY = (short)(a >> 48);

		XStrob += UstavX;
		YStrob += (UstavY >> 1);

		if(ColStrob > 256) ColStrob = 256;
		if(RowStrob > 128) RowStrob = 128;
		if(XStrob < 0) XStrob = 0;
		if((XStrob + ColStrob) >= 720) XStrob = 720 - ColStrob - 1;

		if(YStrob < 0) YStrob = 0;
		if((YStrob + RowStrob) >= 288) YStrob = 288 - RowStrob - 1;

		CadrMem = CadrN;
		//отладочные данные
		*CoordsStrobToAltera = _dpack2(((YStrob + RowStrob) << 16) | YStrob, ((XStrob + ColStrob) << 16) | XStrob);

//		switch(AlgNum)
//		{
//		default:
//			Altera_regs_write->_00_Input_control.ARU_en = 1;
//			CorGray = (1 << 7);
//			AlgNum = 6;
//		case 1:
//		case 2:
//			Altera_regs_write->_00_Input_control.ARU_en = 0;
//			CorGray = 0;
//			break;
//		case 3:
//		case 4:
//		case 5:
//		case 6:
//			Altera_regs_write->_00_Input_control.ARU_en = 1;
//			CorGray = (1 << 7);
//			break;
//		}

//		switch(AlgNum)
//		{
//		default:
//			Altera_regs_write->_00_Input_control.ARU_en = 1;
//			CorGray = (1 << 7);
//			AlgNum = 6;
//		case 1:
//		case 2:
////			treshmult = 48;
////			*MedCamToAltera |= (1 << 0);//град в зоне
//			Altera_regs_write->_00_Input_control.ARU_en = 0;
//			CorGray = 0;
//			break;
//		case 3:
////			Altera_regs_write->_00_Input_control.ARU_en = 1;
////			*MedCamToAltera |= (1 << 6) + (1 << 5) + (1 << 2) + (1 << 1);//ару ст + мед сер + мед конт + ару
////			break;
//		case 4:
////			CorGray = (1 << 7);
//		case 5:
////			*MedCamToAltera |= (1 << 5) + (1 << 1);// мед сер + ару
////			break;
//		case 6:
//			Altera_regs_write->_00_Input_control.ARU_en = 1;
//			CorGray = (1 << 7);
////		case 7:
////			treshmult = 64;
////			*MedCamToAltera |= (1 << 5) + (1 << 2) + (1 << 1) + (1 << 0);// мед сер + мед конт + ару + град в зоне
//			break;
//		}

	//	treshmult = d >> 8;
	//	*MedCamToAltera |= (d & 255);
	//	CorGray = d & (1 << 7);

		Altera_regs_write->_00_Input_control.GrayScale_median_en = 1;
		Altera_regs_write->_00_Input_control.Contour_median_en = 1;
		Altera_regs_write->_00_Input_control.ARU_en = 1;
		CorGray = (1 << 7);

		//ответное сообщение
		if(AsOn == 0) CommandWrite(1);
	}
}


