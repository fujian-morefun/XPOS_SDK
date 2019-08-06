#ifndef __EMV_READ_DATA__
#define __EMV_READ_DATA__


extern int Emv_Read_AppData(char *cTransMode);
extern int oda_Read_AppData(char *cTransMode);
extern int PayPass_Read_AppData(uchar ucTransMode,uchar ucActiveSfiSign);

extern int Dpas_Read_AppData(char *cTransMode);

int get_sm_terminal(void);

#endif