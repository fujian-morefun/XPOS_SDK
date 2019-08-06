#ifndef __MESSAGEDATASTRUCT_H__
#define __MESSAGEDATASTRUCT_H__

#include "xgui_pub.h"

#define MESSAGE_ERR_NO_ERR		0
#define MESSAGE_ERR_MEM_ERR		-1
#define MESSAGE_ERR_NULL_ERR	-2
#define MESSAGE_ERR_TIME_OVER	-3
#define MESSAGE_ERR_OTHER_ERR	-99

#define MESSAGE_MAX_NUMS	100

#define POWER_MESSAGE_BIT	(1<<0)
#define SYSTEM_MESSAGE_BIT	(1<<1)

#define KEY_MESSAGE_BIT		(1<<5)
#define UART_MESSAGE_BIT	(1<<6)
#define POINTER_MESSAGE_BIT	(1<<7)

#define GUI_MESSAGE_BIT		(1<<10)
#define USER_MESSAGE_BIT	(1<<14)

#define ALL_MESSAGE_BIT		(0xFF)


typedef struct st_mfs_message{
	void * hDest;
	unsigned int MessageId;
	unsigned int WParam;
	unsigned int LParam;
	unsigned int time;
}MESSAGE, *PMESSAGE;

typedef struct st_message_list
{
	MESSAGE Msg;
	struct st_message_list * next;
}MESSAGELIST, * PMESSAGELIST;


#endif



