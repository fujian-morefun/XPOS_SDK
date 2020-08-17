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
Functions: Test files exist¡ê¡§UFile_Check¡ê?
Input : FileName¡êoFile Name End with NULL
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
		UFILE_SUCCESS        =  0               //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_Check(cchar *FileName, int iFileLocation);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:File open / create¡ê¡§UFile_OpenCreate¡ê?
Input : FileName¡êoFile Name End with NULL
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
		Flag¡êoOpen the file mode and refer to the FileFlags definition.
		RecSize¡êoFile record size
			RecSize = 0,Create open stream file, text file
			RecSize = 1¡ê?Create a non fixed length record (TLV) file
			8<=RecSize<=4090 Create open fixed length record file
Output : Fh¡êoFile handle
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
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
Functions:2.2.9.6	file read¡ê¡§UFile_Read¡ê?
Input : handle¡êoread File handle
		size¡êoread data size
Output : buffer¡êo readout data
return: File read successfully: the return value is equal to the number of bytes actually read.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
		UFILE_READ_FAIL		= -5,              
		UFILE_FAIL			= -1,              //Fail
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_Read(FILE_HANDLE handle, char *buffer, int size);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: File writing¡ê¡§UFile_Write¡ê?
Input : handle¡êoFile handle to be written
		size¡êodata sizeto be written
		buffer¡êoData to be written
Output : Nothing
return: Success¡êoThe return value equals the number of bytes actually written.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
		UFILE_WRITE_FAIL		= -4,              
		UFILE_FAIL			= -1,              //Fail
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_Write(FILE_HANDLE handle, char *buffer, int size);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:Locating file pointer¡ê¡§UFile_Lseek¡ê?
Input : handle¡êoFile handle
		offset¡êooffset
		origin¡êostart position
Output : Nothing
return: UFILE_PARAERROR      = -11¡ê?            //Parameter Error
		UFILE_SEEK_FAIL	   = -6,              / / location file pointer error


		UFILE_SUCCESS        =  0
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT long UFile_Lseek(FILE_HANDLE handle, long offset, int origin);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.9	delete file record¡ê¡§UFile_Delete¡ê?
Input : handle¡êoFile handle
		size¡êoDeleted File Bytes
Output : Nothing
return: UFILE_PARAERROR      = -11¡ê?            //Parameter Error
		UFILE_DELETE_FAIL	= -7,              delete file record error
		UFILE_SUCCESS        =  0    
Remarks: deletion is determined by the File_Lseek () function.
*************************************************************************************/
LIB_EXPORT int UFile_Delete(FILE_HANDLE handle, uint size);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.10	Close the file¡ê¡§UFile_Close¡ê?
Input : Handle¡êoFile handle
Output : Nothing
return: UFILE_PARAERROR      = -11¡ê?            //Parameter Error
		UFILE_CLOSE_FAIL		= -8,              closing file error
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_Close(FILE_HANDLE handle);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.11	Delete file¡ê¡§UFile_Remove¡ê?
Input : fileName¡êoFile Name End with NULL
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_Remove(cchar *filename, int iFileLocation);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.12	Rename file¡ê¡§UFile_Rename¡ê?
Input : oldname¡êoOld  FileName
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
		newname¡êoNew FileName
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_Rename(cchar *oldname, int iFileLocation, cchar *newname);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.13	Empty File¡ê¡§UFile_Clear¡ê?
Input : FileName¡êoFile Name End with NULL
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_Clear(cchar *FileName, int iFileLocation);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:File system remaining space¡ê¡§UFile_GetFreeSpace¡ê?
Input : drive¡êo0
Output : Nothing
return: Success¡êoReturn to the remaining space unit K
		UFILE_FAIL			= -1,              //Fail
Remarks: 
*************************************************************************************/
LIB_EXPORT long UFile_GetFreeSpace(cchar *drive);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.15	get record number¡ê¡§UFile_GetNumberOfRecords¡ê?
Input : FileName¡êoFile Name 
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
		Record_Len¡êoSingle Record Len
Output : Nothing
return: Success¡êo record number
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
		UFILE_FAIL			= -1,              //Fail
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_GetNumberOfRecords(cchar *FileName, int iFileLocation, int Record_Len);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.9.16	AppendRecord¡ê¡§UFile_AppendRecord¡ê?
Input : FileName¡êoFile Name End with NULL
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
		Record¡êoRecord data
		Record_Len¡êoLength of recorded data
Output : Nothing
return: UFILE_PARAERROR      = -11¡ê?            //Parameter Error
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
Functions: 	Query record by index¡ê¡§UFile_GetRecordByIndex¡ê?
Input : FileName¡êoFile Name 
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
		Record_Len¡êoRecord Len
		Record_Index ¡êoRecord index (starting from 0)
Output : Record¡êoRecord data
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
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
Functions: Query record¡ê¡§UFile_GetRecord¡ê?
Input : FileName¡êoFile Name 
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
		Record_Len¡êoRecord Len
		Condtion¡êoFor reference, refer to DBSearCond structure.
Output : Record¡êoRecord data
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
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
Input : FileName¡êoFile Name 
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
		Record¡êoRecord data
		Record_Len¡êoRecord Len
		Condtion¡êoFor reference, refer to DBSearCond structure.
Output : Record¡êoRecord data
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
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
Functions: Update record according to index number¡ê¡§UFile_UpdateRecordByIndex¡ê?
Input : FileName¡êoFile Name 
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
		Record¡êoRecord data
		Record_Len¡êoRecord Len
		Index¡êo Record Index
Output : Record¡êoRecord data
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
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
Author:yangjy
Functions:2.2.9.21	Delete record (UFile_DeleteRecord) by deleting any record by condition.
Input : FileName¡êoFile Name 
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
		Record_Len¡êoRecord Len
		Condtion¡êoFor reference, refer to DBSearCond structure.
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
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
Functions:2.2.9.22	Delete record based on index number¡ê¡§UFile_DeleteRecordByIndex¡ê?
Input : FileName¡êoFile Name 
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
		Record_Len¡êoRecord Len
		Index¡êo Record Index
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
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
Input : pFile¡êoFile Handle
		LineBuffSize¡êoLine Buff Size
Output : pLineBuff	¡êoText data read
return: Success¡êoData length
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
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
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
		FldID: (Tag)
Output : Data: (Value)
		DataLen: (length)
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
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
Input : FileName¡êoFile Name 
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
		FldID¡êo(Tag)
		Data¡êo(Value)
		DataLen¡êo(length)
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
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
Functions:2.2.9.26	Delete non fixed length record¡ê¡§UFile_DeleteTLV¡ê?
Input : FileName¡êoFile Name 
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
		FldID¡êo(Tag)
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
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
Functions:2.2.9.26	Delete non fixed length record¡ê¡§UFile_DeleteTLV¡ê?
Input : FileName¡êoFile Name 
		iFileLocation: Storage location¡ê?Reference enum FILELOCATION
		FldID¡êo(Tag)
Output : Nothing
return: UFILE_NO_EXIST       = -12,             //The specified file does not exist.
		UFILE_PARAERROR      = -11¡ê?            //Parameter Error
		UFILE_NO_RECORD		= -10,             //Record not found
		UFILE_DELETE_FAIL	= -7,              delete file record error
		UFILE_OPEN_FAIL  	= -2,              //Open a mistake
		UFILE_FAIL			= -1,              //Fail
		UFILE_SUCCESS        =  0              //Successful file operation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int UFile_GetLength(cchar *FileName, int iFileLocation);

LIB_EXPORT void UFile_clean(void);

#endif /*__LIBAPI_FILE_HEADER__*/
