/* 
 * Copyright (c) 2015 MoreFun
 *
 * @date 2015-3-15
 * @author ZhaoJinYun
 *
*/


#ifndef __MF_ICC_H
#define __MF_ICC_H


#ifdef __cplusplus
extern "C" {
#endif

enum
{
	ICC_SOCKET1 = 0, //SMART CARD
	ICC_SOCKET2, //TSAM
	ICC_SOCKET3,
};

int icc_open(int socket);
int icc_close(int socket);

int icc_present(int socket);
int icc_powerup(int socket, unsigned char * atrstr, int buflen);
int icc_powerdown(int socket);
int icc_send_apdu(int socket, unsigned char *buffer, unsigned short length, unsigned char *rbuffer);

int icc_highspeed(int socket, int status);


#ifdef __cplusplus
}
#endif

#endif /* __MF_ICC_H */

