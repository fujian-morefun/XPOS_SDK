#include <stdlib.h>
#include "calculator.h"

#define ERRORSTR  "!!!ERROR!!!"


static double number_value( number * src)
{
	double ret = atof( src->str );

	return ret;
}
static int number_empty( number * src )
{
	memset(src,0x00, sizeof(number));
	return 0;
}
static int number_copy( number * dst, number * src )
{
	memcpy(dst,src, sizeof(number));
	return 0;
}

#ifdef WIN32
#define _snprintf sprintf_s
#else
#define _snprintf snprintf
#endif

static int trimzreo(char*numstr)
{
	char *pend = numstr + strlen(numstr) -1;
	

	if ( strchr(numstr,'.') != 0 )
	{
		while ( pend > numstr )
		{
			if ( *pend =='0')
			{
				*pend = 0;
				pend--;
			}
			else if ( *pend =='.')
			{
				*pend = 0;
				pend--;
				break;
			}
			else{
				break;
			}
		}
	}
	return strlen(numstr);

}


static int number_setvalue( number * src , double val)
{
	char a[64];
	int ret = 0;
	ret = _snprintf(a,sizeof(a),"%f", val );
	ret = trimzreo(a);
	if ( ret >= sizeof(src->str) )
	{
		sprintf(src->str,"%s", ERRORSTR );
		src->strlen = 0;
	}
	else{
		strcpy( src->str, a);
		src->strlen = strlen(src->str);
	}
	return 0;
}
static int number_tostring( number * src , char *outbuff)
{
	return sprintf(outbuff,"%s" , src->str );
}

static int number_exist( number * src)
{
	return src->strlen > 0;
}
static int number_append( number * src,unsigned int keycode)
{
	if ( src->strlen < sizeof(src->str) -1 )
	{
		src->str[src->strlen++] = keycode;
		src->str[src->strlen] = 0;
	}

	return src->strlen;
}
static int number_appendpoint( number * src)
{
	if ( src->strlen < sizeof(src->str)-1 )
	{
		if ( src->strlen == 0 )
		{
			strcpy(src->str,"0.");
			src->strlen = 2;
		}
		else{
			if ( strstr( src->str,".") == 0 )
			{
				src->str[src->strlen++] = '.';
				src->str[src->strlen] = 0;
			}
		}

	}

	return src->strlen;
}

static int number_backspace( number * src)
{
	if ( src->strlen > 0 )
	{
		src->strlen--;
		src->str[src->strlen] = 0;
	}

	return src->strlen;
}

static number * cal_number_current( calculator *info)
{
	if ( info->setp == step_f1)
	{
		return &info->f1;
	}
	else if ( info->setp == step_f2)
	{
		return &info->f2;
	}
	else if ( info->setp == step_result)
	{
		return &info->result;
	}
	return 0;
}

int cal_addkeycode( calculator *info , unsigned char keycode )
{
	number *current = 0;

	if (info->setp == step_result )
	{
		info->setp = step_f1;
		number_empty(&info->f1);
	}

	current = cal_number_current( info);

	if ( keycode == '.' )
	{
		return number_appendpoint( current );
	}
	else{
		return number_append( current , keycode );
	}

}

int cal_backspace(calculator *info )
{
	number *current = 0;
	current = cal_number_current( info);
	number_backspace( current );
	return 0;
}

static double cal_op_result(calculator *info )
{
	double result=0;

	double f1 = number_value(&info->f1);
	double f2 = number_value(&info->f2);

	switch( info->op )
	{
	case '+':
		{
			result = f1+f2;
		}
		break;
	case '-':
		{
			result = f1-f2;
		}
		break;
	case '*':
		{
			result = f1*f2;
		}
		break;
	case '/':
		{
			if ( f2 == 0)
			{

			}
			else{
				result = f1/f2;
			}
		}
		break;
	}
	return result;

}

int cal_addop(calculator *info ,unsigned char opchar )
{
	if (info->setp == step_f2 )
	{
		double result = cal_op_result(info );
		number_setvalue(&info->f1 ,result);
	}
	
	if (info->setp == step_result )
	{
		number_copy( &info->f1 , &info->result );
	}

	switch(opchar)
	{
	case '+':
	case '-':
	case '*':
	case '/':
		{
			info->op = opchar;
			number_empty(&info->f2);
			info->setp = step_f2;
		}
		break;
	}
	return 0;
}

int cal_compute(calculator *info  )
{
	double result;
	if ( info->setp == step_f1 )
	{
		return -1;
	}
	if (info->setp == step_result )
	{
		number_copy( &info->f1 , &info->result );
	}
	else if ( info->setp == step_f2 )
	{
		if ( number_exist( &info->f2 ) == 0)
		{
			number_copy( &info->f2 , &info->f1 );
		}
	}
	
	result = cal_op_result( info );

	number_setvalue( &info->result, result);
	info->setp = step_result;
	return 0;
}

int cal_result( calculator *info , double *ret)
{
	if ( info->setp == step_f1 )
	{
		*ret = number_value(&info->f1);
		return 1;
	}

	if ( info->setp == step_result )
	{
		*ret = number_value(&info->result);
		return 1;
	}
	return 0;
}

int cal_show( calculator *info ,char *showbuff )
{
	char tmp[32];
	number *current = 0;
	current = cal_number_current( info);
	if ( info->setp == step_f2 )
	{
		if ( number_exist( &info->f2) == 0 )
		{
			current = &info->f1;
		}
	}

	number_tostring( current, tmp );

	if ( number_exist( &info->memory ))
	{
		sprintf(showbuff,"M%15s", tmp);
	}
	else{
		sprintf(showbuff," %19s", tmp);
	}
	return 0;
}

int cal_showfull( calculator *info ,char *full )
{
	char tmp1[32];
	char tmp2[32];

	number_tostring( &info->f1, tmp1 );
	number_tostring( &info->f2, tmp2 );

	strcpy(full,"");
	if ( info->setp == step_f1  )
	{
		//return sprintf( full,"%s" , tmp1);
	}
	else 
	{
		return sprintf( full,"%s%c%s" , tmp1, info->op, tmp2);
	}
	

	return 0;

}

int cal_memory_clear( calculator *info )
{
	number_empty( &info->memory);
	return 0;
}

int cal_memory_save( calculator *info )
{	
	number *current = 0;
	current = cal_number_current( info);

	number_copy( &info->memory, current );
	return 0;
}

int cal_memory_read( calculator *info )
{
	number *current = 0;
	current = cal_number_current( info);
	
	if ( number_exist( &info->memory ) == 1)
	{
		number_copy(current, &info->memory );
	}
	return 0;
}

int cal_memory_op( calculator *info , char opchar )
{
	double f1;
	double f2;
	double result;

	number *current = cal_number_current( info);

	if ( number_exist( &info->memory ) == 1 )
	{
		f1 = number_value(&info->memory);
	}
	else{
		f1 = 0;
	}

	f2 = number_value(current);

	switch(opchar){
		case '+':
			result = f1 + f2;
			break;
		case '-':
			result = f1 - f2;
			break;
	}

	number_setvalue( &info->memory, result);

	return 0;
}

int cal_memory_plus( calculator *info )
{
	return cal_memory_op(info,'+');
}

int cal_memory_subtract( calculator *info )
{
	return cal_memory_op(info,'-');
}

