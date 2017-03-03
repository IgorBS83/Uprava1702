#include <csl_intc.h>

CSL_IntcContext context;
CSL_IntcEventHandlerRecord EventRecord[10];
CSL_IntcEventHandlerRecord isr_gpio;
CSL_IntcGlobalEnableState state;
CSL_IntcObj intcObjTmrHi, intcObjTmrLo, intcObjEdma, intcObjGpio;
CSL_IntcHandle hIntcTmrHi, hIntcTmrLo, hIntcEdma, hIntcGpio;
CSL_IntcParam vectId;
CSL_Status intStat;

extern int GpioBlink(int);
extern interrupt void CommandRead();

extern volatile Uint32 IntHalfCadr;	//сигнал о приходе полукадра
extern volatile Uint32 flagCopyStarted;

interrupt void Reset()
{
    void (*init)() = (void*) 0xB0000000;
	(*init)();
    asm(" nop 9");
}

interrupt void GPIOHalfCadr()
{
	GpioBlink(6);
	IntHalfCadr = 1;
}

interrupt void EdmaDone()
{
	*(Uint32*) 0x02A01070 = 1;//ICR
	flagCopyStarted = 2;
}


void IntInit(){

	context.eventhandlerRecord = EventRecord;
	context.numEvtEntries = 10;

	CSL_intcInit(&context);
	CSL_intcGlobalNmiEnable();
	intStat = CSL_intcGlobalDisable(&state);

	//прерывания от едма
/*
	vectId = CSL_INTC_VECTID_5;
	hIntcEdma = CSL_intcOpen(&intcObjEdma, CSL_INTC_EVENTID_EDMA3CC_INT0, &vectId, &intStat);
	CSL_intcHwControl(hIntcEdma, CSL_INTC_CMD_EVTENABLE, NULL);
	CSL_intcHookIsr(CSL_INTC_VECTID_5, &EdmaDone);
*/

	//прерывания от GPIO кадр

	vectId = CSL_INTC_VECTID_4;
	hIntcGpio = CSL_intcOpen(&intcObjGpio, CSL_INTC_EVENTID_GPINT1, &vectId, &intStat);
	CSL_intcHwControl(hIntcGpio, CSL_INTC_CMD_EVTENABLE, NULL);
	CSL_intcHookIsr(CSL_INTC_VECTID_4, &GPIOHalfCadr);



	//прерывания от GPIO протокол

	vectId = CSL_INTC_VECTID_6;
	hIntcGpio = CSL_intcOpen(&intcObjGpio, CSL_INTC_EVENTID_GPINT2, &vectId, &intStat);
	CSL_intcHwControl(hIntcGpio, CSL_INTC_CMD_EVTENABLE, NULL);
	CSL_intcHookIsr(CSL_INTC_VECTID_6, &CommandRead);

	//прерывания от таймера

	vectId = CSL_INTC_VECTID_7;
	hIntcTmrHi = CSL_intcOpen(&intcObjTmrHi, CSL_INTC_EVENTID_TINTLO0, &vectId, &intStat);
	CSL_intcHwControl(hIntcTmrHi, CSL_INTC_CMD_EVTENABLE, NULL);
	CSL_intcHookIsr(CSL_INTC_VECTID_7, &Reset);
/*
	vectId = CSL_INTC_VECTID_4;//нет 4,5 да
	hIntcTmrLo = CSL_intcOpen(&intcObjTmrLo, CSL_INTC_EVENTID_TINTLO0, &vectId, NULL);
	CSL_intcHwControl(hIntcTmrLo, CSL_INTC_CMD_EVTENABLE, NULL);
	CSL_intcHookIsr(CSL_INTC_VECTID_4, &TmrLoClock);
*/
	intStat = CSL_intcGlobalEnable(&state);
}
/*
interrupt void blink1(){
//	GpioBlink(12);
}
Uint8 fl=6, np=1,ncnt=0;
interrupt void TmrHiClock(){
//	GpioBlink(7);
}

interrupt void TmrLoClock(){
//	GpioBlink(6);
	if (np==1){
		switch (fl){
		case 6:
			GpioBlink(fl);
			fl = 7;
			break;
		case 7:
			GpioBlink(fl);
			fl = 12;
			break;
		case 12:
			GpioBlink(fl);
			fl = 13;
			break;
		case 13:
			GpioBlink(fl);
			fl = 6;
			ncnt++;
			if (ncnt == 2) {
				fl = 13;
				np = 0;
				ncnt = 0;
			}
		}
	}
	else{
		switch (fl){
		case 13:
			GpioBlink(fl);
			fl = 12;
			break;
		case 12:
			GpioBlink(fl);
			fl = 7;
			break;
		case 7:
			GpioBlink(fl);
			fl = 6;
			break;
		case 6:
			GpioBlink(fl);
			fl = 13;
			ncnt++;
			if (ncnt == 2) {
				fl = 6;
				np = 1;
				ncnt = 0;
			}
		}
	}
//	GpioBlink(fl);
}
*/
