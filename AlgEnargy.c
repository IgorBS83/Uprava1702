#include "main.h"
#include <string.h>
#include <math.h>
#include <MathFuncs.h>

#define ZONE_MIN_PIX_AMOUNT 50

BinaryZone AddZone(BinaryZone, BinaryZone);
int ZoneCheck(BinaryZone);
BinaryZone TakeZone(BinaryZone*);
BinaryZone FindZone(BinaryZone*);
BinaryZone TakeZone2(int, BinaryZone*);
BinaryZone FindZone2(int, BinaryZone*);



short AvgBright(Uint8* st)
{
	int mb, j;
	Uint8* st1, *st2;
	mb = 0;
	st1 = st;
	st2 = st + (RowStrob - 1)* ColStrob;
	for(j = 0; j < ColStrob; j++, st1++, st2++)
	{
		mb += *st1;
		mb += *st2;
	}

	st1 = st;
	st2 = st + ColStrob - 1;

	for(j = 0; j < RowStrob; j++, st1 += ColStrob, st2 += ColStrob)
	{
		mb += *st1;
		mb += *st2;
	}
	mb = (mb / (RowStrob + ColStrob)) >> 1;
	return (short)mb;
}
/*
XY MinMax(Uint8* st)
{
	Uint32 *st32 =(Uint32*) st;
	int i, b;
	Uint32 min, max;
	min = 0xFFFFFFFF;
	max = 0;
	for(i = 0; i < ((RowStrob * ColStrob) >> 2); i++)
	{
		b = _cmpgtu4(st32[i], min);
	}
	return 0;
}
*/
int Energy()
{
	int rezult = 0;

	volatile Uint16  NumZone, NumZoneInv;
	BinaryZone *Zones, *ZonesInv;
	BinaryZone Zone1;

	if(CadrN & 1)
	{
		NumZone = 		*(Uint16*)(0xA0000000 + (0x2005 << 3)) - 1;
		NumZoneInv = 	*(Uint16*)(0xA0000000 + (0x2007 << 3)) - 1;
		Zones =  	(BinaryZone*)(0xA0000000 + (1 << (12 + 3)) + (1 << (10 + 3)));
//		ZonesLast =  	(BinaryZone*)(0xA0000000 + (1 << (10 + 3)));
		ZonesInv =  (BinaryZone*)(0xA0000000 + (1 << (12 + 3)) + (1 << (11 + 3)));
//		ZonesInvLast = (BinaryZone*)(0xA0000000 + (1 << (11 + 3)));
	}
	else
	{
		NumZone = 		*(Uint16*)(0xA0000000 + (0x2004 << 3)) - 1;
		NumZoneInv = 	*(Uint16*)(0xA0000000 + (0x2006 << 3)) - 1;
		Zones =  	(BinaryZone*)(0xA0000000 + (1 << (10 + 3)));
//		ZonesLast =  	(BinaryZone*)(0xA0000000 + (1 << (12 + 3)) + (1 << (10 + 3)));
		ZonesInv =  (BinaryZone*)(0xA0000000 + (1 << (11 + 3)));
//		ZonesInvLast = (BinaryZone*)(0xA0000000 + (1 << (12 + 3)) + (1 << (11 + 3)));
	}

	if(Sync == 0) Sync ++;
	else
	{
		if(Sync == 1)
		{
			Sync++;
			ObjType = 1;
			//прямая картинка
			EtZone = TakeZone2(NumZone, Zones);
			//инверсная картинка
			Zone1 = TakeZone2(NumZoneInv, ZonesInv);

			if(Zone1.NumPix > EtZone.NumPix)
			{
				EtZone = Zone1;
				ObjType = 2;
			}
			if (EtZone.NumPix == 0)
			{
				Capture = 0;
			}

		}
		else
		{
			switch(ObjType)
			{
			case 1:
				Zone1 = FindZone2(NumZone, Zones);
				break;
			case 2:
				Zone1 = FindZone2(NumZoneInv, ZonesInv);
				break;
			}
			if(Zone1.NumPix > 0) {
				EtZone = Zone1;

				Mxy.x = (float)EtZone.SumBrightX/EtZone.SumBright;
				Mxy.y = (float)EtZone.SumBrightY/EtZone.SumBright;

				XStrob = EtZone.left - BorderCols;
				YStrob = EtZone.up - BorderRows;
				ColStrob = EtZone.right - EtZone.left + (BorderCols << 1) + 1;
				RowStrob = EtZone.down - EtZone.up + (BorderRows << 1) + 1;

				if(XStrob < 0) XStrob = 0;
				if(YStrob < 0) YStrob = 0;
				if(XStrob > 719) XStrob = 719;
				if(YStrob > 287) YStrob = 287;

				if(XStrob + ColStrob > 719) ColStrob = 720 - XStrob;
				if(YStrob + RowStrob > 287) RowStrob = 288 - YStrob;
			}
			else
			{
				freeze++;
				if(freeze > 25)
				{
					freeze = 0;
					Capture = 0;//цель потеряна
					BinarInv = 2;
				}
			}
		}
	}
	return rezult;
}

BinaryZone TakeZone2(int Zone_amount, BinaryZone *Zones)
{
	BinaryZone Zone, Zone1;
	int i;
	memset((Uint32*)&Zone1, 0, sizeof(BinaryZone));

	for(i = 0; i < Zone_amount; i++)
	{
		Zone = Zones[i];
		if (ZoneCheck(Zone) > 0)
			if((Zone.left >= XStrob + 1) && (Zone.right <= XStrob + ColStrob - 1) && (Zone.up >= YStrob + 1) && (Zone.down <= YStrob + RowStrob - 1))
			//накопление зон
				if(Zone1.NumPix < Zone.NumPix) Zone1 = Zone;
	}
	return Zone1;
}

BinaryZone FindZone2(int Zone_amount, BinaryZone *Zones)
{
	BinaryZone Zone, Zone1;
	int i;
	float K_kor = 0, K_kor_rez = 0.5;
	memset((Uint32*)&Zone1, 0, sizeof(BinaryZone));


	for(i = 0; i < Zone_amount; i++)
	{
		Zone = Zones[i];
		if (ZoneCheck(Zone) > 0)
			if((Zone.left >= XStrob + 1) && (Zone.right <= XStrob + ColStrob - 1) && (Zone.up >= YStrob + 1) && (Zone.down <= YStrob + RowStrob - 1)){
				K_kor = fabs((float)(EtZone.NumPix - Zone.NumPix) / EtZone.NumPix);
				if(K_kor < K_kor_rez){
					K_kor_rez = K_kor;
					Zone1 = Zone;
				}
			}
	}
	return Zone1;

}


int ZoneCheck(BinaryZone z)
{
	volatile int rez = 1;
	if((z.NumPix < ZONE_MIN_PIX_AMOUNT) ||
		(z.left > 720) ||
		(z.right > 720) ||
		(z.up > 288) ||
		(z.down > 288)) rez = 0;
	return rez;
}

