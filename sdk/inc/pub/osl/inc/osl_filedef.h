/*! \file osl_filedef.h
	\brief 文件系统封装
*	\author lx
*	\date 2014/02/08
*/
//文件宏定义
#ifndef _OSL_FILEDEF_H_
#define _OSL_FILEDEF_H_

#ifdef __cplusplus
extern "C"{
#endif


#include "pub\pub.h"



#if WIN32
	#include <io.h>
	#include <fcntl.h>
	#include <sys/stat.h>
	#include <stdio.h>
#elif OS_NOVA
	#include "nova_fs_api.h"
#elif OS_LINUX
	#include <fcntl.h>
	#include <sys/stat.h>
	#include <stdio.h>
#else
	#include "fatfs\ff.h"
#endif

#if WIN32

#elif OS_NOVA
	#define O_RDONLY		(NOVA_FS_MODE_READ)
	#define O_WRONLY		(NOVA_FS_MODE_WRITE)
	#define O_RDWR			(NOVA_FS_MODE_READ | NOVA_FS_MODE_WRITE)
	#define O_APPEND		(NOVA_FS_MODE_APPEND)

	#define O_CREAT			(NOVA_FS_MODE_CREATE_NEW)	  /* create and open file */
	#define O_TRUNC			(NOVA_FS_MODE_CREATE_ALWAYS)  /* open and truncate */
	#define O_EXCL			(NOVA_FS_MODE_OPEN_EXISTING)  /* open only if file doesn't already exist */

	#define O_BINARY		0x8000 
	#define S_IREAD			0x0100 
	#define S_IWRITE		0x0080 

	#define SEEK_SET        (NOVA_FS_SEEK_BEGIN)			/* seek to an absolute position */
	#define SEEK_CUR        (NOVA_FS_SEEK_CUR)				/* seek relative to current position */
	#define SEEK_END        (NOVA_FS_SEEK_END)				/* seek relative to end of file */



#elif OS_LINUX
	#define O_BINARY		0x0000
#else

	#define O_RDONLY		0x0000  /* open for reading only */
	#define O_WRONLY		0x0001  /* open for writing only */
	#define O_RDWR			0x0002  /* open for reading and writing */
	#define O_APPEND		0x0008  /* writes done at eof */

	#define O_CREAT			0x0100  /* create and open file */
	#define O_TRUNC			0x0200  /* open and truncate */
	#define O_EXCL			0x0400  /* open only if file doesn't already exist */

	#define O_BINARY		0x8000 

	#define S_IREAD			0x0100 
	#define S_IWRITE		0x0080 

	#ifndef SEEK_SET
	#define SEEK_SET        0               /* seek to an absolute position */
	#define SEEK_CUR        1               /* seek relative to current position */
	#define SEEK_END        2               /* seek relative to end of file */
	#endif 

#endif


#if WIN32
#define USE_WIN32_FS	1
#define PATH_MAX_SIZE	512
#elif OS_NOVA
#define USE_NOVA_FS		1
#define PATH_MAX_SIZE	512
#elif OS_LINUX
#define USE_LINUX_FS	1
#define PATH_MAX_SIZE	512
#else
#define USE_FATFS		1
#define PATH_MAX_SIZE	32
#endif


#define FILE_OPEN_FAIL (-1)

#define FILE_INIT			mf_file_init
#define FILE_OPEN			mf_file_open
#define	FILE_CLOSE			mf_file_close 
#define FILE_LSEEK			mf_file_lseek
#define FILE_WRITE			mf_file_write
#define FILE_READ			mf_file_read

#define FILE_UNLINK			mf_file_unlink
#define FILE_DELETE			mf_file_unlink	
//#define FILE_TELL			mf_file_tell
#define FILE_RENAME			mf_file_rename
#define FILE_FLUSH			mf_file_flush
#define FILE_MKDIR			mf_file_mkdir


	
#define FILE_WRITE_FLAG		(O_RDWR|O_CREAT|O_BINARY)
#define FILE_CREAT_FLAG		(O_RDWR|O_TRUNC|O_CREAT|O_BINARY)
#define FILE_WRITE_MODE		(S_IREAD| S_IWRITE)
#define FILE_READ_FLAG		(O_RDONLY|O_BINARY)
#define FILE_READ_MODE		(S_IREAD)

#define CHECK_INIT_FILE	"fileinit.dat"

/**
* @brief 文件系统初始化
* @return 
*/
LIB_EXPORT void mf_file_init();
/**
* @brief 打开文件
* @param name 文件名称
* @param flag 打开标志
* @param mode 打开模式
* @return <0失败 >=0文件句柄
*/
LIB_EXPORT int mf_file_open(const char * name , int flag , int mode);
/**
* @brief 文件定位
* @param fp 文件句柄
* @param pos 位置
* @param flag 标志
* @return 移动的位置
*/
LIB_EXPORT int mf_file_lseek(int fp , int pos  , int flag);
/**
* @brief 写文件
* @param fp 文件句柄
* @param buff 缓冲区
* @param size 长度
* @return 已写入长度
*/
LIB_EXPORT int mf_file_write(int fp ,const void * buff , unsigned int size);
/**
* @brief 读文件
* @param fp 文件句柄
* @param buff 缓冲区
* @param size 长度
* @return 已读取的长度
*/
LIB_EXPORT int mf_file_read(int fp , void * buff , unsigned int size);
/**
* @brief 关闭文件
* @param fp 文件句柄
* @return 
*/
LIB_EXPORT int mf_file_close(int fp );
/**
* @brief 删除文件
* @param name 文件名称
* @return 
*/
LIB_EXPORT int mf_file_unlink(const char * name);
/**
* @brief 重命名文件
* @param oldname 原文件名
* @param newname 新文件名
* @return 
*/
LIB_EXPORT int mf_file_rename(const char *oldname ,const char *newname);
/**
* @brief 文件系统是否已初始化
* @return 0 未初始化
*/
LIB_EXPORT int mf_file_get_init();
/**
* @brief 格式化文件系统
* @return 
*/
LIB_EXPORT int mf_file_format();


/**
* @brief 获取文件系统剩余空间
* @return 
*/
LIB_EXPORT int mf_file_space_free(); 

/**
* @brief 获取文件系统空间
* @return 
*/
LIB_EXPORT int mf_file_total_free();

/**
* @brief 截断文件
* @param fp 文件句柄
* @param size 文件大小
* @return 
*/
LIB_EXPORT int mf_file_truncate(int fp , int size);

/**
* @brief 设置数据目录，设置后原data开始的路径会替换成data_path
* @param data_path 目录
* @return 
*/
LIB_EXPORT void mf_file_set_path(char *data_path);

/**
* @brief 创建目录
* @param data_path 目录
* @return 
*/
LIB_EXPORT void mf_file_mkdir(char *data_path);

LIB_EXPORT int mf_file_space_task();

LIB_EXPORT void mf_find_dir(char * root , void *pfun);

#ifdef __cplusplus
}
#endif	

#endif	//_FILEDEF_H_


