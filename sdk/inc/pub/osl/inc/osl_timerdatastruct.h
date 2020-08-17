#ifndef __OSL_TIMERDATA_STRUCT__
#define __OSL_TIMERDATA_STRUCT__

#pragma once

#define TIMER_PRECISION			1
#define TIMER_PRESCALE			64
#define TIMER_MODE_CRITICAL		0xF0AAAA1F
#define TIMER_MODE_NORMAL		0xF0AAAA0F

#define TIMER_STATUS_ENABLE		1
#define TIMER_STATUS_DISABLE 	0

typedef  unsigned int ( *TIMERFUNCTION)(void *);

//Description of Timer Data Structure
typedef struct	__timer_entry_tag{

	unsigned int nTimerNo;	//Timer number
	unsigned int nTaskId;		//Priority of Timer		
	TIMERFUNCTION pWorkFunction;	//Timer Work Thread
	void *pParam;		//Timer Work Thread Parameters
	unsigned int nPeriod; //Timing period
	unsigned int nCurTime;
	unsigned int nMode;	//Timer execution mode
	unsigned int nStatus;	//Timer status
} TIMERENTRYTAG;

//Timer list item
typedef struct __timer_entry_node{
	TIMERENTRYTAG *pTimerEntry;	
	struct __timer_entry_node *pNext;
}TIMERENTRYNODE;


#endif