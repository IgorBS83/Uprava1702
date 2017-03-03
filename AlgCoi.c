#include "main.h"
#include "Corr.h"
#include <string.h>
#include <MathFuncs.h>

int EtalonCorrect(Uint8*, Uint32, Uint32);
XY CorrParts(Uint32, Uint32, Uint32, Uint32, float*, Uint32, Uint32);
void TakeEt();

void EtCopy(Uint8* src, Uint8* dst, short cols, short rows)
{
	int i, n = (cols * rows) >> 3;
	for(i = 0; i < n; i++, src += 8, dst += 8)
		_mem8(dst) = _mem8(src);
}

void EtCopy1(Uint8* src, Uint8* dst)
{
	short i, j, i1, j1, i2, j2;
	for(i = 0, i1 = 0, i2 = coordsEt.y * ColStrob; i < coordsEt.rows; i++, i1 += coordsEt.cols, i2 += ColStrob)
		for(j = 0, j1 = 0, j2 = coordsEt.x; j < coordsEt.cols; j++, j1++, j2++)
			dst[i1 + j1] = src[i2 + j2];

}

const float porog_0_90 = 255 * (1 - 0.9);
const float porog_0_65 = 255 * (1 - 0.65);
const float porog_0_40 = 255 * (1 - 0.40);

short dx, dy;
int horizonX2, horizonX1, horizonX, horizonXavg;
int d1, d2, d3;


void AirCont()
{
	static BinaryZone Curr_zone;
	int takeEt;
	if(Sync < 2)//начало работы, первы кадр
	{
		if((CadrN & 3) == 0) Sync ++;
		if(Sync > 1)
		{
			switch(AlgNum)
			{
			case 1://air
				findObj((Uint8*)strobAddr, RowStrob, ColStrob, (Uint32)&coordsEt);
				break;
			case 2://sea
//				haf(strobAddr, ColStrob, RowStrob, 255);
				//findObj4((Uint8*) strobAddr, RowStrob, ColStrob, (BinaryZone*) &Bz, (RECT*) &stack1, (RECT*) &stack, MaxStack, (Uint32)&NPixSeaOb);
				FourSv((Uint8*)strobAddr, RowStrob, ColStrob);
				coordsEt.cols = ColStrob;
				coordsEt.rows = RowStrob;
				coordsEt.x = 0;
				coordsEt.y = 0;
				EtCopy1((Uint8*)strobAddr, Etalon1);
				CheckStrobe((Uint32)&Etalon1, ColStrob, RowStrob, ColMin, RowMin, ColMax, RowMax, (Uint32)&coordsEt);
				break;
			case 4:
				coordsEt.cols = ColStrob;
				coordsEt.rows = RowStrob;
				coordsEt.x = 0;
				coordsEt.y = 0;
				break;
			case 5:
				EtZone = findObjPerim(G10 , Cbuf, ColStrob, RowStrob, Bz, stack , stack1, 1, Sync++);
				if(EtZone.NumPix > 0)
				{
					coordsEt.cols = EtZone.right - EtZone.left + 1;
					coordsEt.rows = EtZone.down - EtZone.up + 1;
					coordsEt.x = EtZone.left;
					coordsEt.y = EtZone.up;
				}
				else Capture = 0;
				break;
			case 6:
			case 7:
				haf(strobAddr, ColStrob, RowStrob, 255);
				findObj((Uint8*)strobAddr, RowStrob, ColStrob, (Uint32)&coordsEt);
				break;
			}

			colsStEt = ColStrob;
			EtCopy((Uint8*)(CorGray == 0 ? strobAddr : strobAddrG), Etalon, ColStrob, RowStrob);

			if(coordsEt.cols > ColMax) coordsEt.cols = ColMax;
			if(coordsEt.rows > RowMax) coordsEt.rows = RowMax;
			if(coordsEt.cols < ColMin) coordsEt.cols = ColMin;
			if(coordsEt.rows < RowMin) coordsEt.rows = RowMin;

			XStrob += coordsEt.x - BorderCols;
			if(XStrob < 0) XStrob = 0;

			YStrob += coordsEt.y - BorderRows;
			if(YStrob < 0) YStrob = 0;

			RowStrob = coordsEt.rows + (BorderRows << 1);
			ColStrob = coordsEt.cols + (BorderCols << 1);
		}
	}
	else
	{
		if(AlgNum >= 6) haf(strobAddr, ColStrob, RowStrob, 255);
//		if(AlgNum == 2) findObj4((Uint8*) strobAddr, RowStrob, ColStrob, (BinaryZone*) &Bz, (RECT*) &stack1, (RECT*) &stack, MaxStack, (Uint32)&NPixSeaOb);
		if(AlgNum == 2)	FourSv((Uint8*)strobAddr, RowStrob, ColStrob);
		if(AlgNum != 5 && AlgNum != 7)	xy = CorrParts(coordsEt.x, coordsEt.y, (Uint32)&Etalon, (CorGray == 0 ? strobAddr : strobAddrG), (float*)&Kkor, (Uint32)&coordsEt, colsStEt);

		switch(AlgNum)
		{
		case 1://air
			if (Kkor < porog_0_65)
			{
				coordsEt.x = xy.x;
				coordsEt.y = xy.y;
				EtalonCorrect((Uint8*)strobAddr,  (Uint32)&coordsEt, colsStEt);
				TakeEt();
			}
			else Capture = 0;
			break;
		case 2://sea
			takeEt = 0;
			if(Kkor < porog_0_65)
			{
				if(freeze++ > 25 || failtim > 0) takeEt = 1;
				failtim = 0;
			}
			if(Kkor > porog_0_40)
			{
				freeze = 0;
				if(failtim++ > 250) Capture = 0;
			}
			if(Kkor <= porog_0_40 && Kkor >= porog_0_65 && failtim == 0) takeEt = 1;
			if(takeEt == 1)
			{
				failtim = 0;
				freeze = 0;
				coordsEt.x = xy.x;
				coordsEt.y = xy.y;

				EtCopy1((Uint8*)strobAddr, Etalon1);

				coordsEt1.cols = coordsEt.cols;
				coordsEt1.rows = coordsEt.rows;
				coordsEt1.x = 0;
				coordsEt1.y = 0;

/*

				if(horizonX1 != 0 && horizonX2 != 0 && horizonX != 0){
					d1 = abs(horizonX2 - horizonX1);
					d2 = abs(horizonX2 - horizonX);
					d3 = abs(horizonX1 - horizonX);

					horizonXavg = d1 < d2 ? (d1 < d3 ? (horizonX2 + horizonX1) / 2.0 : (horizonX1 + horizonX) / 2.0) :
						(d2 < d3 ? (horizonX2 + horizonX) / 2.0 : (horizonX1 + horizonX) / 2.0);

				}
				else{
					horizonXavg = 0;
				}

				horizonX2 = horizonX1;
				horizonX1 = horizonX;

				horizonX = horizonFilter((Uint8*)strobAddr, ColStrob, RowStrob, (Uint32)&coordsEt, (Uint16) horizonXavg);
*/

				CheckStrobe((Uint32)&Etalon1, coordsEt.cols, coordsEt.rows, ColMin, RowMin, ColMax, RowMax, (Uint32)&coordsEt1);

				dx = coordsEt.x + coordsEt1.x;
				dy = coordsEt.y + coordsEt1.y;

				if(dx >= 0){
					coordsEt.x += coordsEt1.x;
				} else{
					coordsEt.x = 0;
				}

				if(dx + coordsEt1.cols < ColStrob){
					coordsEt.cols = coordsEt1.cols;
				}
				else{
					coordsEt.cols = ColStrob - 1;
				}

				if(dy >= 0){
					coordsEt.y += coordsEt1.y;
				}
				else{
					coordsEt.y = 0;
				}

				if(dy + coordsEt1.rows < RowStrob){
					coordsEt.rows = coordsEt1.rows;
				}
				else{
					coordsEt.rows = RowStrob - 1;
				}

				/*if(coordsEt1.x >= 0 && coordsEt1.x < ColStrob
						&& coordsEt1.y >= 0 && coordsEt1.y < RowStrob
						&& coordsEt1.cols > 0 && coordsEt1.rows > 0
						&& coordsEt1.cols <= ColStrob && coordsEt1.rows <= RowStrob
						&& coordsEt1.x + coordsEt1.cols < ColStrob
						&& coordsEt1.y + coordsEt1.rows < RowStrob)
				{
					coordsEt.x += coordsEt1.x;
					coordsEt.y += coordsEt1.y;
					coordsEt.cols = coordsEt1.cols;
					coordsEt.rows = coordsEt1.rows;
				}
*/
				TakeEt();
			}
			break;
		case 4:
			if (Kkor > porog_0_90)
			{
				if(freeze++ > 20) Capture = 0;
			}
			else freeze = 0;
			break;
		case 5:
//			EtZone = findObjPerim(G10 , Cbuf, ColStrob, RowStrob, Bz, stack , stack1, MaxStack, Sync);
			Curr_zone = findObjPerim(G10 , Cbuf, ColStrob, RowStrob, Bz, stack , stack1, 0, Sync);
			Kkor = fabs((float)(EtZone.NumPix - Curr_zone.NumPix) / EtZone.NumPix);
			if(Kkor < 0.5){
				freeze = 0;
				EtZone = Curr_zone;
				RowStrob = EtZone.down - EtZone.up + (BorderRows << 1) + 1;
				ColStrob = EtZone.right - EtZone.left + (BorderCols << 1) + 1;
				xy.x = EtZone.left;
				xy.y = EtZone.up;
				Mxy.x = (float)EtZone.SumBrightX/EtZone.SumBright + XStrob;
				Mxy.y = (float)EtZone.SumBrightY/EtZone.SumBright + YStrob;
			}
			else
			{
				freeze++;
				if(freeze > 25)
				{
					freeze = 0;
					Capture = 0;//цель потеряна
				}
			}
			break;
		case 6:
			if (Kkor < porog_0_90)
			{
				freeze = 0;
				coordsEt.x = xy.x;
				coordsEt.y = xy.y;
				EtalonCorrect((Uint8*)strobAddr,  (Uint32)&coordsEt, ColStrob);
				TakeEt();
			}
			else if(freeze++ > 20) Capture = 0;
			break;
		case 7:
			findObj((Uint8*)strobAddr, RowStrob, ColStrob, (Uint32)&coordsEt1);
			if (abs(coordsEt1.cols + coordsEt1.rows - coordsEt.cols - coordsEt.rows) < ((coordsEt.cols + coordsEt.rows) >> 1))
			{
				coordsEt = coordsEt1;
				freeze = 0;
			}
			else if(freeze++ > 20) Capture = 0;
			xy.x = coordsEt.x;
			xy.y = coordsEt.y;
			break;
		}
		if(AlgNum != 5)
		{
			Mxy.x = (float)(xy.x + XStrob) + (float)coordsEt.cols / 2;
			Mxy.y = (float)(xy.y + YStrob) + (float)coordsEt.rows / 2;
		}
		//обновление координат
		if(freeze == 0){
			XStrob += xy.x - BorderCols;
			if(XStrob < 0) XStrob = 0;
			if(XStrob > 719) XStrob = 719;
			if((XStrob + ColStrob) >= 720) XStrob = 720 - ColStrob - 1;

			YStrob += xy.y - BorderRows;
			if(YStrob < 0) YStrob = 0;
			if(YStrob > 287) YStrob = 287;
			if((YStrob + RowStrob) >= 288) YStrob = 288 - RowStrob - 1;
		}
		if(coordsEt.cols <= ColMin + 1 && coordsEt.rows <= RowMin + 1)  Capture = 0;


	}
}

void TakeEt()
{
	colsStEt = ColStrob;
	EtCopy((Uint8*)(CorGray == 0 ? strobAddr : strobAddrG), Etalon, ColStrob, RowStrob);
	RowStrob = coordsEt.rows + (BorderRows << 1) + 1;
	ColStrob = coordsEt.cols + (BorderCols << 1) + 1;
	xy.x = coordsEt.x;
	xy.y = coordsEt.y;
}

XY CorrParts(Uint32 smx, Uint32 smy, Uint32 et, Uint32 st, float* RezKkor, Uint32 coordsEtaddr, Uint32 colsStEt)
{
	XY xyrez;
	Uint32 stepx = 1;
	Uint32 stepy = 1;
	if(ColStrob > 128) stepx = 2;
//	if(ColStrob > 192) stepx = 5;
//	if(RowStrob > 64) stepy = 2;
//	if(RowStrob > 96) stepy = 2;
	*RezKkor = PartFastCorrFullFromPrevSt0(et, smy, smx, 0, 0, st, coordsEt.cols, coordsEt.rows,  colsStEt, ColStrob, RowStrob, (Uint32)&xyrez, BorderCols, BorderRows, stepx, stepy);
	return xyrez;
//
//
//
//	XY xyrez, xyrez1;
//	float k, Kk;
//	int x, y;
//	int gridx = 3 * BorderCols >> 1;
//	int gridy = 3 * BorderRows >> 1;
//	int sizeRow, sizeCol;
//	Uint32 IssmallX = 0, IssmallY = 0;
//
//	COORDS coordsEt = *(COORDS*)coordsEtaddr;
//
//	if(coordsEt.rows > gridy) sizeRow = coordsEt.rows /(coordsEt.rows / gridy);
//	else {sizeRow = coordsEt.rows; IssmallY = 1;}
//	if(coordsEt.cols > gridx) sizeCol = coordsEt.cols /(coordsEt.cols / gridx);
//	else {sizeCol = coordsEt.cols; IssmallX = 1;}
//
//	Kk = 255.0;
//
////	memset(MassCorR, 0, ((BorderRows << 1) + 1) * ((BorderCols << 1) + 1) *2);
//
//	Uint32 sum, i, j, i1, j1;
//	Uint8* st1;
//	for(y = 0; y < coordsEt.rows - 3; y += sizeRow)
//		for(x = 0; x < coordsEt.cols - 3; x += sizeCol)
//		{
//			st1 = (Uint8*)et;
//			sum = 0;
//			for(i = colsStEt * (y + smy), i1 = 0; i1 < sizeRow; i1 ++, i += colsStEt)
//				for(j = smx + x, j1 = 0; j1 < sizeCol; j1 ++, j ++)
//				sum += st1[i + j];
//
//			if((sum > sizeCol * sizeRow * (255 * 0.10)) || CorGray > 0 || (IssmallY == 1  && IssmallX == 1))
//			{
//	//			memset(MassCor, 255, ((BorderRows << 1) + 1)* ((BorderCols << 1) + 1) * 2);
//				k = PartFastCorrFullFromPrevSt0(et, smy, smx, y, x, st, sizeCol, sizeRow, colsStEt, ColStrob, RowStrob, (Uint32)&xyrez1, BorderCols, BorderRows, IssmallX, IssmallY);
//				if(Kk > k)
//				{
//					Kk = k;
//					xyrez = xyrez1;
//				}
//			}
//		}
//	*RezKkor = Kk;
//	return xyrez;
}


int EtalonCorrect(Uint8* st, Uint32 rezult, Uint32 colsStEt)
{
	int cordone = 0;
	Uint16* rez = (Uint16*)rezult;
	Uint16 smy = rez[1];
	Uint16 smx = rez[0];
	Uint16 colsEt = rez[2];
	Uint16 rowsEt = rez[3];
	Uint32 cnt;

	Uint32 NPixRowFirst = 0; //число ненулевых пикселей на 1-й строке
	Uint32 NPixRowFirstNext = 0; //число ненулевых пикселей на 1-й строке
	Uint32 NPixRowFirstPrev = 0; //число ненулевых пикселей на 1-й строке
	Uint32 NPixRowFirstMax = 0; //число ненулевых пикселей на 1-й строке
	Uint32 NPixRowFirstMin = 0; //число ненулевых пикселей на 1-й строке

	Uint32 NPixRowLast = 0; //число ненулевых пикселей на послдней строке
	Uint32 NPixRowLastPrev = 0; //число ненулевых пикселей на послдней строке
	Uint32 NPixRowLastNext = 0; //число ненулевых пикселей на послдней строке
	Uint32 NPixRowLastMin = 0; //число ненулевых пикселей на послдней строке
	Uint32 NPixRowLastMax = 0; //число ненулевых пикселей на послдней строке

	Uint8* RowFirst = st + smy * colsStEt + smx;
	Uint8* RowFirstPrev = st + (smy - 1) * colsStEt + smx;
	Uint8* RowFirstNext = st + (smy + 1) * colsStEt + smx;

	Uint8* RowLast = RowFirst + (rowsEt - 1)* colsStEt;
	Uint8* RowLastPrev = RowFirst + (rowsEt - 2)* colsStEt;
	Uint8* RowLastNext = RowFirst + (rowsEt)* colsStEt;


	Uint8* ColFirst = RowFirst;
	Uint8* ColFirstNext = RowFirst + 1;
	Uint8* ColFirstPrev = RowFirst - 1;

	Uint8* ColLast = ColFirst + colsEt - 1;
	Uint8* ColLastNext = ColFirst + colsEt;
	Uint8* ColLastPrev = ColFirst + colsEt - 2;

	Uint32 NPixColFirst = 0; //число ненулевых пикселей на 1-м столбце
	Uint32 NPixColFirstMin = 0; //число ненулевых пикселей на 1-м столбце
	Uint32 NPixColFirstMax = 0; //число ненулевых пикселей на 1-м столбце
	Uint32 NPixColFirstPrev = 0; //число ненулевых пикселей на 1-м столбце
	Uint32 NPixColFirstNext = 0; //число ненулевых пикселей на 1-м столбце

	Uint32 NPixColLast = 0; //число ненулевых пикселей на послднем столбце
	Uint32 NPixColLastMin = 0; //число ненулевых пикселей на послднем столбце
	Uint32 NPixColLastMax = 0; //число ненулевых пикселей на послднем столбце
	Uint32 NPixColLastNext = 0; //число ненулевых пикселей на послднем столбце
	Uint32 NPixColLastPrev = 0; //число ненулевых пикселей на послднем столбце

	for(cnt = 0; cnt < colsEt; cnt++)//строки
	{
		NPixRowLast += *RowLast++;
		NPixRowLastNext += *RowLastNext++;
		NPixRowLastPrev += *RowLastPrev++;

		NPixRowFirst += *RowFirst++;
		NPixRowFirstPrev += *RowFirstPrev++;
		NPixRowFirstNext += *RowFirstNext++;
	}

	NPixRowFirstMin = NPixRowFirst;
	if(NPixRowFirstMin < NPixRowFirstPrev) NPixRowFirstMin = NPixRowFirstPrev;
	if(NPixRowFirstMin < NPixRowFirstNext) NPixRowFirstMin = NPixRowFirstNext;

	NPixRowFirstMax = NPixRowFirst;
	if(NPixRowFirstMax > NPixRowFirstPrev) NPixRowFirstMax = NPixRowFirstPrev;
	if(NPixRowFirstMax > NPixRowFirstNext) NPixRowFirstMax = NPixRowFirstNext;

	NPixRowLastMin = NPixRowLast;
	if(NPixRowLastMin < NPixRowLastPrev) NPixRowLastMin = NPixRowLastPrev;
	if(NPixRowLastMin < NPixRowLastNext) NPixRowLastMin = NPixRowLastNext;

	NPixRowLastMax = NPixRowLast;
	if(NPixRowLastMax > NPixRowLastPrev) NPixRowLastMax = NPixRowLastPrev;
	if(NPixRowLastMax > NPixRowLastNext) NPixRowLastMax = NPixRowLastNext;

	for(cnt = 0; cnt < rowsEt; cnt++)//столбцы
	{
		NPixColLast += *ColLast;
		NPixColLastNext += *ColLastNext;
		NPixColLastPrev += *ColLastPrev;

		NPixColFirst += *ColFirst;
		NPixColFirstNext += *ColFirstNext;
		NPixColFirstPrev += *ColFirstPrev;

		ColLast += colsStEt;
		ColLastNext += colsStEt;
		ColLastPrev += colsStEt;

		ColFirst += colsStEt;
		ColFirstNext += colsStEt;
		ColFirstPrev += colsStEt;
	}

	NPixColLastMin = NPixColLast;
	if(NPixColLastMin < NPixColLastPrev) NPixColLastMin = NPixColLastPrev;
	if(NPixColLastMin < NPixColLastNext) NPixColLastMin = NPixColLastNext;

	NPixColLastMax = NPixColLast;
	if(NPixColLastMax > NPixColLastPrev) NPixColLastMax = NPixColLastPrev;
	if(NPixColLastMax > NPixColLastNext) NPixColLastMax = NPixColLastNext;

	NPixColFirstMin = NPixColFirst;
	if(NPixColFirstMin < NPixColFirstPrev) NPixColFirstMin = NPixColFirstPrev;
	if(NPixColFirstMin < NPixColFirstNext) NPixColFirstMin = NPixColFirstNext;

	NPixColFirstMax = NPixColFirst;
	if(NPixColFirstMax > NPixColFirstPrev) NPixColFirstMax = NPixColFirstPrev;
	if(NPixColFirstMax > NPixColFirstNext) NPixColFirstMax = NPixColFirstNext;

	if(rowsEt < RowMax)//расширение по вертикали 255*3 = 765
		if((NPixRowLastMin > 510) && ((smy + rowsEt) < RowStrob)) rowsEt++;	//вниз
	if(rowsEt < RowMax)//расширение по вертикали 255*3 = 765
		if((NPixRowFirstMin > 510) && (smy > 0)) {rowsEt++; smy--; cordone = 1;}		//вверх

	if(colsEt < ColMax)//расширение по горизонтали
		if((NPixColLastMin > 510) && ((smx + colsEt) < ColStrob)) colsEt++;	//вниз
	if(colsEt < ColMax)//расширение по горизонтали
		if((NPixColFirstMin > 510) && (smx > 0)) {colsEt++; smx--;cordone = 1;}		//вверх

	if(rowsEt > RowMin)//сужение по вертикали
		if(NPixRowLastMax <= 510) {rowsEt--;cordone = 1;}				//вниз
	if(rowsEt > RowMin)//сужение по вертикали
		if(NPixRowFirstMax <= 510) {rowsEt--; smy++;cordone = 1;}	//вверх

	if(colsEt > ColMin)//сужение по горизонтали
		if(NPixColLastMax <= 510) {colsEt--;cordone = 1;}				//вниз
	if(colsEt > ColMin)//сужение по горизонтали
		if(NPixColFirstMax <= 510) {colsEt--; smx++;cordone = 1;}	//вверх


	rez[1] = smy;
	rez[0] = smx;
	rez[2] = colsEt;
	rez[3] = rowsEt;
	return cordone;
}
/*
int AirEtalonCorrect(Uint8* st, Uint32 rezult, Uint32 colsStEt, Uint16 smx, Uint16 smy)
{
	int cordone = 0;
	Uint16* rez = (Uint16*)rezult;
	Uint16 colsEt = rez[2];
	Uint16 rowsEt = rez[3];
	Uint32 cnt;

	Uint32 NPixRowFirst = 0; //число ненулевых пикселей на 1-й строке
	Uint32 NPixRowLast = 0; //число ненулевых пикселей на послдней строке

	Uint32 NPixColFirst = 0; //число ненулевых пикселей на 1-м столбце
	Uint32 NPixColLast = 0; //число ненулевых пикселей на послднем столбце

	Uint16 ilast, ifirst;
	ifirst = smy * colsStEt + smx;
	ilast = (rowsEt - 1 + smy) * colsStEt + smx;
	for(cnt = 0; cnt < colsEt; cnt++, ifirst++, ilast++)//строки
	{
		NPixRowLast += st[ilast];
		NPixRowFirst += st[ifirst];
	}
	ifirst = smy * colsStEt + smx;
	ilast = smy * colsStEt + smx + colsEt - 1;
	for(cnt = 0; cnt < rowsEt; cnt++, ifirst += colsStEt, ilast += colsStEt)//столбцы
	{
		NPixColLast += st[ilast];
		NPixColFirst += st[ifirst];
	}

	if(rowsEt < RowMax)//расширение по вертикали 255*3 = 765
		if((NPixRowLast > 510) && ((smy + rowsEt) < RowStrob)) rowsEt++;	//вниз
	if(rowsEt < RowMax)//расширение по вертикали 255*3 = 765
		if((NPixRowFirst > 510) && (smy > 0)) {rowsEt++; smy--; cordone = 1;}		//вверх

	if(colsEt < ColMax)//расширение по горизонтали
		if((NPixColLast > 510) && ((smx + colsEt) < ColStrob)) colsEt++;	//вниз
	if(rowsEt < RowMax)//расширение по вертикали 255*3 = 765
		if((NPixColFirst > 510) && (smx > 0)) {colsEt++; smx--;cordone = 1;}		//вверх

	if(rowsEt > RowMin)//сужение по вертикали
		if(NPixRowLast <= 510) {rowsEt--;cordone = 1;}				//вниз
	if(rowsEt > RowMin)//сужение по вертикали
		if(NPixRowFirst <= 510) {rowsEt--; smy++;cordone = 1;}	//вверх

	if(colsEt > ColMin)//сужение по горизонтали
		if(NPixColLast <= 510) {colsEt--;cordone = 1;}				//вниз
	if(colsEt > ColMin)//сужение по горизонтали
		if(NPixColFirst <= 510) {colsEt--; smx++;cordone = 1;}	//вверх


	rez[1] = smy;
	rez[0] = smx;
	rez[2] = colsEt;
	rez[3] = rowsEt;
	return cordone;
}
*/

/*
void TresholdCorrect(Uint32* st, int isH, int step)
{
	int i, rez = 0;
	for(i = 0; i < RowStrob * ColStrob; i+=4)
		rez += _dotpu4(*st++, 0x01010101);		//накопление сумм 4-х элементов
	int square = (RowStrob - (BorderRows << 1))*(ColStrob - (BorderCols << 1));
	double d = (double)rez/(255 * square);
	double tr = 0.05;
	switch(0)
	{
	case 0:
		if(square <= 32*16) { 	tr = 0.25;	break;}
		if(square <= 64*32) { 	tr = 0.20;	break;}
		if(square <= 128*64) { 	tr = 0.10;	break;}
		if(square <= 192*96) { 	tr = 0.10;	break;}
	}
	if (d > tr) tresh += step;
	else
		if(isH < 1275) tresh-= step;
	*ContTreshToAltera = tresh;
}
*/

/*
void MassCounting(Uint16 x, Uint16 y)
{
	int i, j, tmp;
	int st, st1;
	int mx = 0, my = 0, mx1 = 0, my1 = 0;


	//заливка по вертикали
	st = y * ColStrob + x;
	for(j = 0; j < coordsEt.cols; j++, st ++)
	{
		tmp = coordsEt.rows;
		st1 = st;
		while(M[st1] < 0xFF)
		{
			M[st1] = 0x11;
			st1 += ColStrob;
			if(tmp-- <= 1) break;
		}
		st1 = st + (coordsEt.rows - 1) * ColStrob;
		while(M[st1] < 0xFF)
		{
			M[st1] = 0x11;
			st1 -= ColStrob;
			if(tmp-- <= 1) break;
		}
	}

	//заливка по горизонтали
	st = y * ColStrob + x;
	for(i = 0; i < coordsEt.rows; i++, st += ColStrob)
	{
		tmp = coordsEt.cols;
		st1 = st;
		while(M[st1] < 0xFF)
		{
			M[st1++] = 0x11;
			if(tmp-- <= 1) break;
		}
		st1 = st + coordsEt.cols - 1;
		while(M[st1] < 0xFF)
		{
			M[st1--] = 0x11;
			if(tmp-- <= 1) break;
		}
	}
	//подсчет по вертикали
	st = y * ColStrob + x;
	for(i = 0; i < coordsEt.rows; i++, st += ColStrob)
	{
		tmp = 0;
		st1 = st;
		for(j = 0; j < coordsEt.cols; j++, st1++)
			if(M[st1] != 0x11) tmp++;
		my += tmp * i;
		my1 += tmp;
	}
	//подсчет по горизонтали
	st = y * ColStrob + x;
	for(j = 0; j < coordsEt.cols; j++, st ++)
	{
		tmp = 0;
		st1 = st;
		for(i = 0; i < coordsEt.rows; i++, st1 += ColStrob)
			if(M[st1] != 0x11) tmp++;
		mx += tmp * j;
		mx1 += tmp;
	}

	//расчет центра масс

	Mxy.y = ((float)my)/my1;
	Mxy.y += YStrob + BorderRows;

	Mxy.x = ((float)mx)/mx1;
	Mxy.x += XStrob + BorderCols;

}
*/
/*
void EtCopy2(Uint8* src, short smx, short smy, Uint8* dst)
{
	short i, j, i1, j1, i2, j2;
	for(i = 0, i1 = 0, i2 = smy * ColStrob; i < coordsEt.rows; i++, i1 += coordsEt.cols, i2 += ColStrob)
		for(j = 0, j1 = 0, j2 = smx; j < coordsEt.cols; j++, j1++, j2++)
//			dst[i1 + j1] = ((dst[i1 + j1] << 4) - dst[i1 + j1] + src[i2 + j2]) >> 4;
			dst[i1 + j1] = src[i2 + j2];
}
*/
