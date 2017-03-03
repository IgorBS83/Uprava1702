#include <csl_tmr.h>
#include <cslr_dev.h>
#include <soc.h>
#include <string.h>

CSL_TmrHandle hTmr;
CSL_TmrObj tmrObj;
CSL_TmrHwSetup TmrhwSetup = CSL_TMR_HWSETUP_DEFAULTS;
CSL_TmrEnamode TimeCountMode = CSL_TMR_ENAMODE_CONT;

void TimerReset()
{
	CSL_tmrHwControl(hTmr, CSL_TMR_CMD_RESET_TIMLO, NULL);
	CSL_tmrHwSetup(hTmr,&TmrhwSetup);
	CSL_tmrHwControl(hTmr, CSL_TMR_CMD_START_TIMLO, (void *)&TimeCountMode); //Start the timer in GPtimer64 OR Chained mode
}

int Timer_Init(){

	CSL_Status status;


	Bool  timer0En;

    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, UNLOCK);
    // Enable the Powersaver clock for TIMER
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_TIMER0CTL, ENABLE);

    do {
    	timer0En = (Bool) CSL_FEXT(((CSL_DevRegs*)CSL_DEV_REGS)->PERSTAT0, DEV_PERSTAT0_TIMER0STAT);
    } while ((timer0En) != TRUE);

    memset(&tmrObj, 0, sizeof(CSL_TmrObj));
// настройка таймера
	CSL_tmrInit(NULL);
	hTmr = CSL_tmrOpen(&tmrObj, 0, NULL, &status);
	TmrhwSetup.tmrClksrcLo = CSL_TMR_CLKSRC_INTERNAL;
	//1.2 GHz 1 секунда
//	TmrhwSetup.tmrTimerPeriodHi = 0x08800000;//4786;
	TmrhwSetup.tmrTimerCounterLo = 0;
	TmrhwSetup.tmrTimerPeriodLo = 0x20000000;//8C00;
	TmrhwSetup.tmrTimerMode = CSL_TMR_TIMMODE_DUAL_UNCHAINED; //The timer is in 64-bit GP timer mode
	CSL_tmrHwSetup(hTmr,&TmrhwSetup);
	//запуск таймера
//	CSL_tmrHwControl(hTmr, CSL_TMR_CMD_RESET_TIMHI, NULL);
	CSL_tmrHwControl(hTmr, CSL_TMR_CMD_RESET_TIMLO, NULL);
	CSL_tmrHwControl(hTmr, CSL_TMR_CMD_START_TIMLO, (void *)&TimeCountMode); //Start the timer in GPtimer64 OR Chained mode
//	CSL_tmrHwControl(hTmr, CSL_TMR_CMD_START_TIMHI, (void *)&TimeCountMode); //Start the timer in GPtimer64 OR Chained mode
//	CSL_tmrClose (hTmr);
	return 0;
}


