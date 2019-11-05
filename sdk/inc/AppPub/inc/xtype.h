//Basic type redefinition
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

//API calling convention	Function call Convention
#ifdef WIN32
#define APICC					__cdecl
#else
#define APICC
#endif

#ifdef WIN32
#define PACKED 
#else
#define PACKED  __attribute__((__packed__)) //µ¥×Ö½Ú¶ÔÆë
#endif

#ifndef MIN
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b)            (((a) < (b)) ? (b) : (a))
#endif

#define IN		//Input parameter identification
#define OUT		//Output parameter identification
#define INOUT	//Identification of input and output parameters

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
	X_ERR_OK,						//Successful operation
	X_ERR_ERROR,					//operation failed
	X_ERR_LOAD_LIBRARY_FAILED,	//Failure to import dynamic libraries
	X_ERR_GET_PROC_ADDR_FAILED,	//Failed to get function address in dynamic library
	X_ERR_INTERFACE_NO_EXIST,		//Interface does not exist
	X_ERR_INVALID_PARAM,	//illegal parameter
	X_ERR_FILE_OP,			//File operation error
	X_ERR_NO_MEMORY,		//insufficient memory
	X_ERR_NO_FLASH,			//FLASH deficiency
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


//Copy data from array2 to array1,
//Note: Aray1 and array are arrays, not pointers¡£
#define ARRAY_MEMCPY(array1, array2) memcpy(array1, array2, MIN(sizeof(array1), sizeof(array2)))

typedef int IBOOL;

#define PNULL	0

#endif //_XTYPE_H_
