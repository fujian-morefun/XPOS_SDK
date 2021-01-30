#pragma once

#include "libapi_pub.h"

#define RKI_MODE_Mosambee  1


LIB_EXPORT int rki_init(int mode);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:rki_load_key
Input : index keydata index
Output: keydata buffer
return: keydata length
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int rki_load_key(int index, char *keydata);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:George
Functions:check_app_key
Input : sha256 value of app KEY 
Output: null
return: check result: 1 success 0 fail
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int check_app_key(unsigned char *sHashValue);

