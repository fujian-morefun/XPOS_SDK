/* 
 * Copyright (c) 2015 MoreFun
 *
 * @date 2015-02-13
 * @author ZhaoJinYun
 *
*/

#ifndef __MF_SPI_FLASH_H
#define __MF_SPI_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void mf_flash_init(void);
unsigned int mf_flash_readid(void);

void mf_flash_erase_sector(unsigned int sector_addr);
void mf_flash_erase_bulk(void);

int mf_flash_erase(unsigned int sector_addr, int size);

int mf_flash_write(unsigned char *wbuf, unsigned int addr, int size);
int mf_flash_read(unsigned char *rbuf, unsigned int addr, int size);

int mf_flash_syncobj(int (*lock)(int status));

int mf_flash_lock(void);
int mf_flash_unlock(void);

void mf_flash_erase_sector_free(unsigned int sector_addr);
int mf_flash_write_free(unsigned char *wbuf, unsigned int addr, int size);
int mf_flash_read_free(unsigned char *rbuf, unsigned int addr, int size);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MF_SPI_FLASH_H */


