#include "pub/osl/inc/osl_timer.h"
#include "sdk_timer.h"

static int timerHandle = -1;
static int count = 0;

static unsigned int timerProc(void *p)
{
	count ++;
	return 0;
}





int sdk_timer_get_count()
{
	return count ;
}

void sdk_timer_init()
{
	if(timerHandle == -1){
		timerHandle = osl_TimerCreate(timerProc, 0 , 1000, TIMER_MODE_NORMAL , 0); 
		osl_TimerEnable(timerHandle);
	}
	
}