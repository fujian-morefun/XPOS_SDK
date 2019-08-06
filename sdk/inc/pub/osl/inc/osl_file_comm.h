/*! \file osl_file_comm.h
	\brief 文件操作
*	\author lx
*	\date 2014/02/08
*/
#ifndef _FILE_COMM_H_
#define _FILE_COMM_H_

#include "pub\pub.h"

#ifdef __cplusplus
extern "C"{
#endif


/**
* @brief 创建文件夹
* @param dir_name 文件夹名称
* @return 1成功
*/
LIB_EXPORT int Dir_Create(char * dir_name);

/**
* @brief 删除文件夹
* @param dir_name 文件夹名称
* @return 1成功
*/
LIB_EXPORT int Delete_Create(char * dir_name);

/**
* @brief 创建文件
* @param file_name 文件名称
* @return 1成功
*/
LIB_EXPORT int File_Create(char * file_name);
/**
* @brief 删除文件
* @param file_name 文件名称
* @return 
*/
LIB_EXPORT int File_Delete(char * file_name);
/**
* @brief 读取一块数据
* @param hfile 文件句柄
* @param read_start 开始位置
* @param read_buff 缓冲区
* @param read_size 读取长度
* @return 已读的长度
*/
LIB_EXPORT int File_ReadBlock( int hfile, int read_start, char * read_buff, int read_size);
/**
* @brief 读取一块数据
* @param file_name 文件名称
* @param read_start 起始位置
* @param read_buff 缓冲区
* @param read_size 读取长度
* @return 已读的长度
*/
LIB_EXPORT int File_ReadBlockByName(char * file_name,int read_start,char * read_buff,int read_size);
/**
* @brief 写一块数据
* @param hfile 文件句柄
* @param write_start 起始位置
* @param write_buff 缓冲区
* @param write_size 写长度
* @return 已写的长度
*/
LIB_EXPORT int File_WriteBlock(int hfile,int write_start, char * write_buff,int write_size);
/**
* @brief 写一块数据
* @param file_name 文件名称
* @param write_start 起始位置
* @param write_buff 缓冲区
* @param write_size 写长度
* @return 已写的长度
*/
LIB_EXPORT int File_WriteBlockByName(char * file_name,int write_start, char * write_buff,int write_size);
/**
* @brief 添加一块数据
* @param hfile 文件句柄
* @param write_buff 缓冲区
* @param write_size 写长度
* @return 已写的长度
*/
LIB_EXPORT int File_AppendBlock(int hfile,char * write_buff,int write_size);
/**
* @brief 添加一块数据
* @param file_name 文件名称
* @param write_buff 缓冲区
* @param write_size 写长度
* @return 已写的长度
*/
LIB_EXPORT int File_AppendBlockByName(char * file_name,char * write_buff,int write_size);
/**
* @brief 文件是否存在
* @param file_name 文件名称
* @return 1存在
*/
LIB_EXPORT int File_Exist(char *file_name);
/**
* @brief 获取文件长度
* @param hfile 文件句柄
* @return 长度
*/
LIB_EXPORT int File_GetLength(int hfile);
/**
* @brief 填充文件
* @param hfile 文件句柄
* @param file_length 填充到长度
* @param fill_char 填充的字符
* @return 1成功
*/
LIB_EXPORT int File_SetLength(int hfile, unsigned int file_length, char fill_char);
/**
* @brief 写文件
* @param file_name 文件名称
* @param write_buff 缓冲区
* @param write_size 长度
* @return 1成功
*/
LIB_EXPORT int File_Write(char * file_name,char * write_buff,int write_size);
/**
* @brief 读文件
* @param file_name 文件名称
* @param read_buff 缓冲区
* @param read_size 长度
* @return 1成功
*/
LIB_EXPORT int File_Read(char * file_name,char * read_buff,int read_size);
/**
* @brief 添加一块数据
* @param file_name 文件名称
* @param write_buff 缓冲区
* @param write_size 长度
* @return 1成功
*/
LIB_EXPORT int File_Append(char * file_name,char * write_buff,int write_size);
/**
* @brief 获取文件长度
* @param file_name 文件名称
* @return 长度
*/
LIB_EXPORT int File_GetLengthByName(char * file_name);
/**
* @brief 获取磁盘剩余空间
* @return 剩余空间
*/
LIB_EXPORT int File_GetDataFreeSpace();
/**
* @brief 获取文件名
* @param pPath 路径
* @return  文件名指针
*/
LIB_EXPORT char * File_GetFileName(char * pPath);
/**
* @brief 获取整个文件数据
* @param FileName 文件名称
* @param pDst 缓冲区
* @return 读取的大小
*/
LIB_EXPORT int File_GetData(const char * FileName, void * pDst);
/**
* @brief 读取文件大小
* @param FilePath 文件名称
* @return 
*/
LIB_EXPORT int File_GetFileLength(const char * FilePath);
/**
* @brief 输出文件内容
* @param name 文件名称
* @param flag 0-16机制 1-字符方式
* @return 
*/
LIB_EXPORT void File_Trace(char *name , int flag);

/**
* @brief 输出文件内容
* @param pszSrcFn		[IN]	源文件名
* @param pDestFn		[IN]	目标文件名
* @return 0 失败  1 成功
*/
LIB_EXPORT  int File_Copy(const char* pszSrcFn, const char* pDestFn);

#ifdef __cplusplus
}
#endif	

#endif
