#ifndef _MF_ICC_H_
#define _MF_ICC_H_


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

