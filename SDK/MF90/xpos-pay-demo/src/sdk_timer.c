#include "pub/osl/inc/osl_timer.h"
#include "sdk_timer.h"

static int timerHandle = -1;
static int count = 0;

static unsigned int timerProc(void *p)
{
	// This timer callback function will be executed every second, in the timer thread.
	// You can do some short-term operations here, 
	// but don't block it all the time, which will affect the scheduling of the system's tasks.
	count ++;
	return 0;
}



//

int sdk_timer_get_count()
{
	// You can call this function in the ui thread to read, the number of executions of the timer thread
	return count ;
}

void sdk_timer_init()
{
	if(timerHandle == -1){
		// Create a timer
		timerHandle = osl_TimerCreate(timerProc, 0 , 1000, TIMER_MODE_NORMAL , 0); 
		osl_TimerEnable(timerHandle);  // Start this timer
	}
	
}