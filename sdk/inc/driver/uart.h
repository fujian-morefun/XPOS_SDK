#ifndef _UART_H_
#define _UART_H_

#ifdef __cplusplus
extern "C"{
#endif
	


#define APP_COM		COM20
#define MODULE_COM	COM21
#define BARCODE_COM	COM22
#define USB_COM		COM23


enum{
	COM1 = 1,
	COM2,
	COM3,
	COM4,
	COM5,
	COM6,
	COM7,
	COM8,
	COM9,
	COM10,
	COM11,
	COM12,
	COM13,
	COM14,
	COM15,
	COM16,
	COM17,
	COM18,
	COM19,
	COM20,
	COM21,
	COM22,
	COM23,
	COM24,
	COM25,
	COM26,
	COM27,
	COM28,
	COM29,
	COM30,
};



#define UART_STATUS_ENABLE	1

#define UART_STATUS_DISABLE	0



//data bit 

#define UART_DATABIT5		5

#define UART_DATABIT6		6

#define UART_DATABIT7		7

#define UART_DATABIT8		8



//stop bit 

#define UART_STOPBIT1		1

#define UART_STOPBIT2		2



//parity bit 

#define UART_NOPARITY		0
#define UART_ODDPARITY		1
#define UART_EVENPARITY		2

unsigned int UartInit(void);
unsigned int UartOpen(unsigned int nCom, unsigned int nBaud, unsigned int nData, unsigned int nStop, unsigned int nParity);
unsigned int UartClose(unsigned int nCom);
unsigned int UartRecv(unsigned int nCom, unsigned char *pBuffer, unsigned int nLength , int timeout);
unsigned int UartSend(unsigned int nCom, unsigned char *pBuffer, unsigned int nLength);
unsigned int UartGetRXBufCount(unsigned int nCom);
unsigned int UartGetTXBufCount(unsigned int nCom);
unsigned int UartClear(int port);

//EMU_LIB_EXPORT unsigned char UartGetChar(unsigned int nCom);
//EMU_LIB_EXPORT unsigned char UartGetCharTO(unsigned int nCom, int nTimeOut, unsigned int *pnError);
//EMU_LIB_EXPORT unsigned int UartGet(unsigned int nCom, unsigned char *pBuffer, unsigned int nLength);
//EMU_LIB_EXPORT unsigned int UartGetTO(unsigned int nCom, unsigned char *pBuffer, unsigned int nLength, int nTimeOut, unsigned int *pnError);

//EMU_LIB_EXPORT unsigned int UartSendChar(unsigned int nCom, unsigned char nChar);
//EMU_LIB_EXPORT unsigned int UartSend(unsigned int nCom, unsigned char *pBuffer, unsigned int nLength);

//EMU_LIB_EXPORT unsigned int UartGetStatus(int nCom);


#ifdef __cplusplus
}
#endif

#endif



