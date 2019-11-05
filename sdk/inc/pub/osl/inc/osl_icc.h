#pragma once

#include "driver/mf_icc.h"
#include "pub/pub.h"

typedef enum
{
	DEV_ICC_ICCID = ICC_SOCKET1,  //Card reader
	DEV_ICC_PSAM1 = ICC_SOCKET2,  //pasm1
	DEV_ICC_PSAM2 = ICC_SOCKET3	  //pasm2
}ICC_TYPE;


/**
* iccid,psam1,psam2 Read interface
* @param type[IN]: See above.
* @param psaIcc[OUT]: Read Data Buffer
* @param return: 
* -1: Failed to open device
* -2: Card in-place detection failed
* -3: Power failure
* -4: sim Carry File Selection Error
* -5: Error reading data
*/
LIB_EXPORT int osl_ReadIcc(ICC_TYPE type, char *pszIcc);	

