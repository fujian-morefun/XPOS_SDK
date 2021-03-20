#ifndef __LIBAPI_FILE_HEADER__
#define __LIBAPI_FILE_HEADER__


#include "libapi_pub.h"
#include "def.h"

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.3	Get File module version (UFile_GetModuleVer)
Input : Nothing
Output : pszVer    module version 
return: > 0 Successfully returns module version number length
		USYS_FAIL     = -1,    
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_GetModuleVer(char *pszVer);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: Test files exist��UFile_Check��
Input : FileName��File Name End with NULL
		iFileLocation: Storage location��Reference enum FILELOCATION
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_SUCCESS        =  0               //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_Check(cchar *FileName, int iFileLocation);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:File open / create��UFile_OpenCreate��
Input : FileName��File Name End with NULL
		iFileLocation: Storage location��Reference enum FILELOCATION
		Flag��Open the file mode and refer to the FileFlags definition.
		RecSize��File record size
			RecSize = 0,Create open stream file, text file
			RecSize = 1��Create a non fixed length record (TLV) file
			8<=RecSize<=4090 Create open fixed length record file
Output : Fh��File handle
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_OPEN_FAIL  	= -2,              //Open a mistake
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0               //Successful file operation
Remarks: For newly created file RecSize, it works.
		The RecSize parameter should be ignored for opening the created file
*************************************************************************************/
LIB_EXPORT int UFile_OpenCreate(cchar *FileName, int iFileLocation, int Flag, FILE_HANDLE *fh, int RecSize);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.6	file read��UFile_Read��
Input : handle��read File handle
		size��read data size
Output : buffer�� readout data
return: File read successfully: the return value is equal to the number of bytes actually read.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_READ_FAIL		= -5,              
		UFILE_FAIL			= -1,              //Fail
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_Read(FILE_HANDLE handle, char *buffer, int size);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: File writing��UFile_Write��
Input : handle��File handle to be written
		size��data sizeto be written
		buffer��Data to be written
Output : Nothing
return: Success��The return value equals the number of bytes actually written.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_WRITE_FAIL		= -4,              
		UFILE_FAIL			= -1,              //Fail
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_Write(FILE_HANDLE handle, char *buffer, int size);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:Locating file pointer��UFile_Lseek��
Input : handle��File handle
		offset��offset
		origin��start position
Output : Nothing
return: UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_SEEK_FAIL	   = -6,              / / location file pointer error


		UFILE_SUCCESS        =  0
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT long UFile_Lseek(FILE_HANDLE handle, long offset, int origin);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.9	delete file record��UFile_Delete��
Input : handle��File handle
		size��Deleted File Bytes
Output : Nothing
return: UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_DELETE_FAIL	= -7,              delete file record error
		UFILE_SUCCESS        =  0    
Remarks: deletion is determined by the File_Lseek () function.
*************************************************************************************/
LIB_EXPORT int UFile_Delete(FILE_HANDLE handle, uint size);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.10	Close the file��UFile_Close��
Input : Handle��File handle
Output : Nothing
return: UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_CLOSE_FAIL		= -8,              closing file error
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_Close(FILE_HANDLE handle);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.11	Delete file��UFile_Remove��
Input : fileName��File Name End with NULL
		iFileLocation: Storage location��Reference enum FILELOCATION
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_Remove(cchar *filename, int iFileLocation);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.12	Rename file��UFile_Rename��
Input : oldname��Old  FileName
		iFileLocation: Storage location��Reference enum FILELOCATION
		newname��New FileName
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_Rename(cchar *oldname, int iFileLocation, cchar *newname);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.13	Empty File��UFile_Clear��
Input : FileName��File Name End with NULL
		iFileLocation: Storage location��Reference enum FILELOCATION
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_Clear(cchar *FileName, int iFileLocation);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:File system remaining space��UFile_GetFreeSpace��
Input : drive��0
Output : Nothing
return: Success��Return to the remaining space unit K
		UFILE_FAIL			= -1,              //Fail
Remarks: 
*************************************************************************************/
LIB_EXPORT long UFile_GetFreeSpace(cchar *drive);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.15	get record number��UFile_GetNumberOfRecords��
Input : FileName��File Name 
		iFileLocation: Storage location��Reference enum FILELOCATION
		Record_Len��Single Record Len
Output : Nothing
return: Success�� record number
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_FAIL			= -1,              //Fail
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_GetNumberOfRecords(cchar *FileName, int iFileLocation, int Record_Len);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.16	AppendRecord��UFile_AppendRecord��
Input : FileName��File Name End with NULL
		iFileLocation: Storage location��Reference enum FILELOCATION
		Record��Record data
		Record_Len��Length of recorded data
Output : Nothing
return: UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Power off protection
		At the end of the file, add a fixed length record file. 
		When the file does not exist, the file is created automatically
*************************************************************************************/
LIB_EXPORT int UFile_AppendRecord(cchar *FileName, int iFileLocation, char *Record, int Record_Len);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: 	Query record by index��UFile_GetRecordByIndex��
Input : FileName��File Name 
		iFileLocation: Storage location��Reference enum FILELOCATION
		Record_Len��Record Len
		Record_Index ��Record index (starting from 0)
Output : Record��Record data
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_NO_RECORD		= -10,             //Record not found
		UFILE_READ_FAIL		= -5,              
		UFILE_OPEN_FAIL  	= -2,              //Open a mistake
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_GetRecordByIndex(cchar *FileName, int iFileLocation, void *Record, int Record_Len, int Record_Index);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: Query record��UFile_GetRecord��
Input : FileName��File Name 
		iFileLocation: Storage location��Reference enum FILELOCATION
		Record_Len��Record Len
		Condtion��For reference, refer to DBSearCond structure.
Output : Record��Record data
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_NO_RECORD		= -10,             //Record not found
		UFILE_READ_FAIL		= -5,              
		UFILE_OPEN_FAIL  	= -2,              //Open a mistake
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_GetRecord(cchar *FileName, int iFileLocation, void *Record, int Record_Len, DBSEARCOND *Condtion);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: Update record (UFile_UpdateRecord) to update any record by condition.
Input : FileName��File Name 
		iFileLocation: Storage location��Reference enum FILELOCATION
		Record��Record data
		Record_Len��Record Len
		Condtion��For reference, refer to DBSearCond structure.
Output : Record��Record data
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_NO_RECORD		= -10,             //Record not found
		UFILE_READ_FAIL		= -5,              
		UFILE_WRITE_FAIL		= -4,              
		UFILE_OPEN_FAIL  	= -2,              //Open a mistake
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Power off protection,
		Record is both a reference and a reference. 
		In search of Success, Record is filled with search results
*************************************************************************************/
LIB_EXPORT int UFile_UpdateRecord(cchar *FileName, int iFileLocation, void *Record, int Record_Len, DBSEARCOND *Condtion);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: Update record according to index number��UFile_UpdateRecordByIndex��
Input : FileName��File Name 
		iFileLocation: Storage location��Reference enum FILELOCATION
		Record��Record data
		Record_Len��Record Len
		Index�� Record Index
Output : Record��Record data
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_NO_RECORD		= -10,             //Record not found
		UFILE_READ_FAIL		= -5,              
		UFILE_WRITE_FAIL		= -4,              
		UFILE_OPEN_FAIL  	= -2,              //Open a mistake
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Power off protection,
		Record is both a reference and a reference. 
		In search of Success, Record is filled with search results
*************************************************************************************/
LIB_EXPORT int UFile_UpdateRecordByIndex(cchar *FileName, int iFileLocation, void *Record, int Record_Len, uint Index);
/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:George
Functions: Write data Block By file name��UFile_UpdateRecordByIndex��
Input : file_name��File Name 
		write_start: the offset start to write
		write_buff��the buffer to write
		write_size��the size to write
return: actual size wrote
*************************************************************************************/
LIB_EXPORT int UFile_WriteBlockByName(char * file_name,int write_start, char * write_buff,int write_size);
/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.21	Delete record (UFile_DeleteRecord) by deleting any record by condition.
Input : FileName��File Name 
		iFileLocation: Storage location��Reference enum FILELOCATION
		Record_Len��Record Len
		Condtion��For reference, refer to DBSearCond structure.
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_NO_RECORD		= -10,             //Record not found
		UFILE_DELETE_FAIL	= -7,              delete file record error
		UFILE_OPEN_FAIL  	= -2,              //Open a mistake
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Power off protection
*************************************************************************************/
LIB_EXPORT int UFile_DeleteRecord(cchar *FileName, int iFileLocation, int Record_Len, DBSEARCOND *Condtion);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.22	Delete record based on index number��UFile_DeleteRecordByIndex��
Input : FileName��File Name 
		iFileLocation: Storage location��Reference enum FILELOCATION
		Record_Len��Record Len
		Index�� Record Index
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_NO_RECORD		= -10,             //Record not found
		UFILE_DELETE_FAIL	= -7,              delete file record error
		UFILE_OPEN_FAIL  	= -2,              //Open a mistake
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Power off protection
*************************************************************************************/
LIB_EXPORT int UFile_DeleteRecordByIndex(cchar *FileName, int iFileLocation, int Record_Len, uint Index);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:	Read a line of text (UFile_ReadLine) and support \r \n wrap
Input : pFile��File Handle
		LineBuffSize��Line Buff Size
Output : pLineBuff	��Text data read
return: Success��Data length
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_READ_FAIL		= -5,              
		UFILE_FAIL			= -1,              //Fail
Remarks: For text files, read one row of data from the current location and jump to the next line.
*************************************************************************************/
LIB_EXPORT int UFile_ReadLine(FILE_HANDLE pFile, char *pLineBuff,uint LineBuffSize);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: Read the non fixed length record (UFile_ReadTLV) 
			to read the non fixed length record TLV, which is consistent with the IC card TVL format.
Input : FileName: File Name 
		iFileLocation: Storage location��Reference enum FILELOCATION
		FldID: (Tag)
Output : Data: (Value)
		DataLen: (length)
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_NO_RECORD		= -10,             //Record not found
		UFILE_READ_FAIL		= -5,              
		UFILE_OPEN_FAIL  	= -2,              //Open a mistake
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Read the record in TLV format
*************************************************************************************/
LIB_EXPORT int UFile_ReadTLV(char *FileName, int iFileLocation, uint FldID, char *Data, uint *DataLen);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:Writing non fixed length data (UFile_WriteTLV)
Input : FileName��File Name 
		iFileLocation: Storage location��Reference enum FILELOCATION
		FldID��(Tag)
		Data��(Value)
		DataLen��(length)
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_WRITE_FAIL		= -4,              
		UFILE_OPEN_FAIL  	= -2,              //Open a mistake
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_WriteTLV(char *FileName, int iFileLocation, uint FldID, char *Data, uint DataLen);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.26	Delete non fixed length record��UFile_DeleteTLV��
Input : FileName��File Name 
		iFileLocation: Storage location��Reference enum FILELOCATION
		FldID��(Tag)
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_NO_RECORD		= -10,             //Record not found
		UFILE_DELETE_FAIL	= -7,              delete file record error
		UFILE_OPEN_FAIL  	= -2,              //Open a mistake
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_DeleteTLV(char *FileName, int iFileLocation, uint FldID);



/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.26	get length by file name��UFile_GetLength��
Input : FileName��File Name 
		iFileLocation: Storage location��Reference enum FILELOCATION
		FldID��(Tag)
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11��            //Parameter Error
		UFILE_NO_RECORD		= -10,             //Record not found
		UFILE_DELETE_FAIL	= -7,              delete file record error
		UFILE_OPEN_FAIL  	= -2,              //Open a mistake
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_GetLength(cchar *FileName, int iFileLocation);

LIB_EXPORT void UFile_Path_clean(char*path);
LIB_EXPORT void UFile_clean(void);

#endif /*__LIBAPI_FILE_HEADER__*/
