#include "main.h"
//Переключение кадров для копирования

void Start()
{
	//получение номера кадра
	CadrN = *(Uint16*)CadrInfoAddr;
	if(ColStrob * RowStrob < MaxCadr)
	{
		R1(fieldsG[CadrN & 1], strobAddrG, XStrob, YStrob, ColStrob, RowStrob);
		R6(fields[CadrN & 1], strobAddr, XStrob, YStrob, ColStrob, RowStrob);
	}
	else Capture = 0;
}
/*
void Start()
{
	//получение номера кадра
	CadrN = *(Uint16*)CadrInfoAddr;
	if(freeze < 1)
	{
		if(TvTpv == 0)
		{
			switch(CadrN & 2)
			{
			case 0:
				strobAddr0 = (Uint32)&C10;
				strobAddr1 = (Uint32)&C11;

				strobEtAddr0 = (Uint32)&C20;
				strobEtAddr1 = (Uint32)&C21;

				strobAddrG0 = (Uint32)&G10;
				strobAddrG1 = (Uint32)&G11;

				strobEtAddrG0 = (Uint32)&G20;
				strobEtAddrG1 = (Uint32)&G21;
				break;
			case 2:
				strobAddr0 = (Uint32)&C20;
				strobAddr1 = (Uint32)&C21;

				strobEtAddr0 = (Uint32)&C10;
				strobEtAddr1 = (Uint32)&C11;

				strobAddrG0 = (Uint32)&G20;
				strobAddrG1 = (Uint32)&G21;

				strobEtAddrG0 = (Uint32)&G10;
				strobEtAddrG1 = (Uint32)&G11;
				break;
			}
			switch(CadrN & 1)
			{
			case 0:
				strobAddr = strobAddr0;
				strobAddrG = strobAddrG0;
				break;
			case 1:
				strobAddr = strobAddr1;
				strobAddrG = strobAddrG1;
				break;
			}
		}
		else
		{
			switch(CadrN & 3)
			{
			case 0:
				strobAddr = (Uint32)&C10;
				strobAddrG = (Uint32)&G10;
				strobEtTpvAddr = (Uint32)&C21;
				strobEtTpvAddrG = (Uint32)&G21;
				break;
			case 1:
				strobAddr = (Uint32)&C11;
				strobAddrG = (Uint32)&G11;
				strobEtTpvAddr = (Uint32)&C10;
				strobEtTpvAddrG = (Uint32)&G10;
				break;
			case 2:
				strobAddr = (Uint32)&C20;
				strobAddrG = (Uint32)&G20;
				strobEtTpvAddr = (Uint32)&C11;
				strobEtTpvAddrG = (Uint32)&G11;
				break;
			case 3:
				strobAddr = (Uint32)&C21;
				strobAddrG = (Uint32)&G21;
				strobEtTpvAddr = (Uint32)&C20;
				strobEtTpvAddrG = (Uint32)&G20;
				break;
			}
		}
	}
	R1(fieldsG[CadrN & 1], strobAddrG, XStrob, YStrob, ColStrob, RowStrob);
//	R2(strobAddr, (Uint32)&M, XStrob, YStrob, ColStrob, RowStrob);
	R6(fields[CadrN & 1], strobAddr, XStrob, YStrob, ColStrob, RowStrob);
}
*/

/*
void Start()
{
	//получение номера кадра
	CadrN = *(Uint32*)CadrInfoAddr;
	if(freeze < 1)
		switch(CadrN & 2)
		{
		case 0:
			strobAddr0 = (Uint32)&C10;
			strobAddr1 = (Uint32)&C11;

			strobEtAddr0 = (Uint32)&C20;
			strobEtAddr1 = (Uint32)&C21;

			strobAddrG0 = (Uint32)&G10;
			strobAddrG1 = (Uint32)&G11;

			strobEtAddrG0 = (Uint32)&G20;
			strobEtAddrG1 = (Uint32)&G21;
			break;
		case 2:
			strobAddr0 = (Uint32)&C20;
			strobAddr1 = (Uint32)&C21;

			strobEtAddr0 = (Uint32)&C10;
			strobEtAddr1 = (Uint32)&C11;

			strobAddrG0 = (Uint32)&G20;
			strobAddrG1 = (Uint32)&G21;

			strobEtAddrG0 = (Uint32)&G10;
			strobEtAddrG1 = (Uint32)&G11;
			break;
		}
	switch(CadrN & 1)
	{
	case 0:
		strobAddr = strobAddr0;
		strobAddrG = strobAddrG0;
		strobEtTpvAddr = strobEtAddr0;
		strobEtTpvAddrG = strobEtAddrG0;
		R1(fieldsG[0], strobAddrG, XStrob, YStrob, ColStrob, RowStrob);
		R2(strobAddr, (Uint32)&M, XStrob, YStrob, ColStrob, RowStrob);
		R6(fields[0], strobAddr, XStrob, YStrob, ColStrob, RowStrob);
		break;
	case 1:
		strobAddr = strobAddr1;
		strobAddrG = strobAddrG1;
		strobEtTpvAddr = strobEtAddr1;
		strobEtTpvAddrG = strobEtAddrG1;
		R1(fieldsG[1], strobAddrG, XStrob, YStrob, ColStrob, RowStrob);
		R2(strobAddr, (Uint32)&M, XStrob, YStrob, ColStrob, RowStrob);
		R6(fields[1], strobAddr, XStrob, YStrob, ColStrob, RowStrob);
		break;
	}
}
*/
