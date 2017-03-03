typedef unsigned int Uint32;
typedef unsigned short Uint16;
typedef unsigned char Uint8;
#include <string.h>
#include <math.h>
#include "main.h"
#include <MathFuncs.h>

Uint32 cossin[180] = {0x3FFF0000,0x3FFD011E,0x3FF6023C,0x3FE9035A,
0x3FD80477,0x3FC10594,0x3FA606B1,0x3F8507CD,0x3F6008E9,0x3F360A03,0x3F070B1D,0x3ED20C37,0x3E990D4F,0x3E5C0E66,0x3E190F7C,0x3DD11091,0x3D8511A4,0x3D3412B6,0x3CDE13C7,0x3C8314D6,
0x3C2315E4,0x3BBF16F0,0x3B5717FA,0x3AE91902,0x3A771A08,0x3A011B0C,0x39851C0E,0x39061D0E,0x38821E0C,0x37F91F07,0x376D2000,0x36DB20F6,0x364621EA,0x35AC22DB,0x350F23CA,0x346D24B5,
0x33C7259E,0x331D2684,0x326E2767,0x31BC2847,0x31072923,0x304D29FD,0x2F8F2AD3,0x2ECE2BA6,0x2E092C75,0x2D412D41,0x2C752E09,0x2BA62ECE,0x2AD32F8F,0x29FD304D,0x29233107,0x284731BC,
0x2767326E,0x2684331D,0x259E33C7,0x24B5346D,0x23CA350F,0x22DB35AC,0x21EA3646,0x20F636DB,0x2000376D,0x1F0737F9,0x1E0C3882,0x1D0E3906,0x1C0E3985,0x1B0C3A01,0x1A083A77,0x19023AE9,
0x17FA3B57,0x16F03BBF,0x15E43C23,0x14D63C83,0x13C73CDE,0x12B63D34,0x11A43D85,0x10913DD1,0x0F7C3E19,0x0E663E5C,0x0D4F3E99,0x0C373ED2,0x0B1D3F07,0x0A033F36,0x08E93F60,0x07CD3F85,
0x06B13FA6,0x05943FC1,0x04773FD8,0x035A3FE9,0x023C3FF6,0x011E3FFD,0x00013FFF,0xFEE33FFD,0xFDC53FF6,0xFCA73FE9,0xFB8A3FD8,0xFA6D3FC1,0xF9503FA6,0xF8343F85,0xF7183F60,0xF5FE3F36,
0xF4E43F07,0xF3CA3ED2,0xF2B23E99,0xF19B3E5C,0xF0853E19,0xEF703DD1,0xEE5D3D85,0xED4B3D34,0xEC3A3CDE,0xEB2B3C83,0xEA1D3C23,0xE9113BBF,0xE8073B57,0xE6FF3AE9,0xE5F93A77,0xE4F53A01,
0xE3F33985,0xE2F33906,0xE1F53882,0xE0FA37F9,0xE001376D,0xDF0B36DB,0xDE173646,0xDD2635AC,0xDC37350F,0xDB4C346D,0xDA6333C7,0xD97D331D,0xD89A326E,0xD7BA31BC,0xD6DE3107,0xD604304D,
0xD52E2F8F,0xD45B2ECE,0xD38C2E09,0xD2C02D41,0xD1F82C75,0xD1332BA6,0xD0722AD3,0xCFB429FD,0xCEFA2923,0xCE452847,0xCD932767,0xCCE42684,0xCC3A259E,0xCB9424B5,0xCAF223CA,0xCA5522DB,
0xC9BB21EA,0xC92620F6,0xC8942000,0xC8081F07,0xC77F1E0C,0xC6FB1D0E,0xC67C1C0E,0xC6001B0C,0xC58A1A08,0xC5181902,0xC4AA17FA,0xC44216F0,0xC3DE15E4,0xC37E14D6,0xC32313C7,0xC2CD12B6,
0xC27C11A4,0xC2301091,0xC1E80F7C,0xC1A50E66,0xC1680D4F,0xC12F0C37,0xC0FA0B1D,0xC0CB0A03,0xC0A108E9,0xC07C07CD,0xC05B06B1,0xC0400594,0xC0290477,0xC018035A,0xC00B023C,0xC004011E};


BinaryZone fill8sv(Uint8* Cadr, Uint8* CAD, short cols, short rows, int j1, int i1, Uint8 Color, Uint8 cnt, Uint8 porog)
{
	memset(stack, 0, sizeof(RECT) * MaxStack);
	Uint32 ist = 1, ist1 = 0;
	Uint32 b = 0;
	RECT a;
	BinaryZone Zone;
	int maxi = cols * rows;
    stack[ist].def = i1 + j1;
    stack[ist].i = i1;
	stack[ist].j = j1;

	memset(&Zone, 0, sizeof(BinaryZone));

	Zone.SumBright = Cadr[i1 + j1];
	Zone.left = cols;
//	Zone.right = 0;
	Zone.up = maxi;
//	Zone.down = 0;
//	Zone.NumPix = 0;
//	Zone.SumBrightX = 0;
//	Zone.SumBrightY = 0;
//	Zone.InvSumBrightX = 0;
//	Zone.InvSumBrightY = 0;


    while((ist > 0) || (ist1 > 0))
    {
     	while(ist > 0)
     	{
     			b = b < ist ? ist : b;
				a = stack[ist];
				stack[ist].def = 0;
				j1 = a.j;
				i1 = a.i;
				CAD[i1 + j1] = cnt;
				ist--;

				Zone.NumPix++;
				Zone.SumBright += Cadr[i1 + j1];
				if(Zone.left > j1) Zone.left = j1;
				if(Zone.right < j1) Zone.right = j1;
				if(Zone.up > i1) Zone.up = i1;
				if(Zone.down < i1) Zone.down = i1;
				Zone.SumBrightX += j1 * Cadr[i1 + j1];
				Zone.SumBrightY += i1 * Cadr[i1 + j1];
				Zone.InvSumBrightX += j1 * (255 - Cadr[i1 + j1]);
				Zone.InvSumBrightY += i1 * (255 - Cadr[i1 + j1]);

				if ((j1 > 0) && (abs(Cadr[i1 + j1 - 1] - Color) < porog) && (CAD[i1 + j1 - 1] == 0))
				{//left
					ist1 = addpoint(stack, stack1, ist, ist1, i1, j1 - 1);
				}
				if ((j1 > 0) && (i1 > 0) && (abs(Cadr[i1 - cols + j1 - 1] - Color) < porog) && (CAD[i1 - cols + j1 - 1] == 0))
				{//left//up
					ist1 = addpoint(stack, stack1, ist, ist1, i1 - cols, j1 - 1);
				}
				if ((j1 > 0) && (i1 < maxi - cols) && (abs(Cadr[i1 + cols + j1 - 1] - Color) < porog) && (CAD[i1 + cols + j1 - 1] == 0))
				{//left//down
					ist1 = addpoint(stack, stack1, ist, ist1, i1 + cols, j1 - 1);
				}
				if ((j1 < cols - 1) && (i1 < maxi - cols) && (abs(Cadr[i1 + cols + j1 + 1] - Color) < porog) && (CAD[i1 + cols + j1 + 1] == 0))
				{//right//down
					ist1 = addpoint(stack, stack1, ist, ist1, i1 + cols, j1 + 1);
				}
				if ((j1 < cols - 1) && (i1 > 0) && (abs(Cadr[i1 - cols + j1 + 1] - Color) < porog) && (CAD[i1 - cols + j1 + 1] == 0))
				{//right//up
					ist1 = addpoint(stack, stack1, ist, ist1, i1 - cols, j1 + 1);
				}
				if ((j1 < cols - 1) && (abs(Cadr[i1 + j1 + 1] - Color) < porog) && (CAD[i1 + j1 + 1] == 0))
				{//right
					ist1 = addpoint(stack, stack1, ist, ist1, i1, j1 + 1);
				}
				if ((i1 > 0) && (abs(Cadr[i1 - cols + j1] - Color) < porog) && (CAD[i1 - cols + j1] == 0))
				{//up
					ist1 = addpoint(stack, stack1, ist, ist1, i1 - cols, j1);
				}
				if ((i1 < maxi - cols) && (abs(Cadr[i1 + cols + j1] - Color) < porog) && (CAD[i1 + cols + j1] == 0))
				{//down
					ist1 = addpoint(stack, stack1, ist, ist1, i1 + cols, j1);
				}
     	}
     	while(ist1 > 0)
     	{
     			b = b < ist1 ? ist1 : b;
				a = stack1[ist1];
				stack1[ist1].def = 0;
				j1 = a.j;
				i1 = a.i;
				CAD[i1 + j1] = cnt;
				ist1--;

				Zone.NumPix++;
				Zone.SumBright += Cadr[i1 + j1];
				if(Zone.left > j1) Zone.left = j1;
				if(Zone.right < j1) Zone.right = j1;
				if(Zone.up > i1) Zone.up = i1;
				if(Zone.down < i1) Zone.down = i1;
				Zone.SumBrightX += j1 * Cadr[i1 + j1];
				Zone.SumBrightY += i1 * Cadr[i1 + j1];
				Zone.InvSumBrightX += j1 * (255 - Cadr[i1 + j1]);
				Zone.InvSumBrightY += i1 * (255 - Cadr[i1 + j1]);

				if ((j1 > 0) && (abs(Cadr[i1 + j1 - 1] - Color) < porog) && (CAD[i1 + j1 - 1] == 0))
				{//left
					ist = addpoint(stack1, stack, ist1, ist, i1, j1 - 1);
				}
				if ((j1 > 0) && (i1 > 0) && (abs(Cadr[i1 - cols + j1 - 1] - Color) < porog) && (CAD[i1 - cols + j1 - 1] == 0))
				{//left//up
					ist = addpoint(stack1, stack, ist1, ist, i1 - cols, j1 - 1);
				}
				if ((j1 > 0) && (i1 < maxi - cols) && (abs(Cadr[i1 + cols + j1 - 1] - Color) < porog) && (CAD[i1 + cols + j1 - 1] == 0))
				{//left//down
					ist = addpoint(stack1, stack, ist1, ist, i1 + cols, j1 - 1);
				}
				if ((j1 < cols - 1) && (i1 < maxi - cols) && (abs(Cadr[i1 + cols + j1 + 1] - Color) < porog) && (CAD[i1 + cols + j1 + 1] == 0))
				{//right//down
					ist = addpoint(stack1, stack, ist1, ist, i1 + cols, j1 + 1);
				}
				if ((j1 < cols - 1) && (i1 > 0) && (abs(Cadr[i1 - cols + j1 + 1] - Color) < porog) && (CAD[i1 - cols + j1 + 1] == 0))
				{//right//up
					ist = addpoint(stack1, stack, ist1, ist, i1 - cols, j1 + 1);
				}
				if ((j1 < cols - 1) && (abs(Cadr[i1 + j1 + 1] - Color) < porog) && (CAD[i1 + j1 + 1] == 0))
				{//right
					ist = addpoint(stack1, stack, ist1, ist, i1, j1 + 1);
				}
				if ((i1 > 0) && (abs(Cadr[i1 - cols + j1] - Color) < porog) && (CAD[i1 - cols + j1] == 0))
				{//up
					ist = addpoint(stack1, stack, ist1, ist, i1 - cols, j1);
				}
				if ((i1 < maxi - cols) && (abs(Cadr[i1 + cols + j1] - Color) < porog) && (CAD[i1 + cols + j1] == 0))
				{//down
					ist = addpoint(stack1, stack, ist1, ist, i1 + cols, j1);
				}
     	}
     }
    Zone.up /= cols;
    Zone.down /= cols;
    Zone.SumBrightY /= cols;
    Zone.InvSumBrightY /= cols;
    return Zone;
}
//
//BinaryZone take8sv(Uint8* Cadr, Uint8* CAD, short cols, short rows, int j1, int i1, Uint8 cnt)
//{
//	Uint16 ist = 1, ist1 = 0;
//	RECT a;
//	BinaryZone Zone;
//	int maxi = cols * rows;
//
//    stack[ist].def = i1 + j1;
//    stack[ist].i = i1;
//	stack[ist].j = j1;
//
//	Zone.SumBright = Cadr[i1 + j1];
//	Zone.left = cols;
//	Zone.right = 0;
//	Zone.up = maxi;
//	Zone.down = 0;
//	Zone.NumPix = 0;
//	Zone.SumBrightX = 0;
//	Zone.SumBrightY = 0;
//	Zone.InvSumBrightX = 0;
//	Zone.InvSumBrightY = 0;
//
//
//    while((ist > 0) || (ist1 > 0))
//    {
//     	while(ist > 0)
//     	{
//				a = stack[ist];
//				stack[ist].def = 0;
//				j1 = a.j;
//				i1 = a.i;
//				CAD[i1 + j1] = cnt;
//				ist--;
//
//				Zone.NumPix++;
//				Zone.SumBright += Cadr[i1 + j1];
//				if(Zone.left > j1) Zone.left = j1;
//				if(Zone.right < j1) Zone.right = j1;
//				if(Zone.up > i1) Zone.up = i1;
//				if(Zone.down < i1) Zone.down = i1;
//				Zone.SumBrightX += j1 * Cadr[i1 + j1];
//				Zone.SumBrightY += i1 * Cadr[i1 + j1];
//				Zone.InvSumBrightX += j1 * (255 - Cadr[i1 + j1]);
//				Zone.InvSumBrightY += i1 * (255 - Cadr[i1 + j1]);
//
//				if ((j1 > 0) && (CAD[i1 + j1 - 1] == 0))
//				{//left
//					ist1 = addpoint(stack, stack1, ist, ist1, i1, j1 - 1);
//				}
//				if ((j1 > 0) && (i1 > 0) && (CAD[i1 - cols + j1 - 1] == 0))
//				{//left//up
//					ist1 = addpoint(stack, stack1, ist, ist1, i1 - cols, j1 - 1);
//				}
//				if ((j1 > 0) && (i1 < maxi - cols) && (CAD[i1 + cols + j1 - 1] == 0))
//				{//left//down
//					ist1 = addpoint(stack, stack1, ist, ist1, i1 + cols, j1 - 1);
//				}
//				if ((j1 < cols - 1) && (i1 < maxi - cols) && (CAD[i1 + cols + j1 + 1] == 0))
//				{//right//down
//					ist1 = addpoint(stack, stack1, ist, ist1, i1 + cols, j1 + 1);
//				}
//				if ((j1 < cols - 1) && (i1 > 0) && (CAD[i1 - cols + j1 + 1] == 0))
//				{//right//up
//					ist1 = addpoint(stack, stack1, ist, ist1, i1 - cols, j1 + 1);
//				}
//				if ((j1 < cols - 1) && (CAD[i1 + j1 + 1] == 0))
//				{//right
//					ist1 = addpoint(stack, stack1, ist, ist1, i1, j1 + 1);
//				}
//				if ((i1 > 0) && (CAD[i1 - cols + j1] == 0))
//				{//up
//					ist1 = addpoint(stack, stack1, ist, ist1, i1 - cols, j1);
//				}
//				if ((i1 < maxi - cols) && (CAD[i1 + cols + j1] == 0))
//				{//down
//					ist1 = addpoint(stack, stack1, ist, ist1, i1 + cols, j1);
//				}
//     	}
//     	while(ist1 > 0)
//     	{
//				a = stack1[ist1];
//				stack1[ist1].def = 0;
//				j1 = a.j;
//				i1 = a.i;
//				CAD[i1 + j1] = cnt;
//				ist1--;
//
//				Zone.NumPix++;
//				Zone.SumBright += Cadr[i1 + j1];
//				if(Zone.left > j1) Zone.left = j1;
//				if(Zone.right < j1) Zone.right = j1;
//				if(Zone.up > i1) Zone.up = i1;
//				if(Zone.down < i1) Zone.down = i1;
//				Zone.SumBrightX += j1 * Cadr[i1 + j1];
//				Zone.SumBrightY += i1 * Cadr[i1 + j1];
//				Zone.InvSumBrightX += j1 * (255 - Cadr[i1 + j1]);
//				Zone.InvSumBrightY += i1 * (255 - Cadr[i1 + j1]);
//
//				if ((j1 > 0) && (CAD[i1 + j1 - 1] == 0))
//				{//left
//					ist = addpoint(stack1, stack, ist1, ist, i1, j1 - 1);
//				}
//				if ((j1 > 0) && (i1 > 0) && (CAD[i1 - cols + j1 - 1] == 0))
//				{//left//up
//					ist = addpoint(stack1, stack, ist1, ist, i1 - cols, j1 - 1);
//				}
//				if ((j1 > 0) && (i1 < maxi - cols) && (CAD[i1 + cols + j1 - 1] == 0))
//				{//left//down
//					ist = addpoint(stack1, stack, ist1, ist, i1 + cols, j1 - 1);
//				}
//				if ((j1 < cols - 1) && (i1 < maxi - cols) && (CAD[i1 + cols + j1 + 1] == 0))
//				{//right//down
//					ist = addpoint(stack1, stack, ist1, ist, i1 + cols, j1 + 1);
//				}
//				if ((j1 < cols - 1) && (i1 > 0) && (CAD[i1 - cols + j1 + 1] == 0))
//				{//right//up
//					ist = addpoint(stack1, stack, ist1, ist, i1 - cols, j1 + 1);
//				}
//				if ((j1 < cols - 1) && (CAD[i1 + j1 + 1] == 0))
//				{//right
//					ist = addpoint(stack1, stack, ist1, ist, i1, j1 + 1);
//				}
//				if ((i1 > 0) && (CAD[i1 - cols + j1] == 0))
//				{//up
//					ist = addpoint(stack1, stack, ist1, ist, i1 - cols, j1);
//				}
//				if ((i1 < maxi - cols) && (CAD[i1 + cols + j1] == 0))
//				{//down
//					ist = addpoint(stack1, stack, ist1, ist, i1 + cols, j1);
//				}
//     	}
//    }
//    return Zone;
//}

#define MIN_OBJECT_POINTS 50

BinaryZone Determine_Object(Uint8* Cadr, Uint8* CAD, short cols, short rows, int j1, int i1, Uint8 Color, Uint8 cnt, Uint8 *porog){
    int num_pix_prev, fl_done;
    float num_pix_div_prev, num_pix_div;
	int color_range = 30;
	BinaryZone Object, Object_rez;
	Object.NumPix = 0;
	while(Object.NumPix < MIN_OBJECT_POINTS){
		memset(CAD, 0, MaxCadr);
		Object = fill8sv(Cadr, CAD, cols, rows, j1, i1 * cols, Color, cnt, color_range);
		color_range += 3;
	}
	num_pix_div_prev = Object.NumPix;
	memset(CAD, 0, MaxCadr);
	Object_rez = fill8sv(Cadr, CAD, cols, rows, j1, i1 * cols, Color, cnt, color_range);
	num_pix_div_prev = (float)Object_rez.NumPix / num_pix_div_prev;
	num_pix_prev = Object_rez.NumPix;
	fl_done = 1;
	while(fl_done){
		color_range += 3;
		memset(CAD, 0, MaxCadr);
		Object = fill8sv(Cadr, CAD, cols, rows, j1, i1 * cols, Color, cnt, color_range);
		num_pix_div = (float)Object.NumPix / num_pix_prev;
		if(num_pix_div > num_pix_div_prev) {
			fl_done = 0;
			color_range -= 3;
		}
		else{
			num_pix_prev = Object.NumPix;
			num_pix_div_prev = num_pix_div;
			Object_rez = Object;
		}
	}
	*porog = color_range;
	return Object_rez;
}

BinaryZone Correct_Object(Uint8* Cadr, Uint8* CAD, short cols, short rows, int j1, int i1, Uint8 Color, Uint8 cnt, Uint8 *porog){
    float div_min, div;
	int color_range = *porog;
	BinaryZone Object, Object_down;
	int i, i_rez = 2;
	memset(CAD, 0, MaxCadr);
	Object = fill8sv(Cadr, CAD, cols, rows, j1, i1 * cols, Color, cnt, color_range + i_rez);
	div_min = fabs((float)(EtZone.NumPix - Object.NumPix) / EtZone.NumPix);
	for(i = -2; i < 2; i++){
//		if(i != 0){
			memset(CAD, 0, MaxCadr);
			Object_down = fill8sv(Cadr, CAD, cols, rows, j1, i1 * cols, Color, cnt, color_range + i);
			div = fabs((float)(EtZone.NumPix - Object_down.NumPix) / EtZone.NumPix);
			if(div < div_min){
				div_min = div;
				Object = Object_down;
				i_rez = i;
			}
//		}
	}
//	if(div_down > div_up) {
//		*porog = color_range + 1;
//		Object = Object_up;
//	}
//	else if(Object_down.NumPix > MIN_OBJECT_POINTS) {
//		*porog = color_range - 1;
//		Object = Object_down;
//	}
	*porog = color_range + i_rez;
	return Object;
}


BinaryZone findObjPerim(Uint8* Cadr, Uint8* CAD, int cols, int rows, BinaryZone* Bzones, RECT* stack1, RECT* stack, Uint16 fl_start, Uint32 IsFirst){
//	memset(stack1, 0, sizeof(RECT) * MxSt);
//	memset(CAD, 0, MaxCadr);
    int i;

    static int color_target;
    static Uint8 color_range;
    Uint8 color_range_black, color_range_white;

    volatile int num_pix_prev, fl_done;
    static float num_pix_div_prev;
    float num_pix_div;

	Uint8 min = 255, max = 0;
	int min_i, min_j, max_i, max_j;

    if(fl_start)
    {
		for(i = 0; i < rows * cols; i ++)
		{
			if(min > Cadr[i]){
				min = Cadr[i];
				min_i = i / cols;
				min_j = i % cols;
			}
			if(max < Cadr[i]){
				max = Cadr[i];
				max_i = i / cols;
				max_j = i % cols;
			}
		}

//    	color_range_black = 5;
//    	Bzones[0].NumPix = 0;
//    	while(Bzones[0].NumPix < 100){
//			memset(CAD, 0, MaxCadr);
//			Bzones[0] = fill8sv(Cadr, CAD, cols, rows, min_j, min_i * cols, min, 100, color_range_black);
//			color_range_black += 5;
//		}
//		num_pix_div_prev = Bzones[0].NumPix;
//		memset(CAD, 0, MaxCadr);
//		Bzones[0] = fill8sv(Cadr, CAD, cols, rows, min_j, min_i * cols, min, 100, color_range_black);
//		num_pix_div_prev = (float)Bzones[0].NumPix / num_pix_div_prev;
//		num_pix_prev = Bzones[0].NumPix;
//		fl_done = 1;
//		while(fl_done){
//			color_range_black += 5;
//			memset(CAD, 0, MaxCadr);
//			Bzones[0] = fill8sv(Cadr, CAD, cols, rows, min_j, min_i * cols, min, 100, color_range_black);
//			num_pix_div = (float)Bzones[0].NumPix / num_pix_prev;
//			if(num_pix_div > num_pix_div_prev) {
//				fl_done = 0;
//				color_range_black -= 5;
//			}
//			else{
//				num_pix_prev = Bzones[0].NumPix;
//				num_pix_div_prev = num_pix_div;
//			}
//		}
		Bzones[1] = Determine_Object(Cadr, CAD, cols, rows, max_j, max_i, max, 200, (Uint8*)&color_range_white);
		Bzones[0] = Determine_Object(Cadr, CAD, cols, rows, min_j, min_i, min, 100, (Uint8*)&color_range_black);
		Bzones[0].SumBright = Bzones[0].NumPix * 255 - Bzones[0].SumBright;
		Bzones[0].SumBrightX = Bzones[0].InvSumBrightX;
		Bzones[0].SumBrightY = Bzones[0].InvSumBrightY;

//	   	color_range_white = 5;
//		Bzones[1].NumPix = 0;
//		while(Bzones[1].NumPix < 100){
//			memset(CAD, 0, MaxCadr);
//			Bzones[1] = fill8sv(Cadr, CAD, cols, rows, max_j, max_i * cols, max, 100, color_range_white);
//			color_range_white += 5;
//		}
//		num_pix_div_prev = Bzones[1].NumPix;
//		memset(CAD, 0, MaxCadr);
//		Bzones[1] = fill8sv(Cadr, CAD, cols, rows, max_j, max_i * cols, max, 100, color_range_white);
//		num_pix_div_prev = (float)Bzones[1].NumPix / num_pix_div_prev;
//		num_pix_prev = Bzones[1].NumPix;
//		fl_done = 1;
//		while(fl_done){
//			color_range_white += 5;
//			memset(CAD, 0, MaxCadr);
//			Bzones[1] = fill8sv(Cadr, CAD, cols, rows, max_j, max_i * cols, max, 100, color_range_white);
//			num_pix_div = (float)Bzones[1].NumPix / num_pix_prev;
//			if(num_pix_div > num_pix_div_prev) {
//				fl_done = 0;
//				color_range_white -= 5;
//			}
//			else{
//				num_pix_prev = Bzones[0].NumPix;
//				num_pix_div_prev = num_pix_div;
//			}
//		}

		//проверка границ зон
		for(i = 0; i < 2; i++)
			if(Bzones[i].left <= 1 ||
					Bzones[i].up <= 1 ||
					Bzones[i].right >= cols - 3 ||
					Bzones[i].down >= rows - 3)
				Bzones[i].NumPix = 0;

		if(Bzones[0].NumPix > Bzones[1].NumPix) {
			color_target = 0;
			color_range = color_range_black;
		}
		else {
			color_target = 1;
			color_range = color_range_white;
		}
    }
    else{
    	if(color_target){
			for(i = 0; i < rows * cols; i ++)
				if(max < Cadr[i]){
					max = Cadr[i];
					max_i = i / cols;
					max_j = i % cols;
				}
			Bzones[1] = Correct_Object(Cadr, CAD, cols, rows, max_j, max_i, max, 200, (Uint8*)&color_range);

			if(Bzones[1].left <= 1 ||
					Bzones[1].up <= 1 ||
					Bzones[1].right >= cols - 3 ||
					Bzones[1].down >= rows - 3)
				Bzones[1].NumPix = 0;

//
			Bzones[0] = fill8sv(Cadr, CAD, cols, rows, max_j, max_i * cols, max, 200, color_range);
			Bzones[1] = fill8sv(Cadr, CAD, cols, rows, max_j, max_i * cols, max, 200, color_range-1);
			Bzones[2] = fill8sv(Cadr, CAD, cols, rows, max_j, max_i * cols, max, 200, color_range+1);
			num_pix_div_prev = (float)Bzones[0].NumPix / Bzones[1].NumPix;
			num_pix_div = (float)Bzones[2].NumPix / Bzones[0].NumPix;
			if(num_pix_div > num_pix_div_prev && Bzones[1].NumPix > 50) {
				color_range--;
//				num_pix_div_prev = num_pix_div;
			}
//			num_pix_div = (float)Bzones[2].NumPix / Bzones[0].NumPix;
			if(num_pix_div <= num_pix_div_prev) {
				color_range++;
//				num_pix_div_prev = num_pix_div;
			}
    	}
    	else{
			for(i = 0; i < rows * cols; i ++)
				if(min > Cadr[i]){
					min = Cadr[i];
					min_i = i / cols;
					min_j = i % cols;
				}
//			Bzones[0] = Determine_Object(Cadr, CAD, cols, rows, min_j, min_i, min, 100, (Uint8*)&color_range_black);
//			Bzones[0] = Correct_Object(Cadr, CAD, cols, rows, min_j, min_i, min, 100, (Uint8*)&color_range);
			memset(CAD, 0, MaxCadr);
			Bzones[0] = fill8sv(Cadr, CAD, cols, rows, min_j, min_i * cols, min, 100, color_range);
			memset(CAD, 0, MaxCadr);
			Bzones[1] = fill8sv(Cadr, CAD, cols, rows, min_j, min_i * cols, min, 100, color_range-1);
			memset(CAD, 0, MaxCadr);
			Bzones[2] = fill8sv(Cadr, CAD, cols, rows, min_j, min_i * cols, min, 100, color_range+1);
			num_pix_div_prev = (float)Bzones[0].NumPix / Bzones[1].NumPix;
			num_pix_div = (float)Bzones[2].NumPix / Bzones[0].NumPix;
			if(num_pix_div > num_pix_div_prev && Bzones[1].NumPix > 50) {
				color_range--;
//				num_pix_div_prev = num_pix_div;
			}
//			num_pix_div = (float)Bzones[2].NumPix / Bzones[0].NumPix;
			if(num_pix_div <= num_pix_div_prev) {
				color_range++;
//				num_pix_div_prev = num_pix_div;
			}

			Bzones[0].SumBright = Bzones[0].NumPix * 255 - Bzones[0].SumBright;
			Bzones[0].SumBrightX = Bzones[0].InvSumBrightX;
			Bzones[0].SumBrightY = Bzones[0].InvSumBrightY;
			if(Bzones[0].left <= 1 ||
					Bzones[0].up <= 1 ||
					Bzones[0].right >= cols - 3 ||
					Bzones[0].down >= rows - 3)
				Bzones[0].NumPix = 0;
   	}
    	if(color_range < 30) color_range = 10;
    	if(color_range > 100) color_range = 100;

    }

//	//проверка границ зон
//	for(i = 0; i < 2; i++)
//		if(Bzones[i].left <= 1 ||
//				Bzones[i].up <= 1 ||
//				Bzones[i].right >= cols - 3 ||
//				Bzones[i].down >= rows - 3)
//			Bzones[i].NumPix = 0;



//	if(Bzones[i].NumPix > 100) color_range--;
//	if(Bzones[i].NumPix < 50) color_range++;
//	if(color_range > 100) color_range = 100;
//	if(color_range < 10) color_range = 10;

    return Bzones[color_target];
}

//BinaryZone findObjPerim(Uint8* Cadr, Uint8* CAD, int cols, int rows, BinaryZone* Bzones, RECT* stack1, RECT* stack, Uint16 fl_start, Uint32 IsFirst){
////	memset(stack1, 0, sizeof(RECT) * MxSt);
//	memset(CAD, 0, MaxCadr);
//    int i;
//    static int color_range = 30;
//    static int color_target = 2;
//
//	Uint8 min = 255, max = 0;
//	int min_i, min_j, max_i, max_j;
//
//    if(fl_start) {
//    	color_range = 30;
//    	color_target = 2;
//    }
//    if(color_target == 2 || color_target == 0)
//    {
//		for(i = 0; i < rows * cols; i ++)
//			if(min > Cadr[i]){
//				min = Cadr[i];
//				min_i = i / cols;
//				min_j = i % cols;
//			}
//		Bzones[0] = fill8sv(Cadr, CAD, cols, rows, min_j, min_i * cols, min, 100, 30);
//		Bzones[0].SumBright = Bzones[0].NumPix * 255 - Bzones[0].SumBright;
//		Bzones[0].SumBrightX = Bzones[0].InvSumBrightX;
//		Bzones[0].SumBrightY = Bzones[0].InvSumBrightY;
//    }
//    if(color_target == 2 || color_target == 1)
//    {
//		for(i = 0; i < rows * cols; i ++)
//			if(max < Cadr[i]){
//				max = Cadr[i];
//				max_i = i / cols;
//				max_j = i % cols;
//			}
//		Bzones[1] = fill8sv(Cadr, CAD, cols, rows, max_j, max_i * cols, max, 200, 30);
//    }
//
//	//проверка границ зон
//	for(i = 0; i < 2; i++)
//		if(Bzones[i].left <= 1 ||
//				Bzones[i].up <= 1 ||
//				Bzones[i].right >= cols - 3 ||
//				Bzones[i].down >= rows - 3)
//			Bzones[i].NumPix = 0;
//
//	if(Bzones[0].NumPix > Bzones[1].NumPix) color_target = 0;
//	else color_target = 1;
//
////	if(Bzones[i].NumPix > 100) color_range--;
////	if(Bzones[i].NumPix < 50) color_range++;
//	if(color_range > 100) color_range = 100;
//	if(color_range < 10) color_range = 10;
//
//    return Bzones[color_target];
//}


/*
Uint32 SumAbsSub2Line4x(Uint32, Uint32, Uint32, Uint32, Uint32);
Uint32 SumAbsSubLine4x(Uint32, Uint32, Uint32);
*/
/*
extern Uint16 MassCor[12 * 2 + 1][22 * 2 + 1];
extern Uint16 MassCorR[12 * 2 + 1][22 * 2 + 1];
extern Uint16 MaxCor, MinCor;
*/
/*
//Поиск смещения в стробе эталона заданного смещением в другом стробе
//Поиск осуществляется путем расчета квадрата 5х5 в центре строба и дальнейшим смещением квадрата по стробу
//в сторону увеличения коррляции
//et 		- адрес строба источника эталона
//smyetst 	- смещение по вертикали эталона в стробе источнике
//smxetst 	- смещение по горизонтали эталона в стробе источнике
//st 		- адрес строба поиска
//colsEt	- число столбцов эталона
//rowsEt	- число строк эталона
//colsEtSt	- число столбцов строба источника
//colsSt	- число столбцов строба
//rowsSt	- число строк строба
//rezult	- адрес структуры содржащей итоговое смещение
float PartFastCorrFullFromPrevSt(Uint32 et, Uint32 smyetst, Uint32 smxetst, Uint32 smpy, Uint32 smpx, Uint32 st, Uint32 colsEt, Uint32 rowsEt, Uint32 colsEtSt, Uint32 colsSt, Uint32 rowsSt, Uint32 rezult, Uint32 bcols, Uint32 brows){
	Uint16* rez = (Uint16*)rezult;
	float rmin = 1000.0, rf, rmid = 0, divider = colsEt * rowsEt;
	Uint16 r, sx, sy, smy;
	Uint32 syet, smySt, smyEtSt;
	Uint32 n1 = rowsEt >> 1, nu = n1 << 1;
	smyetst = (smyetst + smpy) * colsEtSt;
	float zz = rmin, divmed = 25;
	int sx1 = bcols - 2, sx2 = bcols + 2;
	int sy1 = brows - 2, sy2 = brows + 2;
	Uint32 end = 1;
	while(end > 0){
		smy = 0;
		for(sy = sy1; sy <= sy2; sy++){
			for(sx = sx1; sx <= sx2; sx++){
				smySt = colsSt * (sy1 + smpy);
				smyEtSt = 0;
				r = 0;
				//накопление суммы модулей разностей с заданным смещением
				for(syet = 0; syet < rowsEt - 1; syet +=2){//переход к следующей паре строк
					//расчет 2-х строк
					r += SumAbsSub2Line4x(et + smyEtSt + smyetst + smxetst + smpx, st + sx + smy + smySt + smpx, et + smyEtSt + colsEtSt  + smyetst + smxetst + smpx, st + sx + smy + smySt + colsSt + smpx, colsEt);
					//смещение для следующей пары строк
					smySt += colsSt << 1;
					smyEtSt += colsEtSt << 1;
				}
				//если число строк нечётное
				if (nu < rowsEt){
					r += SumAbsSubLine4x(et + smyEtSt + smyetst + smxetst + smpx, st + sx + smy + smySt, colsEt);
				}
				//расчет коэф корреляции
				rf = (float)r/divider;
				rmid += rf;
				MassCor[sy][sx] += (Uint8)rf;
				if(rf < rmin) {//выбор минимума и сохранение
					rmin = rf;
					rez[0] = sx;
					rez[1] = sy;
				}
			}
			smy += colsSt;
		}
		end = 0;
		if(rmin < zz)
		{
			zz = rmin;
			if(rez[0] == sx1)		{sx1 -= 5;		sx2 -= 5;	end = 1;}
			if(rez[0] == sx2)		{sx2 += 5;		sx1 += 5;	end = 1;}
			if(rez[1] == sy1)		{sy1 -= 5;		sy2 -= 5;	end = 1;}
			if(rez[1] == sy2)		{sy2 += 5;		sy1 += 5;	end = 1;}
		}
		if((sx1 < 0) || (sy1 < 0) || (sx2 > ((bcols << 1) + 1)) || (sy2 > ((brows << 1) + 1))) end = 0;
	}
	return (1 - (rmin * divmed / rmid));
}
*/

/*
float PartFastCorrFullFromPrevSt0(Uint32 et, Uint32 smyetst, Uint32 smxetst, Uint32 smpy, Uint32 smpx, Uint32 st, Uint32 colsEt, Uint32 rowsEt, Uint32 colsEtSt, Uint32 colsSt, Uint32 rowsSt, Uint32 rezult, Uint32 bcols, Uint32 brows, Uint32 IsmallX, Uint32 IsmallY){
	Uint16* rez = (Uint16*)rezult;
	float rmin = 1000.0, rmax = 0.0, rf, divider = colsEt * rowsEt;
	Uint32 r, sx, sy, smy;
	Uint32 syet, smySt, smyEtSt;
	Uint32 n1 = rowsEt >> 1, nu = n1 << 1;
	smyetst = (smyetst + smpy) * colsEtSt;
	float zz = rmin;

	int sx1, sx2, sy1, sy2;

	if(IsmallX == 1) { sx1 = 0; sx2 = (bcols << 1);}
	else {sx1 = bcols - 2, sx2 = bcols + 2;}

	if(IsmallY == 1) { sy1 = 0; sy2 = (brows << 1);}
	else {sy1 = brows - 2, sy2 = brows + 2;}
	Uint32 end = 1;
	while(end > 0){
		smy = 0;
		for(sy = sy1; sy <= sy2; sy++){
			for(sx = sx1; sx <= sx2; sx++){
				smySt = colsSt * (sy1 + smpy);
				smyEtSt = 0;
				r = 0;
				//накопление суммы модулей разностей с заданным смещением
				for(syet = 0; syet < rowsEt - 1; syet +=2){//переход к следующей паре строк
					//расчет 2-х строк
					r += SumAbsSub2Line4x(et + smyEtSt + smyetst + smxetst + smpx, st + sx + smy + smySt + smpx, et + smyEtSt + colsEtSt  + smyetst + smxetst + smpx, st + sx + smy + smySt + colsSt + smpx, colsEt);
					//смещение для следующей пары строк
					smySt += colsSt << 1;
					smyEtSt += colsEtSt << 1;
				}
				//если число строк нечётное
				if (nu < rowsEt){
					r += SumAbsSubLine4x(et + smyEtSt + smyetst + smxetst + smpx, st + sx + smy + smySt, colsEt);
				}
				//расчет коэф корреляции
				rf = (float)r/divider;
//				rmid += rf;
//				MassCor[sy][sx] = (Uint16)rf;
				if(rf < rmin) {//выбор минимума и сохранение
					rmin = rf;
					rez[0] = sx;
					rez[1] = sy;
				}
				if(rf > rmax) rmax = rf;
			}
			smy += colsSt;
		}
		end = 0;
		if(rmin < zz)
		{
			zz = rmin;
			if(rez[0] == sx1)		{sx1 -= 5;		sx2 -= 5;	end = 1;}
			if(rez[0] == sx2)		{sx2 += 5;		sx1 += 5;	end = 1;}
			if(rez[1] == sy1)		{sy1 -= 5;		sy2 -= 5;	end = 1;}
			if(rez[1] == sy2)		{sy2 += 5;		sy1 += 5;	end = 1;}
		}
		if((sx1 < 0) || (sy1 < 0) || (sx2 > ((bcols << 1) + 1)) || (sy2 > ((brows << 1) + 1))) end = 0;
	}
	return rmin;
}
*/
/*

//Поиск смещения в стробе эталона заданного смещением в другом стробе
//Поиск осуществляется путем расчета квадрата 5х5 в центре строба и дальнейшим смещением квадрата по стробу
//в сторону увеличения коррляции
//et 		- адрес строба источника эталона
//smyetst 	- смещение по вертикали эталона в стробе источнике
//smxetst 	- смещение по горизонтали эталона в стробе источнике
//st 		- адрес строба поиска
//colsEt	- число столбцов эталона
//rowsEt	- число строк эталона
//colsEtSt	- число столбцов строба источника
//colsSt	- число столбцов строба
//rowsSt	- число строк строба
//rezult	- адрес структуры содржащей итоговое смещение
float FastCorrFullFromPrevSt(Uint32 et, Uint32 smyetst, Uint32 smxetst, Uint32 st, Uint32 colsEt, Uint32 rowsEt, Uint32 colsEtSt, Uint32 colsSt, Uint32 rowsSt, Uint32 rezult, Uint32 bcols, Uint32 brows){
	Uint16* rez = (Uint16*)rezult;
	float rmin = 1000.0, rf, rmid = 0, divider = colsEt * rowsEt;
	Uint16 r, sx, sy, smy;
	Uint32 syet, smySt, smyEtSt;
	Uint32 x_max = colsSt - colsEt;
	Uint32 y_max = rowsSt - rowsEt;
	Uint32 n1 = rowsEt >> 1, nu = n1 << 1;
	smyetst *= colsEtSt;
	float zz = rmin, divmed = 25;
	int sx1 = bcols - 2, sx2 = bcols + 2;
	int sy1 = brows - 2, sy2 = brows + 2;
	Uint32 end = 1;
	while(end > 0){
		smy = 0;
		for(sy = sy1; sy <= sy2; sy++){
			for(sx = sx1; sx <= sx2; sx++){
				smySt = colsSt * sy1;
				smyEtSt = 0;
				r = 0;
				//накопление суммы модулей разностей с заданным смещением
				for(syet = 0; syet < rowsEt - 1; syet +=2){//переход к следующей паре строк
					//расчет 2-х строк
					r += SumAbsSub2Line4x(et + smyEtSt + smyetst + smxetst, st + sx + smy + smySt, et + smyEtSt + colsEtSt  + smyetst + smxetst, st + sx + smy + smySt + colsSt, colsEt);
					//смещение для следующей пары строк
					smySt += colsSt << 1;
					smyEtSt += colsEtSt << 1;
				}
				//если число строк нечётное
				if (nu < rowsEt){
					r += SumAbsSubLine4x(et + smyEtSt + smyetst + smxetst, st + sx + smy + smySt, colsEt);
				}
				//расчет коэф корреляции
				rf = (float)r/divider;
				rmid += rf;
				MassCor[sy][sx] = (Uint8)rf;
				if(rf < rmin) {//выбор минимума и сохранение
					rmin = rf;
					rez[0] = sx;
					rez[1] = sy;
				}
			}
			smy += colsSt;
		}
		end = 0;
		if(rmin < zz)
		{
			zz = rmin;
			if(rez[0] == sx1)		{sx1 -= 5;		sx2 -= 5;	end = 1;}
			if(rez[0] == sx2)		{sx2 += 5;		sx1 += 5;	end = 1;}
			if(rez[1] == sy1)		{sy1 -= 5;		sy2 -= 5;	end = 1;}
			if(rez[1] == sy2)		{sy2 += 5;		sy1 += 5;	end = 1;}
		}
		if((sx1 < 0) || (sy1 < 0) || (sx2 > x_max) || (sy2 > y_max)) end = 0;
	}
	return (1 - (rmin * divmed / rmid));
}
*/
/*
Uint32 SumAbsSub2Line4x(Uint32 addr_a0, Uint32 addr_b0, Uint32 addr_a1, Uint32 addr_b1, Uint32 n){//сумма модулей разностей по линии кратной 4-м
	//Нулевая строка
	Uint32 a0n, b0n;
	Uint32 a0b0, a0b1;
	Uint32 b0b0, b0b1;
	Uint8* a0 = (Uint8*)addr_a0;
	Uint8* b0 = (Uint8*)addr_b0;
	//Первая строка
	Uint32 a1n, b1n;
	Uint32 a1b0, a1b1;
	Uint32 b1b0, b1b1;
	Uint8* a1 = (Uint8*)addr_a1;
	Uint8* b1 = (Uint8*)addr_b1;

	Uint32 rez = 0;
	Uint32 i;
	Uint32 j0 = 0, j1 = 1, j2 = 2, j3 = 3;

	Uint32 n1 = n >> 2, nu = n1 << 2;

	for(i = 0; i < n1 ;i++){

		a0b0 = _packl4(a0[j0], a0[j1]);	//0102
		a0b1 = _packl4(a0[j2], a0[j3]);	//0304
		a0n = _packl4(a0b0, a0b1);		//1234

		b0b0 = _packl4(b0[j0], b0[j1]);
		b0b1 = _packl4(b0[j2], b0[j3]);
		b0n = _packl4(b0b0, b0b1);

		rez += _dotpu4(_subabs4(a0n, b0n), 0x01010101);		//накопление сумм модулей разниц 4-х элементов

		a1b0 = _packl4(a1[j0], a1[j1]);	//0102
		a1b1 = _packl4(a1[j2], a1[j3]);	//0304
		a1n = _packl4(a1b0, a1b1);		//1234

		b1b0 = _packl4(b1[j0], b1[j1]);
		b1b1 = _packl4(b1[j2], b1[j3]);
		b1n = _packl4(b1b0, b1b1);

		rez += _dotpu4(_subabs4(a1n, b1n), 0x01010101);		//накопление сумм модулей разниц 4-х элементов

		j0 += 4;
		j1 += 4;
		j2 += 4;
		j3 += 4;

	}

	if (nu < n){
		for(i = nu; i < n ;i++){
			rez += abs(a0[i] - b0[i]);
			rez += abs(a1[i] - b1[i]);
		}
	}
	return rez;
}

Uint32 SumAbsSubLine4x(Uint32 addr_a0, Uint32 addr_b0, Uint32 n){//сумма модулей разностей по линии кратной 4-м
	//Нулевая строка
	Uint32 a0n, b0n;
	Uint32 a0b0, a0b1;
	Uint32 b0b0, b0b1;
	Uint8* a0 = (Uint8*)addr_a0;
	Uint8* b0 = (Uint8*)addr_b0;

	Uint32 rez = 0;
	Uint32 i;
	Uint32 j0 = 0, j1 = 1, j2 = 2, j3 = 3;

	Uint32 n1 = n >> 2, nu = n1 << 2;

	for(i = 0; i < n1 ;i++){

		a0b0 = _packl4(a0[j0], a0[j1]);	//0102
		a0b1 = _packl4(a0[j2], a0[j3]);	//0304
		a0n = _packl4(a0b0, a0b1);		//1234

		b0b0 = _packl4(b0[j0], b0[j1]);
		b0b1 = _packl4(b0[j2], b0[j3]);
		b0n = _packl4(b0b0, b0b1);

		rez += _dotpu4(_subabs4(a0n, b0n), 0x01010101);		//накопление сумм модулей разниц 4-х элементов

		j0 += 4;
		j1 += 4;
		j2 += 4;
		j3 += 4;

	}

	if (nu < n){
		for(i = nu; i < n ;i++){
			rez += abs(a0[i] - b0[i]);
		}
	}
	return rez;
}
*/

/*
//Поиск смещения в стробе эталона заданного смещением в другом стробе
//расчет всех значений корреляции для каждого смещения и выбор минимальной корреляции
//в сторону увеличения коррляции
//et 		- адрес строба источника эталона
//smyetst 	- смещение по вертикали эталона в стробе источнике
//smxetst 	- смещение по горизонтали эталона в стробе источнике
//st 		- адрес строба поиска
//colsEt	- число столбцов эталона
//rowsEt	- число строк эталона
//colsEtSt	- число столбцов строба источника
//colsSt	- число столбцов строба
//rowsSt	- число строк строба
//rezult	- адрес структуры содржащей итоговое смещение
float CorrFullFromPrevSt(Uint32 et, Uint32 smyetst, Uint32 smxetst, Uint32 st, Uint32 colsEt, Uint32 rowsEt, Uint32 colsEtSt, Uint32 colsSt, Uint32 rowsSt, Uint32 rezult){
	Uint32* rez = (Uint32*)rezult;
	Uint32 rmin = 1000.0, rf, rmid = 0, divider = colsEt * rowsEt;
	Uint32 r, sx, sy, smy = 0;
	Uint32 syet, smySt, smyEtSt;
	Uint32 x_max = colsSt - colsEt;
	Uint32 y_max = rowsSt - rowsEt;
	Uint32 n1 = rowsEt >> 1, nu = n1 << 1;
	smyetst *= colsEtSt;
		for(sy = 0; sy < y_max; sy++){//смещение по у
			for(sx = 0; sx < x_max; sx++){//смещение по х
				smySt = 0;
				smyEtSt = 0;
				r = 0;
				//накопление суммы модулей разностей с заданным смещением
				for(syet = 0; syet < rowsEt - 1; syet +=2){//переход к следующей паре строк
					//расчет 2-х строк
					r += SumAbsSub2Line4x(et + smyEtSt + smyetst + smxetst, st + sx + smy + smySt, et + smyEtSt + colsEtSt  + smyetst + smxetst, st + sx + smy + smySt + colsSt, colsEt);
					//смещение для следующей пары строк
					smySt += colsSt << 1;
					smyEtSt += colsEtSt << 1;
				}
				//если число строк нечётное
				if (nu < rowsEt){
					r += SumAbsSubLine4x(et + smyEtSt + smyetst + smxetst, st + sx + smy + smySt, colsEt);
				}
				//расчет коэф корреляции
				rf = (float)r/divider;
				rmid += rf;
				if(rf < rmin) {//выбор минимума и сохранение
					rmin = rf;
					rez[0] = sx;
					rez[1] = sy;
				}
			}
			smy += colsSt;
		}
	return (1.0 - ((double)(rmin * divider) / rmid));
}
*/
//#pragma DATA_SECTION (H, "cL2RAM");
Uint16 H[180][500];

//#pragma DATA_SECTION (H1, "cL2RAM");
Uint16 H1[4][500];

//#pragma DATA_SECTION (H2, "cL2RAM");
Uint16 H2[500];

int HistLine[11];


Uint16 haf(Uint32 Data, Uint16 cols, Uint16 rows, Uint16 num){
	memset(H, 0, 2*180*500);
	memset(H1, 0, 2*4*500);
	memset(H2, 0, 2*500);
	Uint16 tMax, HMax = 0, Rmax;//длина и угол перпендикулярной линии
//	Uint16  HMaxP = 0, tMaxP;
	Uint16 rRazm = 500;
	int zz, i, j;
	Uint16 t, t1, t2, t3, r, r1, r2, r3;
	Uint8* buf = (Uint8*)Data;
	for(i = 0; i < rows; i++){//первичный расчет угла
		for(j = 0; j < cols; j++)
			if((*buf++ == num) && ((j < 22) || (j > cols - 22))){//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				zz = _pack2(i,j);
#pragma UNROLL(5);
				for(t = 0, t1 = 15, t2 = 150, t3 = 165; t < 15; t+=3, t1+=3, t2+=3, t3+=3){
					r = (_dotp2(cossin[t], zz)>>14) + cols;	//r = ((i * cos1[t] + j * sin1[t])>>14) + cols;
					r1 = (_dotp2(cossin[t1], zz)>>14) + cols;
					r2 = (_dotp2(cossin[t2], zz)>>14) + cols;
					r3 = (_dotp2(cossin[t3], zz)>>14) + cols;
					H[t][r]++;
					H[t1][r1]++;
					H[t2][r2]++;
					H[t3][r3]++;
				}
			}
	}
	for (t = 0; t < 30; t += 3){
		for(r = 0; r < rRazm; r ++){
			if (H[t][r] > HMax) {HMax = H[t][r]; tMax = t; Rmax = r;}
		}
	}
	for (t = 150; t < 180; t += 3){
		for(r = 0; r < rRazm; r ++){
			if (H[t][r] > HMax) {HMax = H[t][r]; tMax = t; Rmax = r;}
		}
	}
	buf = (Uint8*)Data;////восстановления адреса
	Uint16 tmm2 = tMax-2, tmm1 = tMax-1, tmp1 = tMax+1, tmp2 = tMax+2;
	if(tMax == 0){
		tmm2 = 178;
		tmm1 = 179;
	}
	for(i = 0; i < rows; i++){//уточненный расчет угла
		for(j = 0; j < cols; j++){
			if(*buf++ == num && (j < 22 || j > (cols - 22))){
				zz = _pack2(i,j);
				r = (_dotp2(cossin[tmm2], zz)>>14) + cols;	//r = ((i * cos1[t] + j * sin1[t])>>14) + cols;
				r1 = (_dotp2(cossin[tmm1], zz)>>14) + cols;
				r2 = (_dotp2(cossin[tmp1], zz)>>14) + cols;
				r3 = (_dotp2(cossin[tmp2], zz)>>14) + cols;
				H1[0][r]++;
				H1[1][r1]++;
				H1[2][r2]++;
				H1[3][r3]++;
			}
		}
	}
	for(r = 0; r < rRazm; r++){
		if (H1[0][r] > HMax) {HMax = H1[0][r]; tMax = tmm2; Rmax = r;}
		if (H1[1][r] > HMax) {HMax = H1[1][r]; tMax = tmm1; Rmax = r;}
		if (H1[2][r] > HMax) {HMax = H1[2][r]; tMax = tmp1; Rmax = r;}
		if (H1[3][r] > HMax) {HMax = H1[3][r]; tMax = tmp2; Rmax = r;}
	}
	int porog;
	if(HMax > 3*(22 >> 3))//удаление линии
	{
		double tpi180 = tMax * 0.017453;//	pi/180 = 0.017453
		double a = -tan(tpi180);
		double b = (Rmax - cols + 1)/cos(tpi180);
		Uint32 y;
		Uint8 *out, *out1;
		int cnt;
		int size = 5;
		memset(HistLine, 0, 11 * 4);
		for(j = 0; j < 22; j++)//расчет ширины линии
		{
			y = (Uint32)(a * j + b);
			out = (Uint8*)Data + (y - size) * cols + j;
			out1 = out;
			cnt = 0;
			for(i = -size; i <= size; i++, out += cols)//проверка ширины линии
				cnt += *out;
			cnt /= 255;
			HistLine[cnt]++;
		}
		for(j = cols - 22; j < cols; j++)//расчет ширины линии
		{
			y = (Uint32)(a * j + b);
			out = (Uint8*)Data + (y - size) * cols + j;
			out1 = out;
			cnt = 0;
			for(i = -size; i <= size; i++, out += cols)//проверка ширины линии
				cnt += *out;
			cnt /= 255;
			HistLine[cnt]++;
		}
		cnt = 0;
		for(j = 0; j < 11; j++)
			if (HistLine[j] > cnt)
			{
				cnt = HistLine[j];
				porog = j + 2;
			}
		porog *= 255;
		j = 0;
		int done = 0;

		while(done == 0)//слеваа направо
		{
			y = (Uint32)(a * j + b);
			out = (Uint8*)Data + (y - size) * cols + j;
			out1 = out;
			cnt = 0;
			for(i = -size; i <= size; i++, out += cols)//проверка ширины линии
				cnt += *out;
			if (cnt > porog) done = 1;
			for(i = -size; i <= size; i++, out1 += cols)//удаление линии
				*out1 = 0;
			j++;
			if (j >= cols) done = 1;
		}
		done = 0;
		zz = cols - 1;
		while(done == 0)//справа налево
		{
			y = (Uint32)(a * zz + b);
			out = (Uint8*)Data + (y - size) * cols + zz;
			out1 = out;
			cnt = 0;
			for(i = -size; i <= size; i++, out += cols)//проверка ширины линии
				cnt += *out;
			if (cnt > porog) done = 1;
			for(i = -size; i <= size; i++, out1 += cols)//удаление линии
				*out1 = 0;
			zz--;
			if (zz <= j) done = 1;
		}

	}
	return porog;
}


/*
Uint16 haf(Uint32 Data, Uint16 cols, Uint16 rows, Uint16 num){
	memset(H, 0, 2*180*500);
	memset(H1, 0, 2*4*500);
	memset(H2, 0, 2*500);
	Uint16 tMax, HMax = 0, Rmax;//длина и угол перпендикулярной линии
//	Uint16  HMaxP = 0, tMaxP;
	Uint16 rRazm = 500;
	int zz, i, j;
	Uint16 t, t1, t2, t3, r, r1, r2, r3;
	Uint8* buf = (Uint8*)Data;
	for(i = 0; i < rows; i++){//первичный расчет угла
		for(j = 0; j < cols; j++){
			if(*buf++ == num){//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				zz = _pack2(i,j);
#pragma UNROLL(5);
				for(t = 0, t1 = 15, t2 = 150, t3 = 165; t < 15; t+=3, t1+=3, t2+=3, t3+=3){
					r = (_dotp2(cossin[t], zz)>>14) + cols;	//r = ((i * cos1[t] + j * sin1[t])>>14) + cols;
					r1 = (_dotp2(cossin[t1], zz)>>14) + cols;
					r2 = (_dotp2(cossin[t2], zz)>>14) + cols;
					r3 = (_dotp2(cossin[t3], zz)>>14) + cols;
					H[t][r]++;
					H[t1][r1]++;
					H[t2][r2]++;
					H[t3][r3]++;
				}
			}
		}
	}
	for (t = 0; t < 30; t += 3){
		for(r = 0; r < rRazm; r ++){
			if (H[t][r] > HMax) {HMax = H[t][r]; tMax = t; Rmax = r;}
		}
	}
	for (t = 150; t < 180; t += 3){
		for(r = 0; r < rRazm; r ++){
			if (H[t][r] > HMax) {HMax = H[t][r]; tMax = t; Rmax = r;}
		}
	}
	buf = (Uint8*)Data;////восстановления адреса
	Uint16 tmm2 = tMax-2, tmm1 = tMax-1, tmp1 = tMax+1, tmp2 = tMax+2;
	if(tMax == 0){
		tmm2 = 178;
		tmm1 = 179;
	}
	for(i = 0; i < rows; i++){//уточненный расчет угла
		for(j = 0; j < cols; j++){
			if(*buf++ == num){
				zz = _pack2(i,j);
				r = (_dotp2(cossin[tmm2], zz)>>14) + cols;	//r = ((i * cos1[t] + j * sin1[t])>>14) + cols;
				r1 = (_dotp2(cossin[tmm1], zz)>>14) + cols;
				r2 = (_dotp2(cossin[tmp1], zz)>>14) + cols;
				r3 = (_dotp2(cossin[tmp2], zz)>>14) + cols;
				H1[0][r]++;
				H1[1][r1]++;
				H1[2][r2]++;
				H1[3][r3]++;
			}
		}
	}
	for(r = 0; r < rRazm; r++){
		if (H1[0][r] > HMax) {HMax = H1[0][r]; tMax = tmm2; Rmax = r;}
		if (H1[1][r] > HMax) {HMax = H1[1][r]; tMax = tmm1; Rmax = r;}
		if (H1[2][r] > HMax) {HMax = H1[2][r]; tMax = tmp1; Rmax = r;}
		if (H1[3][r] > HMax) {HMax = H1[3][r]; tMax = tmp2; Rmax = r;}
	}
	int porog;
	if(HMax > 3*(cols >> 4))//удаление линии
	{
		double tpi180 = tMax * 0.017453;//	pi/180 = 0.017453
		double a = -tan(tpi180);
		double b = (Rmax - cols + 1)/cos(tpi180);
		Uint32 y;
		Uint8 *out, *out1;
		int cnt;
		int size = 5;
		memset(HistLine, 0, 11 * 4);
		for(j = 0; j < cols; j++)//расчет ширины линии
		{
			y = (Uint32)(a * j + b);
			out = (Uint8*)Data + (y - size) * cols + j;
			out1 = out;
			cnt = 0;
			for(i = -size; i <= size; i++, out += cols)//проверка ширины линии
				cnt += *out;
			cnt /= 255;
			HistLine[cnt]++;
		}
		cnt = 0;
		for(j = 0; j < 11; j++)
			if (HistLine[j] > cnt)
			{
				cnt = HistLine[j];
				porog = j + 1;
			}
		porog *= 255;
		j = 0;
		int done = 0;

		while(done == 0)//слеваа направо
		{
			y = (Uint32)(a * j + b);
			out = (Uint8*)Data + (y - size) * cols + j;
			out1 = out;
			cnt = 0;
			for(i = -size; i <= size; i++, out += cols)//проверка ширины линии
				cnt += *out;
			if (cnt > porog) done = 1;
			for(i = -size; i <= size; i++, out1 += cols)//удаление линии
				*out1 = 0;
			j++;
			if (j >= cols) done = 1;
		}
		done = 0;
		zz = cols - 1;
		while(done == 0)//справа налево
		{
			y = (Uint32)(a * zz + b);
			out = (Uint8*)Data + (y - size) * cols + zz;
			out1 = out;
			cnt = 0;
			for(i = -size; i <= size; i++, out += cols)//проверка ширины линии
				cnt += *out;
			if (cnt > porog) done = 1;
			for(i = -size; i <= size; i++, out1 += cols)//удаление линии
				*out1 = 0;
			zz--;
			if (zz <= j) done = 1;
		}

	}
	return porog;
}
*/

int CleanMemory(Uint32 addr, Uint32 cnt)
{
	Uint32* a = (Uint32*)addr;
	int i;
	for(i = 0; i < cnt >> 2; i++) *a++ = 0;
	return 0;
}

short EihgtSv(Uint8* Cadr, Uint32 rows, Uint32 cols){
	CleanMemory((Uint32)&stack, 1024 * sizeof(RECT));
    int i ,j ,i1 , j1 ;
    int ist, def;
    Uint32 maxi = cols * rows;
    Uint32 maxicmp = cols * (rows - 1);
    Uint32 colscmp = cols - 1;
    short cnt = 0, num = 255;
    BinaryZone b;
    CleanMemory((Uint32)&b, 1 * sizeof(BinaryZone));
    for(i = 0; i < maxi; i += cols){
        for(j = 0; j < cols; j++){
            if (Cadr[i + j] == num){
                cnt++;
                if(cnt > 253) break;
                ist=0;
              	Cadr[i + j] = cnt;
               	j1 = j;
               	i1 = i;
               	def = 0;

                b.NumPix = 1;
                b.left = j1;
                b.up = i1;
                b.right = j1;
                b.down = i1;

                while(ist>=0){
					switch (def){
						case 0:
							if ((j1 > 0) && (Cadr[i1 + j1 - 1] == num)){//left
									stack[ist].def = 4;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;

									j1 -= 1;
									def = 0;
					               	Cadr[i1 + j1] = cnt;

					               	b.NumPix++;
									if(b.left > j1) b.left = j1;
									if(b.right < j1) b.right = j1;
									if(b.up > i1) b.up = i1;
									if(b.down < i1) b.down = i1;
									break;
							}
						case 4:
							if ((j1 > 0) && (i1 > 0) && (Cadr[i1 - cols + j1 - 1] == num)){//left//up
									stack[ist].def = 5;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;

									i1 -= cols;
									j1 -= 1;
									def = 0;
					               	Cadr[i1 + j1] = cnt;

					               	b.NumPix++;
									if(b.left > j1) b.left = j1;
									if(b.right < j1) b.right = j1;
									if(b.up > i1) b.up = i1;
									if(b.down < i1) b.down = i1;
									break;
							}
						case 5:
							if ((j1 > 0) && (i1 < maxicmp) && (Cadr[i1 + cols + j1 - 1] == num)){//left//down
									stack[ist].def = 6;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;

									i1 += cols;
									j1 -= 1;
									def = 0;
					               	Cadr[i1 + j1] = cnt;

					               	b.NumPix++;
									if(b.left > j1) b.left = j1;
									if(b.right < j1) b.right = j1;
									if(b.up > i1) b.up = i1;
									if(b.down < i1) b.down = i1;
									break;
							}
						case 6:
							if ((j1 < colscmp) && (i1 < maxicmp) && (Cadr[i1 + cols + j1 + 1] == num)){//right//down
									stack[ist].def = 7;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;

									i1 += cols;
									j1 += 1;
									def = 0;
					               	Cadr[i1 + j1] = cnt;

					               	b.NumPix++;
									if(b.left > j1) b.left = j1;
									if(b.right < j1) b.right = j1;
									if(b.up > i1) b.up = i1;
									if(b.down < i1) b.down = i1;
									break;
							}
						case 7:
							if ((j1 < colscmp) && (i1 > 0) && (Cadr[i1 - cols + j1 + 1] == num)){//right//up
									stack[ist].def = 1;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;

									i1 -= cols;
									j1 += 1;
									def = 0;
					               	Cadr[i1 + j1] = cnt;

					               	b.NumPix++;
									if(b.left > j1) b.left = j1;
									if(b.right < j1) b.right = j1;
									if(b.up > i1) b.up = i1;
									if(b.down < i1) b.down = i1;
									break;
							}
						case 1:
							if ((j1 < colscmp) && (Cadr[i1 + j1 + 1] == num)){//right
									stack[ist].def = 2;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;

									j1 += 1;
									def = 0;
					               	Cadr[i1 + j1] = cnt;

					               	b.NumPix++;
									if(b.left > j1) b.left = j1;
									if(b.right < j1) b.right = j1;
									if(b.up > i1) b.up = i1;
									if(b.down < i1) b.down = i1;
									break;
							}
						case 2:
							if ((i1 > 0) && (Cadr[i1 - cols + j1] == num)){//up
									stack[ist].def = 3;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;

									i1 -= cols;
									def = 0;
					               	Cadr[i1 + j1] = cnt;

					               	b.NumPix++;
									if(b.left > j1) b.left = j1;
									if(b.right < j1) b.right = j1;
									if(b.up > i1) b.up = i1;
									if(b.down < i1) b.down = i1;
									break;
							}
						case 3:
							if ((i1 < maxicmp) && (Cadr[i1 + cols + j1] == num)){//down
									i1 += cols;
									def = 0;
					               	Cadr[i1 + j1] = cnt;

					               	b.NumPix++;
									if(b.left > j1) b.left = j1;
									if(b.right < j1) b.right = j1;
									if(b.up > i1) b.up = i1;
									if(b.down < i1) b.down = i1;
									break;
							}
							ist--;
							j1 = stack[ist].j;
							i1 = stack[ist].i;
							def = stack[ist].def;
					}
                	if(ist >= MaxStack)
                	{
						ist--;
						j1 = stack[ist].j;
						i1 = stack[ist].i;
						def = stack[ist].def;
                	}
                }
                b.up /= cols;
                b.down /= cols;
                Bz[cnt] = b;
    }}}

    //восстановление эталона

    Uint32* a = (Uint32*)Cadr;
    for(i = 0; i < (cols * rows) >> 2; i ++)
          *a++ = _xpnd4(_cmpgtu4(*a, 0));
    return cnt + 0;
}


Uint16 findObj(Uint8* Cadr, Uint32 rows, Uint32 cols, Uint32 rezult)
{
	CleanMemory((Uint32)&Bz, 256 * sizeof(BinaryZone));
	short ZoneCnt = EihgtSv((Uint8*)strobAddr, RowStrob, ColStrob);
	COORDS* rez = (COORDS*)rezult;
	int i, k, Npmax = 0;
	for(i = 1; i <= ZoneCnt; i++)
	{
		if(Bz[i].NumPix > Npmax)
		{
			Npmax = Bz[i].NumPix;
			k = i;
		}
	}
	rez->x = Bz[k].left;
	rez->y = Bz[k].up;
	rez->cols = Bz[k].right - Bz[k].left + 1;
	rez->rows = Bz[k].down - Bz[k].up + 1;
	return Npmax;
}

short FourSv(Uint8* Cadr, Uint32 rows, Uint32 cols){
	CleanMemory((Uint32)&stack, 1024 * sizeof(RECT));
    int i ,j ,i1 , j1 ;
    int ist, def;
    Uint32 maxi = cols * rows;
    Uint32 maxicmp = cols * (rows - 1);
    Uint32 colscmp = cols - 1;
    short cnt = 0, num = 255;
    BinaryZone b;
    CleanMemory((Uint32)&b, 1 * sizeof(BinaryZone));
    for(i = 0; i < maxi; i += cols){
        for(j = 0; j < cols; j++){
            if (Cadr[i + j] == num){
                cnt++;
                if(cnt > 253) break;
                ist=0;
              	Cadr[i + j] = cnt;
               	j1 = j;
               	i1 = i;
               	def = 0;

                b.NumPix = 1;
                b.left = j1;
                b.up = i1;
                b.right = j1;
                b.down = i1;

                while(ist>=0){
					switch (def){
						case 0:
							if ((j1 > 0) && (Cadr[i1 + j1 - 1] == num)){//left
									stack[ist].def = 1;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;

									j1 -= 1;
									def = 0;
					               	Cadr[i1 + j1] = cnt;

									b.NumPix++;
									if(b.left > j1) b.left = j1;
									if(b.right < j1) b.right = j1;
									if(b.up > i1) b.up = i1;
									if(b.down < i1) b.down = i1;
									break;
							}
						case 1:
							if ((j1 < colscmp) && (Cadr[i1 + j1 + 1] == num)){//right
									stack[ist].def = 2;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;

									j1 += 1;
									def = 0;
					               	Cadr[i1 + j1] = cnt;

									b.NumPix++;
									if(b.left > j1) b.left = j1;
									if(b.right < j1) b.right = j1;
									if(b.up > i1) b.up = i1;
									if(b.down < i1) b.down = i1;
									break;
							}
						case 2:
							if ((i1 > 0) && (Cadr[i1 - cols + j1] == num)){//up
									stack[ist].def = 3;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;

									i1 -= cols;
									def = 0;
					               	Cadr[i1 + j1] = cnt;

									b.NumPix++;
									if(b.left > j1) b.left = j1;
									if(b.right < j1) b.right = j1;
									if(b.up > i1) b.up = i1;
									if(b.down < i1) b.down = i1;
									break;
							}
						case 3:
							if ((i1 < maxicmp) && (Cadr[i1 + cols + j1] == num)){//down
									i1 += cols;
									def = 0;
					               	Cadr[i1 + j1] = cnt;

									b.NumPix++;
									if(b.left > j1) b.left = j1;
									if(b.right < j1) b.right = j1;
									if(b.up > i1) b.up = i1;
									if(b.down < i1) b.down = i1;
									break;
							}
							ist--;
							j1 = stack[ist].j;
							i1 = stack[ist].i;
							def = stack[ist].def;
					}
                	if(ist >= MaxStack)
                	{
						ist--;
						j1 = stack[ist].j;
						i1 = stack[ist].i;
						def = stack[ist].def;
                	}
                }
                b.up /= cols;
                b.down /= cols;
                Bz[cnt] = b;
    }}}

    //нормировка числа строк выбор 4-х наиболее крупных объектов
    Uint8 bestOBN[4] = {255, 255, 255, 255};
    Uint16 bestOBS[4] = {0, 0, 0, 0};

    int fl;
    for(i = 1; i <= cnt; i++)
    {
		fl = 0;
		for(i1 = 0; (i1 < 4) && (fl == 0); i1++)
		{
			if(Bz[i].NumPix > bestOBS[i1])
			{
				for(j = 3; j >= i1 + 1; j--)
				{
					bestOBS[j] = bestOBS[j - 1];
					bestOBN[j] = bestOBN[j - 1];
				}
				bestOBS[i1] = Bz[i].NumPix;
				bestOBN[i1] = i;
				fl = 1;
			}
		}
    }
    //в случае, если объекты меньше допустимого удаляются(кроме первого)
    for(i = 1; i < 4; i++)
    	if(bestOBS[i] < 5) bestOBN[i] = 255;

    //восстановление картинки

    Uint32* a = (Uint32*)Cadr;
    Uint32 b0, b1, b2, b3;
    b0 = (bestOBN[0] << 24) | (bestOBN[0] << 16) | (bestOBN[0] << 8) | bestOBN[0];
    b1 = (bestOBN[1] << 24) | (bestOBN[1] << 16) | (bestOBN[1] << 8) | bestOBN[1];
    b2 = (bestOBN[2] << 24) | (bestOBN[2] << 16) | (bestOBN[2] << 8) | bestOBN[2];
    b3 = (bestOBN[3] << 24) | (bestOBN[3] << 16) | (bestOBN[3] << 8) | bestOBN[3];
    for(i = 0; i < (cols * rows) >> 2; i ++)
    {
    	j = _cmpeq4(*a, b0) | _cmpeq4(*a, b1) | _cmpeq4(*a, b2) | _cmpeq4(*a, b3);
    	*a++ = _xpnd4(j);
    }
    return cnt + 0;
}




/*
Uint16 findObj(Uint8* Cadr, Uint32 rows, Uint32 cols, Uint32 rezult){
	memset(stack, 0, sizeof(RECT) * 1024);
	memset(ObjSq, 0, 2 * 256);
	Uint16* rez = (Uint16*)rezult;
    int i ,j ,i1 , j1 ;
    int ist, def;
    Uint32 maxi = cols * rows;
    Uint16 cnt, sqMax=0, num=0;

    cnt = 1;
    for(i = 0; i < maxi; i += cols){
        for(j = 0; j < cols; j++){
            if (Cadr[i + j] == 255){
                cnt++;
                ist=0;
              	Cadr[i + j] = cnt;
               	ObjSq[cnt]=1;
               	j1 = j;
               	i1 = i;
               	def = 0;
                while(ist>=0){
					switch (def){
						case 0:
							if ((j1 > 0) && (Cadr[i1 + j1 - 1] == 255)){//left
					               	ObjSq[cnt]++;
									stack[ist].def = 4;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;

									j1 = j1 - 1;
									def = 0;
					               	Cadr[i1 + j1] = cnt;
									break;
							}
						case 4:
							if ((j1 < cols) && (Cadr[i1 - cols + j1 - 1] == 255)){//left//up
					               	ObjSq[cnt]++;
									stack[ist].def = 5;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;
									i1 = i1 - cols;
									j1 = j1 - 1;
									def = 0;
					               	Cadr[i1 + j1] = cnt;
									break;
							}
						case 5:
							if ((j1 < cols) && (Cadr[i1 + cols + j1 - 1] == 255)){//left//down
					               	ObjSq[cnt]++;
									stack[ist].def = 6;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;
									i1 = i1 + cols;
									j1 = j1 - 1;
									def = 0;
					               	Cadr[i1 + j1] = cnt;
									break;
							}
						case 6:
							if ((j1 < cols) && (Cadr[i1 + cols + j1 + 1] == 255)){//right//down
					               	ObjSq[cnt]++;
									stack[ist].def = 7;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;
									i1 = i1 + cols;
									j1 = j1 + 1;
									def = 0;
					               	Cadr[i1 + j1] = cnt;
									break;
							}
						case 7:
							if ((j1 < cols) && (Cadr[i1 - cols + j1 + 1] == 255)){//right//up
					               	ObjSq[cnt]++;
									stack[ist].def = 1;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;
									i1 = i1 - cols;
									j1 = j1 + 1;
									def = 0;
					               	Cadr[i1 + j1] = cnt;
									break;
							}
						case 1:
							if ((j1 < cols) && (Cadr[i1 + j1 + 1] == 255)){//right
					               	ObjSq[cnt]++;
									stack[ist].def = 2;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;

									j1 = j1 + 1;
									def = 0;
					               	Cadr[i1 + j1] = cnt;
									break;
							}
						case 2:
							if ((i1 > 0) && (Cadr[i1 - cols + j1] == 255)){//up
					               	ObjSq[cnt]++;
									stack[ist].def = 3;
									stack[ist].i = i1;
									stack[ist].j = j1;
									ist++;
									i1 = i1 - cols;

									def = 0;
					               	Cadr[i1 + j1] = cnt;
									break;
							}
						case 3:
							if ((i1 < maxi) && (Cadr[i1 + cols + j1] == 255)){//down
					               	ObjSq[cnt]++;
									i1 = i1 + cols;

									def = 0;
					               	Cadr[i1 + j1] = cnt;
									break;
							}
							ist--;
							j1 = stack[ist].j;
							i1 = stack[ist].i;
							def = stack[ist].def;
					}
                	if(ist >= MaxStack)
                	{
						ist--;
						j1 = stack[ist].j;
						i1 = stack[ist].i;
						def = stack[ist].def;
                	}
                }
    }}}
    for(i = 2; i <= cnt; i++){
    	if (ObjSq[i] > sqMax) {
    		sqMax = ObjSq[i];
    		num = i;
    	}
    }
    int iu, iu1;
    //верх
    for(i = 0, i1 = 0; i < maxi; i += cols, i1++)
        for(j = 0; j < cols; j++)
            if (Cadr[i + j] == num)
            {
            	rez[1] = i1;
            	iu = i;
            	iu1 = i1;
            	i = maxi;
            	j = cols;
            }
    //лев
    for(j = 0; j < cols; j++)
    	for(i = iu, i1 = iu1; i < maxi; i += cols, i1++)
            if (Cadr[i + j] == num)
            {
            	rez[0] = j;
            	i = maxi;
            	j = cols;
            }
    //низ
    for(i = maxi - cols, i1 = rows; i >= 0; i -= cols, i1--)
        for(j = 0; j < cols; j++)
            if (Cadr[i + j] == num)
            {
            	rez[3] = i1;
            	i = -1;
            	j = cols;
            }
    //прав
    for(j = cols - 1; j >= 0; j--)
        for(i = iu, i1 = iu1; i < maxi; i += cols, i1++)
            if (Cadr[i + j] == num)
            {
            	rez[2] = j;
            	i = maxi;
            	j = -1;
           }
    rez[2] -= rez[0];
    rez[3] -= rez[1];

    //восстановление эталона

    for(i = 0; i < maxi; i += cols)
        for(j = 0; j < cols; j++)
            if (Cadr[i + j] > 0) Cadr[i + j] = 0xFF;


    return num;
}

*/



/*

#pragma DATA_SECTION (Rcoords , "cL2RAM");
Uint8 Rcoords[61][61] = {
                  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {3,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {4,4,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {5,5,5,4,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {6,6,6,5,4,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {7,7,7,6,6,5,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {8,8,8,7,7,6,5,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {9,9,9,8,8,7,7,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {10,10,10,10,9,9,8,7,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {11,11,11,11,10,10,9,8,8,6,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {12,12,12,12,11,11,10,10,9,8,7,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {13,13,13,13,12,12,12,11,10,9,8,7,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {14,14,14,14,13,13,13,12,11,11,10,9,7,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {15,15,15,15,14,14,14,13,13,12,11,10,9,7,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {16,16,16,16,15,15,15,14,14,13,12,12,11,9,8,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {17,17,17,17,17,16,16,15,15,14,14,13,12,11,10,8,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {18,18,18,18,18,17,17,17,16,16,15,14,13,12,11,10,8,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {19,19,19,19,19,18,18,18,17,17,16,15,15,14,13,12,10,8,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {20,20,20,20,20,19,19,19,18,18,17,17,16,15,14,13,12,11,9,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {21,21,21,21,21,20,20,20,19,19,18,18,17,16,16,15,14,12,11,9,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {22,22,22,22,22,21,21,21,20,20,20,19,18,18,17,16,15,14,13,11,9,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {23,23,23,23,23,22,22,22,22,21,21,20,20,19,18,17,17,15,14,13,11,9,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {24,24,24,24,24,23,23,23,23,22,22,21,21,20,19,19,18,17,16,15,13,12,10,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {25,25,25,25,25,24,24,24,24,23,23,22,22,21,21,20,19,18,17,16,15,14,12,10,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {26,26,26,26,26,26,25,25,25,24,24,24,23,23,22,21,20,20,19,18,17,15,14,12,10,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {27,27,27,27,27,27,26,26,26,25,25,25,24,24,23,22,22,21,20,19,18,17,16,14,12,10,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {28,28,28,28,28,28,27,27,27,27,26,26,25,25,24,24,23,22,21,21,20,19,17,16,14,13,10,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {29,29,29,29,29,29,28,28,28,28,27,27,26,26,25,25,24,23,23,22,21,20,19,18,16,15,13,11,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {30,30,30,30,30,30,29,29,29,29,28,28,27,27,27,26,25,25,24,23,22,21,20,19,18,17,15,13,11,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {31,31,31,31,31,31,30,30,30,30,29,29,29,28,28,27,27,26,25,24,24,23,22,21,20,18,17,15,13,11,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {32,32,32,32,32,32,31,31,31,31,30,30,30,29,29,28,28,27,26,26,25,24,23,22,21,20,19,17,15,14,11,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {33,33,33,33,33,33,32,32,32,32,31,31,31,30,30,29,29,28,28,27,26,25,25,24,23,22,20,19,17,16,14,11,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {34,34,34,34,34,34,33,33,33,33,32,32,32,31,31,31,30,29,29,28,27,27,26,25,24,23,22,21,19,18,16,14,11,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {35,35,35,35,35,35,34,34,34,34,34,33,33,32,32,32,31,31,30,29,29,28,27,26,25,24,23,22,21,20,18,16,14,12,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {36,36,36,36,36,36,35,35,35,35,35,34,34,34,33,33,32,32,31,31,30,29,28,28,27,26,25,24,23,21,20,18,16,14,12,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {37,37,37,37,37,37,37,36,36,36,36,35,35,35,34,34,33,33,32,32,31,30,30,29,28,27,26,25,24,23,22,20,19,17,15,12,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {38,38,38,38,38,38,38,37,37,37,37,36,36,36,35,35,34,34,33,33,32,32,31,30,29,29,28,27,26,25,23,22,20,19,17,15,12,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {39,39,39,39,39,39,39,38,38,38,38,37,37,37,36,36,36,35,35,34,33,33,32,31,31,30,29,28,27,26,25,24,22,21,19,17,15,12,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {40,40,40,40,40,40,40,39,39,39,39,38,38,38,37,37,37,36,36,35,35,34,33,33,32,31,30,30,29,28,26,25,24,23,21,19,17,15,12,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {41,41,41,41,41,41,41,40,40,40,40,39,39,39,39,38,38,37,37,36,36,35,35,34,33,32,32,31,30,29,28,27,26,24,23,21,20,18,15,13,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {42,42,42,42,42,42,42,41,41,41,41,41,40,40,40,39,39,38,38,37,37,36,36,35,34,34,33,32,31,30,29,28,27,26,25,23,22,20,18,16,13,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {43,43,43,43,43,43,43,42,42,42,42,42,41,41,41,40,40,39,39,39,38,38,37,36,36,35,34,33,33,32,31,30,29,28,26,25,24,22,20,18,16,13,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {44,44,44,44,44,44,44,43,43,43,43,43,42,42,42,41,41,41,40,40,39,39,38,38,37,36,35,35,34,33,32,31,30,29,28,27,25,24,22,20,18,16,13,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {45,45,45,45,45,45,45,44,44,44,44,44,43,43,43,42,42,42,41,41,40,40,39,39,38,37,37,36,35,34,34,33,32,31,29,28,27,26,24,22,21,19,16,13,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {46,46,46,46,46,46,46,45,45,45,45,45,44,44,44,43,43,43,42,42,41,41,40,40,39,39,38,37,36,36,35,34,33,32,31,30,29,27,26,24,23,21,19,16,13,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {47,47,47,47,47,47,47,46,46,46,46,46,45,45,45,45,44,44,43,43,43,42,42,41,40,40,39,38,38,37,36,35,34,33,32,31,30,29,28,26,25,23,21,19,17,14,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {48,48,48,48,48,48,48,47,47,47,47,47,46,46,46,46,45,45,44,44,44,43,43,42,42,41,40,40,39,38,37,37,36,35,34,33,32,31,29,28,27,25,23,21,19,17,14,10,0,0,0,0,0,0,0,0,0,0,0,0,0},
                  {49,49,49,49,49,49,49,48,48,48,48,48,48,47,47,47,46,46,46,45,45,44,44,43,43,42,42,41,40,39,39,38,37,36,35,34,33,32,31,30,28,27,25,23,22,19,17,14,10,0,0,0,0,0,0,0,0,0,0,0,0},
                  {50,50,50,50,50,50,50,50,49,49,49,49,49,48,48,48,47,47,47,46,46,45,45,44,44,43,43,42,41,41,40,39,38,38,37,36,35,34,32,31,30,29,27,26,24,22,20,17,14,10,0,0,0,0,0,0,0,0,0,0,0},
                  {51,51,51,51,51,51,51,51,50,50,50,50,50,49,49,49,48,48,48,47,47,46,46,46,45,44,44,43,43,42,41,40,40,39,38,37,36,35,34,33,32,30,29,27,26,24,22,20,17,14,10,0,0,0,0,0,0,0,0,0,0},
                  {52,52,52,52,52,52,52,52,51,51,51,51,51,50,50,50,49,49,49,48,48,48,47,47,46,46,45,44,44,43,42,42,41,40,39,38,38,37,35,34,33,32,31,29,28,26,24,22,20,17,14,10,0,0,0,0,0,0,0,0,0},
                  {53,53,53,53,53,53,53,53,52,52,52,52,52,51,51,51,51,50,50,49,49,49,48,48,47,47,46,46,45,44,44,43,42,41,41,40,39,38,37,36,35,34,32,31,30,28,26,24,22,20,18,14,10,0,0,0,0,0,0,0,0},
                  {54,54,54,54,54,54,54,54,53,53,53,53,53,52,52,52,52,51,51,51,50,50,49,49,48,48,47,47,46,46,45,44,43,43,42,41,40,39,38,37,36,35,34,33,31,30,28,27,25,23,20,18,15,10,0,0,0,0,0,0,0},
                  {55,55,55,55,55,55,55,55,54,54,54,54,54,53,53,53,53,52,52,52,51,51,50,50,49,49,48,48,47,47,46,45,45,44,43,42,42,41,40,39,38,37,36,34,33,32,30,29,27,25,23,21,18,15,10,0,0,0,0,0,0},
                  {56,56,56,56,56,56,56,56,55,55,55,55,55,54,54,54,54,53,53,53,52,52,51,51,51,50,50,49,48,48,47,47,46,45,44,44,43,42,41,40,39,38,37,36,35,33,32,30,29,27,25,23,21,18,15,11,0,0,0,0,0},
                  {57,57,57,57,57,57,57,57,56,56,56,56,56,55,55,55,55,54,54,54,53,53,53,52,52,51,51,50,50,49,48,48,47,46,46,45,44,43,42,42,41,40,39,37,36,35,34,32,31,29,27,25,23,21,18,15,11,0,0,0,0},
                  {58,58,58,58,58,58,58,58,57,57,57,57,57,57,56,56,56,55,55,55,54,54,54,53,53,52,52,51,51,50,50,49,48,48,47,46,45,45,44,43,42,41,40,39,38,37,35,34,33,31,29,28,26,24,21,18,15,11,0,0,0},
                  {59,59,59,59,59,59,59,59,58,58,58,58,58,58,57,57,57,56,56,56,56,55,55,54,54,53,53,52,52,51,51,50,50,49,48,47,47,46,45,44,43,42,41,40,39,38,37,36,34,33,31,30,28,26,24,21,19,15,11,0,0},
                  {60,60,60,60,60,60,60,60,59,59,59,59,59,59,58,58,58,58,57,57,57,56,56,55,55,55,54,54,53,53,52,51,51,50,49,49,48,47,46,46,45,44,43,42,41,40,39,37,36,35,33,32,30,28,26,24,22,19,15,11,0},
                  };

#pragma DATA_SECTION (HafC , "cL2RAM");
Uint8 HafC[198][198];


//поиск окружности с оптимальным соотноешением точек на ней присутствующих
//Data - адрес изображения
//cols - число колонок изображнения
//rows - число строк изображения
//Rmin - минимальный радиус искомой окружности
//Rmax - максимальный радиус искомой окружности
double HafCircle(Uint32 Data, Uint32 cols, Uint32 rows, Uint32 Rmin, Uint32 Rmax, Uint32 result)
{
	memset(HafC, 0, 198*198);
	Uint8* Img = (Uint8*)Data;
	Uint32* rez = (Uint32*)result;
	Uint32 r; //текущий радиус
	Uint32 i, j, si; //текущие координаты центра окружности
	Uint32 lim; //стык дуг
	Uint32 p;// счетчик точки на окружности
	Uint32 xr;// координаты точки на окружности
	Uint32 MaxH; //макс хафа при тек радиусе
	double rezH, doblH;
	Uint32 rezX, rezY, rezR, rX, rY, rR;
	rezH = 0.0;
	for(r = Rmin; r <= Rmax; r++)
	{
		memset(&HafC, 0, 198*198);
		lim = ((r * 45) >> 6) + 1;
		for(i = r, si = r * cols; i < rows - r; i++, si += cols)
			for(j = r; j < cols - r; j++)
				if(Img[si + j] > 0)
				{
					HafC[i][j + r] += 1;
					HafC[i][j - r] += 1;
					HafC[i + r][j] += 1;
					HafC[i - r][j] += 1;
					for(p = 1; p <= lim; p++)
					{
						xr = Rcoords[r][p];
						HafC[i + p][j + xr] += 1;
						HafC[i + p][j - xr] += 1;
						HafC[i - p][j + xr] += 1;
						HafC[i - p][j - xr] += 1;
						HafC[i + xr][j + p] += 1;
						HafC[i + xr][j - p] += 1;
						HafC[i - xr][j + p] += 1;
						HafC[i - xr][j - p] += 1;
					}
				}
		MaxH = 0;
		for(i = 0; i < rows; i++)
			for(j = 0; j < cols; j++)
				if(HafC[i][j] > MaxH)
				{
					MaxH = HafC[i][j];
					rY = i;
					rX = j;
					rR = r;
				}
		doblH = (double)(MaxH * MaxH) / r;
		if(doblH > rezH)
		{
			rezH = doblH;
			rezY = rY;
			rezX = rX;
			rezR = rR;
		}
	}
	rez[0] = rezY - rezR;
	rez[1] = rezX - rezR;
	rez[2] = rezR;
	rez[3] = rezR;
	return sqrt(rezH / rezR) / (2*3.14) ;
}

*/
