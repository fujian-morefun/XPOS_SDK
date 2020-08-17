#ifndef _MF_SERIAL_H_
#define _MF_SERIAL_H_

#ifdef __cplusplus
extern "C" {
#endif

enum
{
	MF_UART_COM1 = 1,
	MF_UART_COM2,
	MF_UART_COM3,
	MF_UART_COM4,
	MF_UART_COM20 = 20,
	MF_UART_COM21,
	MF_UART_COM22,
};

#define MF_UART_WordLength_8b                  (0x0000)
#define MF_UART_WordLength_9b                  (0x1000)


#define MF_UART_StopBits_1                     (0x0000)
#define MF_UART_StopBits_0_5                   (0x1000)
#define MF_UART_StopBits_2                     (0x2000)
#define MF_UART_StopBits_1_5                   (0x3000)


#define MF_UART_Parity_No                      (0x0000)
#define MF_UART_Parity_Even                    (0x0400)
#define MF_UART_Parity_Odd                     (0x0600)


/* modem lines */
#define TIOCM_LE			(0x001)
#define TIOCM_DTR			(0x002)
#define TIOCM_RTS			(0x004)
#define TIOCM_ST			(0x008)
#define TIOCM_SR			(0x010)
#define TIOCM_CTS			(0x020)
#define TIOCM_CAR			(0x040)
#define TIOCM_RNG			(0x080)
#define TIOCM_DSR			(0x100)
#define TIOCM_CD			(TIOCM_CAR)
#define TIOCM_RI			(TIOCM_RNG)
#define TIOCM_OUT1			(0x2000)
#define TIOCM_OUT2			(0x4000)
#define TIOCM_LOOP			(0x8000)



int mf_serial_open(int com, int baudrate, int wordlength, int stopbits, int parity);
int mf_serial_close(int com);

int mf_serial_write(int com, unsigned char *buf, int size);
int mf_serial_read(int com, unsigned char *buf, int size, int milliseconds);

int mf_serial_flush(int com);

int mf_serial_data_avail(int com, int *txlen, int *rxlen);
int mf_serial_free_avail(int com, int *txlen, int *rxlen);

int mf_serial_set_mctrl(int com, unsigned int mctrl);
int mf_serial_get_mctrl(int com);

#ifdef __cplusplus
}
#endif

#endif /* __MF_SERIAL_H */

