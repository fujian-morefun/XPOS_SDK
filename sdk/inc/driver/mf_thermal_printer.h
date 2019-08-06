/* 
 * Copyright (c) 2015 MoreFun
 *
 * @date 2015-02-11
 * @author ZhaoJinYun
 *
*/

#ifndef __MF_THERMAL_PRINTER_H
#define __MF_THERMAL_PRINTER_H

#ifdef __cplusplus
extern "C" {
#endif

int mf_thermal_printer_init(void);
int mf_thermal_printer_fini(void);

int mf_thermal_printer_write(unsigned char *buf, int size);
int mf_thermal_printer_nopaper(void);
int mf_thermal_printer_flush(void);
int mf_thermal_printer_space(void);
int mf_thermal_printer_status(void);
int mf_thermal_printer_heatfactor(int factor);

#ifdef __cplusplus
}
#endif


#endif /* __MF_THERMAL_PRINTER_H */

