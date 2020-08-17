#ifndef __LIBAPI_FILE_HEADER__
#define __LIBAPI_FILE_HEADER__


#include "def.h"

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.3	获取文件类模块版本号(UFile_GetModuleVer)
输入参数：无
输出参数：pszVer   模块版本号
返    回：成功返回模块版本号长度
		UFILE_FAIL   =-1,           //失败
备	 注: 无
*************************************************************************************/
int UFile_GetModuleVer(char *pszVer);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.4	检测文件是否存在（UFile_Check）
输入参数：FileName：文件名, 以NULL结束，最长16个字节
		iFileLocation: 存储位置，参见enum FILELOCATION
输出参数：无
返    回：UFILE_NO_EXIST       = -12,             //指定的文件不存在
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_SUCCESS        =  0               //文件操作成功
备	 注: 无
*************************************************************************************/
int UFile_Check(cchar *FileName, int iFileLocation);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.5	文件打开/创建（UFile_OpenCreate）
输入参数：FileName：打开文件名, 以NULL结束，最长16个字节
		iFileLocation: 存储位置，参见enum FILELOCATION
		Flag：打开文件方式, 取值参考FileFlags定义
		RecSize：文件记录大小（联迪专用）
		RecSize = 0,创建打开 流式文件，文本文件
		RecSize = 1，创建打开 非定长记录（TLV）文件
		8<=RecSize<=4090 创建打开定长记录文件
输出参数：Fh：文件句柄
返    回：UFILE_NO_EXIST       = -12,             //指定的文件不存在
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_OPEN_FAIL  	= -2,              //打开错误
		UFILE_FAIL			= -1,              //文件操作失败
		UFILE_SUCCESS        =  0               //文件操作成功
备	 注: 对于新创建的文件RecSize才有作用；
		对于打开已创建的文件，应忽略RecSize参数。
*************************************************************************************/
int UFile_OpenCreate(cchar *FileName, int iFileLocation, int Flag, FILE_HANDLE *fh, int RecSize);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.6	文件读取（UFile_Read）
输入参数：handle：读取的文件句柄
		size：读取的数据大小
输出参数：buffer：读出数据
返    回：文件读取成功：返回值等于实际读取到的字节数
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_READ_FAIL		= -5,              //读错误
		UFILE_FAIL			= -1,              //文件操作失败
备	 注: 无
*************************************************************************************/
int UFile_Read(FILE_HANDLE handle, char *buffer, int size);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.7	文件写入（UFile_Write）
输入参数：handle：读取的文件句柄
		size：待写入的数据大小
		buffer：待写入的数据
输出参数：无
返    回：文件写入成功：返回值等于实际写入的字节数
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_WRITE_FAIL		= -4,              //写错误
		UFILE_FAIL			= -1,              //文件操作失败
备	 注: 无
*************************************************************************************/
int UFile_Write(FILE_HANDLE handle, char *buffer, int size);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.8	定位文件指针（UFile_Lseek）
输入参数：handle：文件句柄
		offset：偏移量
		origin：开始位置，参看FileSeekFlags类型
输出参数：无
返    回：UFILE_PARAERROR      = -11，            //参数错
		UFILE_SEEK_FAIL	   = -6,              //定位文件指针错误
		UFILE_SUCCESS        =  0
备	 注: 无
*************************************************************************************/
long UFile_Lseek(FILE_HANDLE handle, long offset, int origin);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.9	删除文件记录（UFile_Delete）
输入参数：handle：文件句柄
		size：删除的文件字节数
输出参数：无
返    回：UFILE_PARAERROR      = -11，            //参数错
		UFILE_DELETE_FAIL	= -7,              //删除文件记录错误
		UFILE_SUCCESS        =  0    
备	 注: 删除的具体位置由File_Lseek()函数决定
*************************************************************************************/
int UFile_Delete(FILE_HANDLE handle, uint size);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.10	关闭文件（UFile_Close）
输入参数：andle：文件句柄
输出参数：无
返    回：UFILE_PARAERROR      = -11，            //参数错
		UFILE_CLOSE_FAIL		= -8,              //关闭文件错误
		UFILE_FAIL			= -1,              //文件操作失败
		UFILE_SUCCESS        =  0              //文件操作成功
备	 注: 无
*************************************************************************************/
int UFile_Close(FILE_HANDLE handle);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.11	删除文件（UFile_Remove）
输入参数：fileName：文件名, 以NULL结束，最长16个字节
		iFileLocation: 存储位置，参见enum FILELOCATION
输出参数：无
返    回：UFILE_NO_EXIST       = -12,             //指定的文件不存在
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_FAIL			= -1,              //文件操作失败
		UFILE_SUCCESS        =  0              //文件操作成功
备	 注: 无
*************************************************************************************/
int UFile_Remove(cchar *filename, int iFileLocation);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.12	重命名文件（UFile_Rename）
输入参数：oldname：旧文件名
		iFileLocation: 存储位置，参见enum FILELOCATION
		newname：新文件名
输出参数：无
返    回：UFILE_NO_EXIST       = -12,             //指定的文件不存在
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_FAIL			= -1,              //文件操作失败
		UFILE_SUCCESS        =  0              //文件操作成功
备	 注: 无
*************************************************************************************/
int UFile_Rename(cchar *oldname, int iFileLocation, cchar *newname);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.13	清空文件（UFile_Clear）
输入参数：FileName：文件名, 以NULL结束，最长16个字节
		iFileLocation: 存储位置，参见enum FILELOCATION
输出参数：无
返    回：UFILE_NO_EXIST       = -12,             //指定的文件不存在
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_FAIL			= -1,              //文件操作失败
		UFILE_SUCCESS        =  0              //文件操作成功
备	 注: 无
*************************************************************************************/
int UFile_Clear(cchar *FileName, int iFileLocation);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.14	取文件系统剩余空间（UFile_GetFreeSpace）
输入参数：drive：驱动器名称("I:"或"F:")
		如果无驱动名称应忽略此参数
输出参数：无
返    回：成功：返回剩余空间单位K
		失败：UFILE_FAIL			= -1,              //文件操作失败
备	 注: 无
*************************************************************************************/
long UFile_GetFreeSpace(cchar *drive);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.15	取文件记录条数（UFile_GetNumberOfRecords）
输入参数：FileName：文件名称
		iFileLocation: 存储位置，参见enum FILELOCATION
		Record_Len：单条记录长度
输出参数：无
返    回：成功：返回记录条数
		失败：UFILE_PARAERROR      = -11，            //参数错
		UFILE_FAIL			= -1,              //文件操作失败
备	 注: 无
*************************************************************************************/
int UFile_GetNumberOfRecords(cchar *FileName, int iFileLocation, int Record_Len);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.16	追加文件记录（UFile_AppendRecord）
输入参数：FileName：文件名, 以NULL结束，最长16个字节
		iFileLocation: 存储位置，参见enum FILELOCATION
		Record：记录数据
		Record_Len：记录数据的长度
输出参数：无
返    回：UFILE_PARAERROR      = -11，            //参数错
		UFILE_FAIL			= -1,              //文件操作失败
		UFILE_SUCCESS        =  0              //文件操作成功
备	 注: 掉电保护
在文件末尾，添加一条定长记录文件。当文件不存在时，自动创建该文件
*************************************************************************************/
int UFile_AppendRecord(cchar *FileName, int iFileLocation, char *Record, int Record_Len);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.17	根据索引号查询记录（UFile_GetRecordByIndex）
输入参数：FileName：文件名称
		iFileLocation: 存储位置，参见enum FILELOCATION
		Record_Len：记录长度
		Record_Index ：记录索引(从0开始)
输出参数：Record：记录数据
返    回：UFILE_NO_EXIST       = -12,             //指定的文件不存在
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_NO_RECORD		= -10,             //记录未找到
		UFILE_READ_FAIL		= -5,              //读错误
		UFILE_OPEN_FAIL  	= -2,              //打开错误
		UFILE_FAIL			= -1,              //文件操作失败
		UFILE_SUCCESS        =  0              //文件操作成功
备	 注: 无
*************************************************************************************/
int UFile_GetRecordByIndex(cchar *FileName, int iFileLocation, void *Record, int Record_Len, int Record_Index);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.18	查询记录（UFile_GetRecord）
输入参数：FileName：文件名称
		iFileLocation: 存储位置，参见enum FILELOCATION
		Record_Len：记录长度
		Condtion：查询条件，参考DBSearCond结构
输出参数：Record：记录数据
返    回：UFILE_NO_EXIST       = -12,             //指定的文件不存在
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_NO_RECORD		= -10,             //记录未找到
		UFILE_READ_FAIL		= -5,              //读错误
		UFILE_OPEN_FAIL  	= -2,              //打开错误
		UFILE_FAIL			= -1,              //文件操作失败
		UFILE_SUCCESS        =  0              //文件操作成功
备	 注: 无
*************************************************************************************/
int UFile_GetRecord(cchar *FileName, int iFileLocation, void *Record, int Record_Len, DBSEARCOND *Condtion);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.19	更新记录（UFile_UpdateRecord）通过条件更新任意一条记录
输入参数：FileName：文件名称
		iFileLocation: 存储位置，参见enum FILELOCATION
		Record：记录数据
		Record_Len：记录长度
		Condtion：查询条件，参考DBSearCond结构
输出参数：Record：记录数据
返    回：UFILE_NO_EXIST       = -12,             //指定的文件不存在
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_NO_RECORD		= -10,             //记录未找到
		UFILE_READ_FAIL		= -5,              //读错误
		UFILE_WRITE_FAIL		= -4,              //写错误
		UFILE_OPEN_FAIL  	= -2,              //打开错误
		UFILE_FAIL			= -1,              //文件操作失败
		UFILE_SUCCESS        =  0              //文件操作成功
备	 注: 掉电保护,Record既是入参也是出参。搜索成功的情况下，Record被搜索结果填充。
*************************************************************************************/
int UFile_UpdateRecord(cchar *FileName, int iFileLocation, void *Record, int Record_Len, DBSEARCOND *Condtion);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.20	根据索引号更新记录（UFile_UpdateRecordByIndex）
输入参数：FileName：文件名称
		iFileLocation: 存储位置，参见enum FILELOCATION
		Record：记录数据
		Record_Len：记录长度
		Index： 记录索引号
输出参数：Record：记录数据
返    回：UFILE_NO_EXIST       = -12,             //指定的文件不存在
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_NO_RECORD		= -10,             //记录未找到
		UFILE_READ_FAIL		= -5,              //读错误
		UFILE_WRITE_FAIL		= -4,              //写错误
		UFILE_OPEN_FAIL  	= -2,              //打开错误
		UFILE_FAIL			= -1,              //文件操作失败
		UFILE_SUCCESS        =  0              //文件操作成功
备	 注: 掉电保护,Record既是入参也是出参。搜索成功的情况下，Record被搜索结果填充。
*************************************************************************************/
int UFile_UpdateRecordByIndex(cchar *FileName, int iFileLocation, void *Record, int Record_Len, uint Index);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.21	删除记录（UFile_DeleteRecord）通过条件删除任意一条记录
输入参数：FileName：文件名称
		iFileLocation: 存储位置，参见enum FILELOCATION
		Record_Len：记录长度
		Condtion：查询条件，参考DBSearCond结构
输出参数：无
返    回：UFILE_NO_EXIST       = -12,             //指定的文件不存在
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_NO_RECORD		= -10,             //记录未找到
		UFILE_DELETE_FAIL	= -7,              //删除文件记录错误
		UFILE_OPEN_FAIL  	= -2,              //打开错误
		UFILE_FAIL			= -1,              //文件操作失败
		UFILE_SUCCESS        =  0              //文件操作成功
备	 注: 掉电保护
*************************************************************************************/
int UFile_DeleteRecord(cchar *FileName, int iFileLocation, int Record_Len, DBSEARCOND *Condtion);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.22	根据索引号删除记录（UFile_DeleteRecordByIndex）
输入参数：FileName：文件名称
		iFileLocation: 存储位置，参见enum FILELOCATION
		Record_Len：记录长度
		Index： 记录索引号
输出参数：无
返    回：UFILE_NO_EXIST       = -12,             //指定的文件不存在
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_NO_RECORD		= -10,             //记录未找到
		UFILE_DELETE_FAIL	= -7,              //删除文件记录错误
		UFILE_OPEN_FAIL  	= -2,              //打开错误
		UFILE_FAIL			= -1,              //文件操作失败
		UFILE_SUCCESS        =  0              //文件操作成功
备	 注: 掉电保护
*************************************************************************************/
int UFile_DeleteRecordByIndex(cchar *FileName, int iFileLocation, int Record_Len, uint Index);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.23	读一行文本（UFile_ReadLine)同时支持 \r \n换行(读出来的数据应不包含换行符)
输入参数：pFile：文件handle
		LineBuffSize：缓冲大小
输出参数：pLineBuff	：读取的文本数据
返    回：成功：数据长度
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_READ_FAIL		= -5,              //读错误
		UFILE_FAIL			= -1,              //文件操作失败
备	 注: 针对文本文件，从当前位置读取一行数据，并跳转到下一行。
*************************************************************************************/
int UFile_ReadLine(FILE_HANDLE pFile, char *pLineBuff,uint LineBuffSize);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.24	读取非定长记录（UFile_ReadTLV）读非定长记录TLV，跟IC卡TVL格式一致
输入参数：FileName: 文件名称
		iFileLocation: 存储位置，参见enum FILELOCATION
		FldID: 标签(Tag)
输出参数：Data: 数据(Value)
		DataLen: 长度(length)
返    回：UFILE_NO_EXIST       = -12,             //指定的文件不存在
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_NO_RECORD		= -10,             //记录未找到
		UFILE_READ_FAIL		= -5,              //读错误
		UFILE_OPEN_FAIL  	= -2,              //打开错误
		UFILE_FAIL			= -1,              //文件操作失败
		UFILE_SUCCESS        =  0              //文件操作成功
备	 注: 读取TLV格式的记录
*************************************************************************************/
int UFile_ReadTLV(char *FileName, int iFileLocation, uint FldID, char *Data, uint *DataLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.25	写非定长数据（UFile_WriteTLV）
输入参数：FileName：文件名称
		iFileLocation: 存储位置，参见enum FILELOCATION
		FldID：标签(Tag)
		Data：数据(Value)
		DataLen：长度(length)
输出参数：无
返    回：UFILE_NO_EXIST       = -12,             //指定的文件不存在
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_WRITE_FAIL		= -4,              //写错误
		UFILE_OPEN_FAIL  	= -2,              //打开错误
		UFILE_FAIL			= -1,              //文件操作失败
		UFILE_SUCCESS        =  0              //文件操作成功
备	 注: 无
*************************************************************************************/
int UFile_WriteTLV(char *FileName, int iFileLocation, uint FldID, char *Data, uint *DataLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.9.26	删除非定长记录（UFile_DeleteTLV）
输入参数：FileName：文件名称
		iFileLocation: 存储位置，参见enum FILELOCATION
		FldID：标签(Tag)
输出参数：无
返    回：UFILE_NO_EXIST       = -12,             //指定的文件不存在
		UFILE_PARAERROR      = -11，            //参数错
		UFILE_NO_RECORD		= -10,             //记录未找到
		UFILE_DELETE_FAIL	= -7,              //删除文件记录错误
		UFILE_OPEN_FAIL  	= -2,              //打开错误
		UFILE_FAIL			= -1,              //文件操作失败
		UFILE_SUCCESS        =  0              //文件操作成功
备	 注: 无
*************************************************************************************/
int UFile_DeleteTLV(char *FileName, int iFileLocation, uint FldID);




int UFile_GetLength(cchar *FileName, int iFileLocation);


#endif /*__LIBAPI_FILE_HEADER__*/
