#include "driver\uart.h"
#include "ucosii\ucos_ii.h"
#include "pub\inc\taskdef.h"
#include "pub\tracedef.h"
#include "pub\osl\inc\osl_time.h"
#include "pub\common\misc\inc\mfmalloc.h"
#include "mpos_pub.h"
#include "mpos_func.h"
#include "mpos_proc.h"


// #define _MPOS_TASK_SIZE		1536
// #define _MPOS_TASK_PRIO		(_APP_TASK_MIN_PRIO + 4)
// static OS_STK pTaskStk[_MPOS_TASK_SIZE];


#define MAX_UART_BUF		512
#define RECV_BUFF_SIZE		512

static unsigned char UART_GetChar(int nSert)
{
	char cRet;

	UartRecv( nSert, &cRet,1 , 0);

	return cRet;
}

void init_com()
{
	char *usb_buff = 0;
	int uartHand = 0;

	osl_log_pause();//close log out

	uartHand = UartOpen(MPOS_PORT_COM, 115200, UART_DATABIT8, UART_STOPBIT1, UART_NOPARITY);

	usb_buff = (unsigned char *)MALLOC(MAX_UART_BUF);
	mf_appport_setfifo(usb_buff, MAX_UART_BUF);
}

void close_com()
{
	UartClose(MPOS_PORT_COM);
	osl_log_resume();
}

//static void _mpos_proc(void * pParam)
void _mpos_proc()
{
	int i;
	int recv_count; 
	int m_recv_index = 0;
	int data_len = 0;
	//unsigned int m_last_recv_tick = osl_GetTick();
	unsigned char check_sum = 0;
	//char *m_recv_buff = 0;
	//char *recv_tmp_buff = 0;
    unsigned char m_recv_buff[RECV_BUFF_SIZE+1];	
    unsigned char recv_tmp_buff[RECV_BUFF_SIZE+1];	


	//recv_tmp_buff = (unsigned char *)MALLOC(RECV_BUFF_SIZE);
	//m_recv_buff = (unsigned char *)MALLOC(RECV_BUFF_SIZE);



	while(UartGetRXBufCount(MPOS_PORT_COM) > 0){
// 		if(UartGetRXBufCount(MPOS_PORT_COM) <=0 ){
// 			if(osl_CheckTimeover(m_last_recv_tick , 1000) != 0){
// 				m_recv_index = 0;
// 				m_last_recv_tick = osl_GetTick();	
// 				APP_TRACE("UartRecv Fail\r\n");
// 				break;
// 			}
// 
// 			osl_Sleep(1);
// 			continue;
// 		}

//		m_last_recv_tick = osl_GetTick();
		memset(recv_tmp_buff, 0x00, sizeof(recv_tmp_buff));
		recv_count = UartRecv(MPOS_PORT_COM , recv_tmp_buff, MAX_UART_BUF, 0);

		APP_TRACE("-------------------------------------\r\n");
		APP_TRACE("-------------------------------------\r\n");
		APP_TRACE("UartRecv(%d):%s", recv_count, recv_tmp_buff);
		//APP_TRACE_BUFF(recv_tmp_buff, recv_count);
		APP_TRACE("-------------------------------------\r\n");
		APP_TRACE("-------------------------------------\r\n");
		//xgui_messagebox_show("UartRecv", recv_tmp, "" , "" , 0);

		memset(m_recv_buff, 0x00, sizeof(m_recv_buff));
		for (i = 0; i < recv_count; i ++)	{

			m_recv_buff[m_recv_index] = recv_tmp_buff[i];

			if (m_recv_index == 0){				// start 1
				if (m_recv_buff[m_recv_index] == STX_CODE_1)	
					m_recv_index ++;			// Correct, receive the next one	
				else
					m_recv_index = 0;			// Error, re-receive
			}
			else if (m_recv_index == 1){			
				if (m_recv_buff[m_recv_index] == STX_CODE_2)	
					m_recv_index ++;			// Correct, receive the next one
				else
					m_recv_index = 0;			// Error, re-receive
			}
			else if (m_recv_index >= 2 && m_recv_index < 5){						// Low length
				m_recv_index++;
			}
			else if (m_recv_index == 5){						// High length
				data_len = mpos_pub_get_len(&m_recv_buff[2]);

				if (data_len > RECV_BUFF_SIZE - 10)				// Length exceeded
					m_recv_index = 0;
				else
					m_recv_index ++;
			}
			else if (m_recv_index > 5)	{						// Start receiving data	
				data_len --;
				m_recv_index ++;
				if (data_len == 0){							// Receiving completed
					//check_sum = 0;
					//mpos_pub_check_sum_update(&check_sum , m_recv_buff + 2 , m_recv_index - 3);
					//if (m_recv_buff[m_recv_index -1] == ETX_CODE /*&& check_sum == m_recv_buff[m_recv_index -1]*/)	{	// Check the data correctly for some processing
					mpos_func_proc(m_recv_buff + 6, m_recv_index - 6);
					// 					}
					// 					else{
					// 						APP_TRACE_BUFF_TIP(m_recv_buff , m_recv_index , "recv check fail:");
					// 						//APP_TRACE("check_sum:%02X", check_sum);						
					// 					}

					m_recv_index = 0;				// Start receiving again
					memset(m_recv_buff,0x00,sizeof(m_recv_buff));
					
					return;
				}
			}
		}
	}
	//mf_appport_setfifo(0, 0);
	//FREE(usb_buff);
	//FREE(recv_tmp_buff);
	//FREE(m_recv_buff);

	//UartClose(MPOS_PORT_COM);
	//osl_log_resume();
}


// void mpos_proc_init(void)
// {
// 	 static int binit = 0;
// //	 OS_STK *pTaskStk;
// 
// 	 if (binit == 0)	{
// 		binit = 1;
// #ifndef WIN32
// //		osl_log_pause();	
// #endif
// //		pTaskStk = (OS_STK *) MALLOC((_MPOS_TASK_SIZE) * sizeof(OS_STK));
// 		 
// 		OSTaskCreateExt(_mpos_proc, 0, &pTaskStk[_MPOS_TASK_SIZE -1], _MPOS_TASK_PRIO , _MPOS_TASK_PRIO ,&(pTaskStk[0]) , _MPOS_TASK_SIZE , 0 , OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK);        
// 	 }
// }

