#include "main.h"
#include <csl_edma3.h>

CSL_Edma3Context Edma3context;
CSL_Edma3Obj edmaObj;
CSL_Edma3Handle hModule;
CSL_Edma3HwSetup EdmahwSetup;
CSL_Edma3CmdDrae regionAccess;
CSL_Edma3CmdIntr regionIntr;
CSL_Edma3ChannelHandle hChannelc0, hChannelc1, hChannelc2, hChannel;
CSL_Edma3ChannelObj chObjc0, chObjc1, chObjc2, chObj;
CSL_Edma3ChannelAttr chAttrc0, chAttrc1, chAttrc2, chAttr;
CSL_Edma3HwDmaChannelSetup dmahwSetup[CSL_EDMA3_NUM_DMACH] = CSL_EDMA3_DMACHANNELSETUP_DEFAULT;
CSL_Edma3ParamHandle        hParamBasicc0, hParamBasicc1, hParamBasicc2, hParamBasic;
CSL_Edma3ParamSetup         myParamSetupC0,myParamSetupC1,myParamSetupC2, myParamSetup;

int Edma3Init(){

	CSL_Status status;

  	status = CSL_edma3Init(&Edma3context); 								//Module Initialization
   	hModule = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&status); 	//Module level open

   	EdmahwSetup.dmaChaSetup = dmahwSetup;
    EdmahwSetup.qdmaChaSetup = NULL;
   	status = CSL_edma3HwSetup(hModule, &EdmahwSetup);					//Module setup

    regionAccess.region = CSL_EDMA3_REGION_0;
    regionAccess.drae =   0xFFFF ;
    regionAccess.draeh =  0x0 ;
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_DMAREGION_ENABLE, &regionAccess);

   	regionIntr.region = CSL_EDMA3_REGION_0;
    regionIntr.intr = 1;
    regionIntr.intrh = 0x0 ;
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTR_ENABLE,&regionIntr);

//����������� ������� ������
   	chAttr.regionNum = CSL_EDMA3_REGION_0;
   	chAttr.chaNum = CSL_EDMA3_CHA_3;
   	hChannel = CSL_edma3ChannelOpen(&chObj, CSL_EDMA3, &chAttr,	&status);		//Channel 0 open in context of shadow region 5

   	hParamBasic = CSL_edma3GetParamHandle(hChannel, CSL_EDMA3_CHA_3, &status);
   	myParamSetup.option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, 		//23 Intermediate transfer completion chaining enable
   												CSL_EDMA3_TCCH_EN, 		//22 Transfer complete chaining enable
   												CSL_EDMA3_ITCINT_DIS, 		//21 Intermediate transfer completion interrupt enable
   	                                           CSL_EDMA3_TCINT_DIS, 		//20 Transfer complete interrupt enable
   	                                        CSL_EDMA3_CHA_5,			//17-12 Transfer complete code
   	                                           CSL_EDMA3_TCC_NORMAL,		//11 A transfer is considered completed after the data has been transferred
   	                                           CSL_EDMA3_FIFOWIDTH_64BIT,	//10-8 FIFO Width. Applies if either SAM or DAM is set to constant addressing mode
   	                                           CSL_EDMA3_STATIC_DIS,		//3 A value of 0 should be used for DMA channels and for non-final transfers in a linked list of QDMA transfers
   	                                           CSL_EDMA3_SYNC_AB, 			//2 Transfer synchronization dimension.
   	                                           CSL_EDMA3_ADDRMODE_INCR,	//1 Destination address mode.
   	                                           CSL_EDMA3_ADDRMODE_INCR);  //0 Source address mode.
   	myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE (CSL_EDMA3_LINK_NULL, 0);
   	myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,0);
   	myParamSetup.cCnt = 1;

   	chAttrc1.regionNum = CSL_EDMA3_REGION_0;
   	chAttrc1.chaNum = CSL_EDMA3_CHA_6;
   	hChannelc1 = CSL_edma3ChannelOpen(&chObjc1, CSL_EDMA3, &chAttrc1,	&status);		//Channel 0 open in context of shadow region 5

   	hParamBasicc1 = CSL_edma3GetParamHandle(hChannelc1, CSL_EDMA3_CHA_6, &status);
   	   	// Setup a Parameter Entry
   	myParamSetupC1.option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, 		//23 Intermediate transfer completion chaining enable
   											 CSL_EDMA3_TCCH_EN, 		//22 Transfer complete chaining enable
                                             CSL_EDMA3_ITCINT_DIS, 		//21 Intermediate transfer completion interrupt enable
                                             CSL_EDMA3_TCINT_DIS, 		//20 Transfer complete interrupt enable
                                             CSL_EDMA3_CHA_5,			//17-12 Transfer complete code
                                             CSL_EDMA3_TCC_NORMAL,		//11 A transfer is considered completed after the data has been transferred
                                             CSL_EDMA3_FIFOWIDTH_64BIT,	//10-8 FIFO Width. Applies if either SAM or DAM is set to constant addressing mode
                                             CSL_EDMA3_STATIC_DIS,		//3 A value of 0 should be used for DMA channels and for non-final transfers in a linked list of QDMA transfers
                                             CSL_EDMA3_SYNC_AB, 			//2 Transfer synchronization dimension.
                                             CSL_EDMA3_ADDRMODE_INCR,	//1 Destination address mode.
                                             CSL_EDMA3_ADDRMODE_INCR);  //0 Source address mode.
   	myParamSetupC1.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE (CSL_EDMA3_LINK_NULL, 0);
   	myParamSetupC1.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,0);
   	myParamSetupC1.cCnt = 1;


   	chAttrc2.regionNum = CSL_EDMA3_REGION_0;
   	chAttrc2.chaNum = CSL_EDMA3_CHA_5;
   	hChannelc2 = CSL_edma3ChannelOpen(&chObjc2, CSL_EDMA3, &chAttrc2,	&status);		//Channel 0 open in context of shadow region 5

   	hParamBasicc2 = CSL_edma3GetParamHandle(hChannelc2, CSL_EDMA3_CHA_5, &status);
   	   	// Setup a Parameter Entry
   	myParamSetupC2.option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, 		//23 Intermediate transfer completion chaining enable
   		   	                                  CSL_EDMA3_TCCH_DIS, 		//22 Transfer complete chaining enable
                                             CSL_EDMA3_ITCINT_DIS, 		//21 Intermediate transfer completion interrupt enable
                                             CSL_EDMA3_TCINT_EN, 		//20 Transfer complete interrupt enable
                                             0,			//17-12 Transfer complete code
                                             CSL_EDMA3_TCC_NORMAL,		//11 A transfer is considered completed after the data has been transferred
                                             CSL_EDMA3_FIFOWIDTH_64BIT,	//10-8 FIFO Width. Applies if either SAM or DAM is set to constant addressing mode
                                             CSL_EDMA3_STATIC_DIS,		//3 A value of 0 should be used for DMA channels and for non-final transfers in a linked list of QDMA transfers
                                             CSL_EDMA3_SYNC_AB, 			//2 Transfer synchronization dimension.
                                             CSL_EDMA3_ADDRMODE_INCR,	//1 Destination address mode.
                                             CSL_EDMA3_ADDRMODE_INCR);  //0 Source address mode.
   	myParamSetupC2.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE (CSL_EDMA3_LINK_NULL, 0);
   	myParamSetupC2.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,0);
   	myParamSetupC2.cCnt = 1;
   	return 0;
}

void EdmaEventCheck(Uint32 EvtNo)
{
  	register volatile Uint32 *IPR = (Uint32*) 0x02A01068;//Interrupt Pending Register
   	register volatile Uint32 *ICR = (Uint32*) 0x02A01070;//Interrupt Clear Register
   	volatile Uint32 a = *IPR & (1 << EvtNo);
	if(a > 0)
	{
		*ICR |= (1 << EvtNo);
		flagCopyStarted = 2;
	}
}

void R1(Uint32 src, Uint32 dst, Uint16 x, Uint16 y, Uint16 cols, Uint16 rows){
	myParamSetupC2.srcAddr = src + FrameCols * y + x;
	myParamSetupC2.srcDstBidx = CSL_EDMA3_BIDX_MAKE(FrameCols, cols);
	myParamSetupC2.aCntbCnt = CSL_EDMA3_CNT_MAKE(cols, rows); //���������� ������������ ���� �� 0 �� 65535
	myParamSetupC2.dstAddr = dst;
	CSL_edma3ParamSetup(hParamBasicc2,&myParamSetupC2);
}

void R2(Uint32 src, Uint32 dst, Uint16 x, Uint16 y, Uint16 cols, Uint16 rows){
	myParamSetupC1.srcAddr = src;
	myParamSetupC1.srcDstBidx = CSL_EDMA3_BIDX_MAKE(cols, cols);
	myParamSetupC1.aCntbCnt = CSL_EDMA3_CNT_MAKE(cols, rows); //���������� ������������ ���� �� 0 �� 65535
	myParamSetupC1.dstAddr = dst;
	CSL_edma3ParamSetup(hParamBasicc1,&myParamSetupC1);
}


void R6(Uint32 src, Uint32 dst, Uint16 x, Uint16 y, Uint16 cols, Uint16 rows){
	myParamSetup.srcAddr = src + FrameCols * y + x;
	myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(FrameCols, cols);
	myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(cols, rows); //���������� ������������ ���� �� 0 �� 65535
	myParamSetup.dstAddr = dst;
	CSL_edma3ParamSetup(hParamBasic,&myParamSetup);

	CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTRPEND_CLEAR, &regionIntr);
	CSL_Status a = CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_SET,NULL);
}

/*
int EdmaCheck(){

	Uint32 *IPR = (Uint32*) 0x02A01068;
	Uint32 *ICR = (Uint32*) 0x02A01070;

	if(*IPR > 0){
		flagCopyStarted = 0;
		rez = 1;
		*ICR |= 1;
	}

	int rez = 0;
	CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND, &regionIntr);

	if((flagCopyStarted == 1) && (regionIntr.intr == 1))
	{
		flagCopyStarted = 0;
		rez = 1;
		CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTRPEND_CLEAR, &regionIntr);
	}

	return rez;
}
*/
