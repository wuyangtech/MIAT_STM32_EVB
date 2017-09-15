/*  
* 	Tun-Kai Yao
*/	
#ifndef __RF_CTRL_H
#define __RF_CTRL_H

typedef struct
{
    unsigned char AddressWidth;
    unsigned char RxAddress[5];
    unsigned char TxAddress[5];
	unsigned char DataLengthPipe0;
    unsigned char Config;
    unsigned char AutoAck;
    unsigned char RxPipe;
    unsigned char Retry;
    unsigned char Channel;
    unsigned char Setup;
    unsigned char Status;
    unsigned char ObserveTx; 
}RF_ConfTypeDef;

unsigned char RF_ConfigureMode(void);
unsigned char RF_FlushTxBuf(void);
unsigned char RF_FlushRxBuf(void);
unsigned char RF_Init(RF_ConfTypeDef* RFInitialValue);

unsigned char RF_TransmitData(u8 *pTxBuf);

unsigned char RF_ClearStatus(unsigned char MFlag);



#endif /* __RF_CTRL_H */
