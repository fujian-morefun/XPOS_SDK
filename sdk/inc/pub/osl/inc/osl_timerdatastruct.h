#pragma once

#define TIMER_PRECISION			1
#define TIMER_PRESCALE			64
#define TIMER_MODE_CRITICAL		0xF0AAAA1F
#define TIMER_MODE_NORMAL		0xF0AAAA0F

#define TIMER_STATUS_ENABLE		1
#define TIMER_STATUS_DISABLE 	0

typedef  unsigned int ( *TIMERFUNCTION)(void *);

//定时器数据结构描述
typedef struct	__timer_entry_tag{

	unsigned int nTimerNo;	//定时器编号
	unsigned int nTaskId;		//定时器所处的优先级		
	TIMERFUNCTION pWorkFunction;	//定时器工作线程
	void *pParam;		//定时器工作线程参数
	unsigned int nPeriod; //定时周期
	unsigned int nCurTime;
	unsigned int nMode;	//定时器执行模式
	unsigned int nStatus;	//定时器状态
} TIMERENTRYTAG;

//定时器链表项
typedef struct __timer_entry_node{
	TIMERENTRYTAG *pTimerEntry;	
	struct __timer_entry_node *pNext;
}TIMERENTRYNODE;


