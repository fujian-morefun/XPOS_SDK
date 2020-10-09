#pragma once


typedef enum{
	step_f1 = 0,
	step_f2,
	step_result,
}e_step;


typedef struct  _calnumber
{
	char str[9];
	int strlen;
}number;

typedef struct  _calculatorinfo
{
	e_step setp;
	number f1;
	number f2;
	number result;
	number memory;
	char op;
}calculator;


int cal_addkeycode(calculator *info , unsigned char keycode );

int cal_backspace(calculator *info );


int cal_addop(calculator *info ,unsigned char opchar );
int cal_compute(calculator *info );

int cal_result( calculator *info , double *ret);

int cal_show(calculator *info ,char *showbuff);

int cal_showfull(calculator *info ,char *full);

int cal_memory_clear( calculator *info );
int cal_memory_save( calculator *info );
int cal_memory_read( calculator *info );
int cal_memory_plus( calculator *info );
int cal_memory_subtract( calculator *info );