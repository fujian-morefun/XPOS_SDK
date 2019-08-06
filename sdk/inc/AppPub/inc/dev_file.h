#ifndef _DEV_FILE_H
#define _DEV_FILE_H

#include "pub/pub.h"

#define FILE_NOCREATEINDEX 0x00	/*不创建索引文件*/
#define FILE_CREATEINDEX 0x01		/*创建索引文件*/
#define MAX_FILENAME_LEN 256		/*文件名最大长度*/

typedef struct tagRecFile
{
	unsigned int unMaxOneRecLen;	/*最大的单条记录长度*/  
	unsigned int unIndex1Start;	/*索引字段1的起始位置*/
	unsigned int unIndex1Len;		/*索引字段1的长度*/
	unsigned int unIndex2Start; 	/*索引字段2的起始位置*/
	unsigned int unIndex2Len;		/*索引字段2的长度*/
	char cIsIndex;				/*是否需要建立索引文件，0x00不建立，0x01建立*/
	char szFileName[MAX_FILENAME_LEN+1];		/*记录文件名,有效的记录文件名长度为8*/
	char s[2];
}STRECFILE;

/******************************************************************************
*	函数名称：Ex_File_CreatFile
*	函数介绍：创建文件
*	函数描述：
*	入口参数：const STRECFILE *pstRecFile 文件头信息
*	出口参数：
*	返回值  ：
*				SUCC 成功
*				FAIL   失败
*******************************************************************************/
LIB_EXPORT extern int Ex_File_CreatFile(const STRECFILE *pstRecFile);
/******************************************************************************
*	函数名称：Ex_File_DelFile
*	函数介绍：删除文件
*	函数描述：
*	入口参数：const char *pszFileName 流水文件名
*	出口参数：
*	返回值  ：
*		SUCC 成功
*		FAIL   失败
*******************************************************************************/
LIB_EXPORT extern int Ex_File_DelFile (const char *pszFileName);
/******************************************************************************
*	函数名称：Ex_File_GetRecSum
*	函数介绍：按文件名打开文件，获取文件记录总数
*	函数描述：
*	入口参数：
*		const char *pszFileName 流水文件名
*	出口参数：
*		int *pnRecSum 指向记录数量的指针
*	返回值  ：
*		SUCC 成功
*		FAIL   失败
*******************************************************************************/
LIB_EXPORT extern int Ex_File_GetRecSum (const char *pszFileName, int *pnRecSum);
/******************************************************************************
*	函数名称：Ex_File_AddRecByName
*	函数介绍：增加流水记录，对于创建记录是指定了需要建立索引文件的会相应增加索引记录。
*	函数描述：
*	入口参数：
*		const char *pszFileName 流水文件名
*		const char *pszRec 输入的流水记录
*	出口参数：无
*	返回值  ：
*		SUCC 成功
*		FAIL   失败
*******************************************************************************/
LIB_EXPORT extern int Ex_File_AddRecByName (const char *pszFileName, const char *pszRec);
/******************************************************************************
*	函数名称：Ex_File_UpdateRecByName
*	函数介绍：更新记录
*	函数描述：修改记录，按指定的记录位置重写指定的记录。
*				   同时对于创建记录是指定了需要建立索引文件的
*				   会相应更新索引记录。
*	入口参数：
*		const char *pszFileName 记录文件名称
*		const int nRecNo 要修改的记录号
*		char *psRec 记录指针
*	出口参数：
*	返回值  ：
*		SUCC 成功
*		FAIL   失败
*******************************************************************************/
LIB_EXPORT extern int Ex_File_UpdateRecByName (const char *pszFileName, const int nRecNo, const char *psRec);
/******************************************************************************
*	函数名称：Ex_File_ReadRecByName
*	函数介绍：按记录号读取单条记录
*	函数描述：
*	入口参数：
*		const char *pszFileName 记录文件名称
*		const int nRecNo 要修改的记录号
*		char *psRec 记录指针
*	出口参数：
*	返回值  ：
*		SUCC 成功
*		FAIL   失败
*******************************************************************************/
LIB_EXPORT extern int Ex_File_ReadRecByName(const char *pszFileName, const int nRecNo, char *psRec);
/******************************************************************************
*	函数名称：DelRecByFileName
*	函数介绍：按索引删除记录
*	函数描述：根据索引字段1/索引字段2从指定的记录号开始查找并删除记录，
*				   若同时指定索引字段1/索引字段2，则要同时满足这两个
*				   条件的记录输出，不指定时用NULL,若符合索引条件的记录
*				   存在重复的情况，输出第一条记录。
*	入口参数：
*		const char *pszFileName 记录文件名称
* 		const char *psIndexStr1 索引字段1
*		const char *psIndexStr2 索引字段2
*	出口参数：
*		无
*	返回值  ：
*******************************************************************************/
LIB_EXPORT extern int Ex_File_DelRecByName(const char *pszFileName, const char *psIndexStr1,const char *psIndexStr2);
/******************************************************************************
*	函数名称：Ex_File_ReadRecByHandle
*	函数介绍：按记录号读流水记录。
*	函数描述：
*	入口参数：
*		const int nFileHandle 打开的文件句柄
*		const int nRecNo 要找的记录号
*	出口参数：
*		char *psRec 记录指针
*	返回值  ：
*		SUCC 成功
*		FAIL   失败
*******************************************************************************/
LIB_EXPORT extern int Ex_File_ReadRecByHandle (const int nFileHandle, const int nRecNo, char *psRec , const char *pszName);
/******************************************************************************
*	函数名称：Ex_File_UpdateRecByHandle
*	函数介绍：更新记录
*	函数描述：修改记录，按指定的记录位置重写指定的记录。
*				   同时对于创建记录是指定了需要建立索引文件的
*				   会相应更新索引记录。
*	入口参数：
*		int  nFileHandle 记录文件句柄
*		const int nRecNo 要修改的记录号
*		char *psRec 记录指针
*	出口参数：
*	返回值  ：
*		SUCC 成功
*		FAIL   失败
*******************************************************************************/
LIB_EXPORT extern int Ex_File_UpdateRecByHandle (int nFileHandle, const int nRecNo, const char *psRec);
/******************************************************************************
*	函数名称：Ex_File_FindRec
*	函数介绍：按索引查找记录
*	函数描述：根据索引字段1/索引字段2从指定的记录号开始查找记录，
*				   若同时指定索引字段1/索引字段2，则要同时满足这两个
*				   条件的记录输出，不指定时用NULL,若符合索引条件的记录
*				   存在重复的情况，输出第一条记录。
*	入口参数：
*		const char *pszFileName 记录文件名称
* 		const char *psIndexStr1 索引字段1
*		const char *psIndexStr2 索引字段2
*		const int nBeginRecNo 指定的开始记录号
*	出口参数：
*		char *psRec 记录指针
*		int *pnRecNo 符合条件的记录号
*	返回值  ：
*		SUCC 成功
*		FAIL   失败
*******************************************************************************/
LIB_EXPORT extern int Ex_File_FindRec(const char *pszFileName, const char *psIndexStr1,
			   const char *psIndexStr2,const int nBeginRecNo, char *psRec, int *pnRecNo);
/******************************************************************************
 *  	函数名称:	Ex_File_GetParam: 
 *	函数介绍:	从参数文件中读取参数信息
 *	入口参数:	nOff 参数偏移地址
 					nLen 参数数据长度
 *	出口参数:     pszOutData 输出字符串指针
 * 	返回值  :		
 ******************************************************************************/
LIB_EXPORT int Ex_File_GetParam(char *pszFileName,char *pszOutData, int nOff, int nLen);
//从带头的参数文件中读取参数信息
LIB_EXPORT int Ex_FileHead_GetParam(char *pszFileName,char *pszOutData, int nOff, int nLen);
/******************************************************************************
 *  	函数名称:	Ex_File_SaveParam: 
 *	函数介绍:	保存参数到参数文件中
 *	入口参数:	pszFileName 文件名
 					nOff 参数偏移地址
 					nLen 参数数据长度
 					pszInData 输入的字符串指针
 *	出口参数:     
 * 	返回值  :		SUCC
 					FAIL
 ******************************************************************************/
LIB_EXPORT extern int Ex_File_SaveParam(char *pszFileName,char *pszInData, int nOff, int nLen);
#endif