//基本类型重定义
#ifndef _XTYPE_H_
#define _XTYPE_H_

#ifdef WIN32
//{
#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
//}
#else
//{
#define DLL_API
//}
#endif

#ifndef NULL
#define NULL					(0)
#endif

#ifndef FALSE
#define FALSE					(0)
#endif
 
#ifndef TRUE
#define TRUE					(1)
#endif

//API calling convention	函数调用约定
#ifdef WIN32
#define APICC					__cdecl
#else
#define APICC
#endif

#ifdef WIN32
#define PACKED 
#else
#define PACKED  __attribute__((__packed__)) //单字节对齐
#endif

#ifndef MIN
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b)            (((a) < (b)) ? (b) : (a))
#endif

#define IN		//输入参数标识
#define OUT		//输出参数标识
#define INOUT	//输入输出参数标识

typedef int						XBOOL;
typedef signed char				XINT8;
typedef unsigned char			XUINT8;
typedef short int				XINT16;
typedef unsigned short 			XUINT16;
typedef unsigned int			XUINT32;
typedef signed int				XINT32;
typedef unsigned long long		XUINT64;
typedef signed long long		XINT64;
typedef float					XFLOAT32;
typedef double					XDOUBLE64;

typedef enum
{
	X_ERR_OK,						//操作成功
	X_ERR_ERROR,					//操作失败
	X_ERR_LOAD_LIBRARY_FAILED,	//导入动态库失败
	X_ERR_GET_PROC_ADDR_FAILED,	//获取动态库中的函数地址失败
	X_ERR_INTERFACE_NO_EXIST,		//接口不存在
	X_ERR_INVALID_PARAM,	//非法参数
	X_ERR_FILE_OP,			//文件操作错误
	X_ERR_NO_MEMORY,		//内存不足
	X_ERR_NO_FLASH,			//FLASH不足
}X_ERROR_CODE_E;

#define SCI_ALLOC				malloc
#define SCI_FREE(mem_ptr)		{if(mem_ptr != NULL) { free(mem_ptr); mem_ptr = NULL;}}
#define SCI_SAFE_FREE(mem_ptr)	SCI_FREE(mem_ptr)
#define SCI_MEMSET				memset
#define SCI_MEMCPY				memcpy

#define BETWEEN(VAL, vmin, vmax) ((VAL) >= (vmin) && (VAL) <= (vmax))
#define ISHEXCHAR(VAL) (BETWEEN(VAL, '0', '9') || BETWEEN(VAL, 'A', 'F') || BETWEEN(VAL, 'a', 'f'))


#define IN
#define OUT

#define MF_ASSERT(X)
#define SCI_ASSERT
#define SCI_Sleep		sys_msleep


//将数据从array2拷到array1,
//注意: array1 与 array都是数组，不能是指针。
#define ARRAY_MEMCPY(array1, array2) memcpy(array1, array2, MIN(sizeof(array1), sizeof(array2)))

typedef int IBOOL;

#define PNULL	0

#endif //_XTYPE_H_
