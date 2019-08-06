/* 
 * Copyright (c) 2015 MoreFun
 *
 * @date 2015-06-04
 * @author ZhaoJinYun
 *
*/

#ifndef __MF_USB_CDC_H
#define __MF_USB_CDC_H

#ifdef __cplusplus
extern "C" {
#endif

int mf_usb_cdc_init(void);
int mf_usb_cdc_is_active(void);
int mf_usb_cdc_write(unsigned char *buf, int size);
int mf_usb_cdc_read(unsigned char *buf, int size);
int mf_cdc_put_char(unsigned char c);
void mf_usb_cdc_flush(void);

int mf_usb_cdc_data_avail(int *txlen, int *rxlen);

int mf_usb_cdc_setfifo(unsigned char *buf, int size);

//
//
//1024 + txsize + rxsize
//
//±ØÐë512×Ö½Ú¶ÔÆë
//#pragma data_alignment = 512
//unsigned char usbbuf[1024 + txsize + rxsize];
//
int mf_usb_cdc_set_mem(unsigned char *buf, int rxsize, int txsize);

#ifdef __cplusplus
}
#endif


#endif /* __MF_USB_CDC_H */



