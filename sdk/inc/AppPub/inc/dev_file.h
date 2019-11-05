#ifndef _DEV_FILE_H
#define _DEV_FILE_H

#include "pub/pub.h"

#define FILE_NOCREATEINDEX 0x00	/*Do not create index files*/
#define FILE_CREATEINDEX 0x01		/*Create index files*/
#define MAX_FILENAME_LEN 256		/*Maximum length of filename*/

typedef struct tagRecFile
{
	unsigned int unMaxOneRecLen;	/*Maximum single record length*/  
	unsigned int unIndex1Start;	/*Starting position of index field 1*/
	unsigned int unIndex1Len;		/*Length of index field 1*/
	unsigned int unIndex2Start; 	/*Starting position of index field 2*/
	unsigned int unIndex2Len;		/*Length of Index Field 2*/
	char cIsIndex;				/*Do you need to create index files, 0x00 is not established, 0x01 is established?*/
	char szFileName[MAX_FILENAME_LEN+1];		/*Record file name, valid record file name length is */
	char s[2];
}STRECFILE;

/******************************************************************************
*	Function name：Ex_File_CreatFile 
*	Function Description: Creating Files
*	Function description：
*	Entry parameters:：const STRECFILE *pstRecFile 文件头信息
*	Export parameters：
*	 Return value  ：
*			SUCC Success
*			 FAIL Failure
*******************************************************************************/
LIB_EXPORT extern int Ex_File_CreatFile(const STRECFILE *pstRecFile);
/******************************************************************************
*	Function name：Ex_File_DelFile
*	Function Description: Delete Files
*	Function description:
*	Entry parameters：const char *pszFileName Name of hydrological document
*	Export parameters：
*	Return value  ：
*		SUCC Success
*	    FAIL Failure
*******************************************************************************/
LIB_EXPORT extern int Ex_File_DelFile (const char *pszFileName);
/******************************************************************************
*	Function name：Ex_File_GetRecSum
*	Function Description: Open the file by file name, get the total number of file records
*	Function description：
*	Entry parameters：
*		const char *pszFileName Name of hydrological document
*	Export parameters：
*		int *pnRecSum A pointer to the number of records
*	Return value  ：
*		SUCC Success
*	    FAIL Failure
*******************************************************************************/
LIB_EXPORT extern int Ex_File_GetRecSum (const char *pszFileName, int *pnRecSum);
/******************************************************************************
* Function name: Ex_File_AddRecByName
* Function introduction: Increase pipeline records, for creating records is to specify the need to create index files will increase index records accordingly.
* Function description:
* Entry parameters:
*			const char * pszFileName: Name of hydrological document
*           const char*pszRec: Input Pipeline Record
* Export parameters: none
* Return value:
*		SUCC Success
*	    FAIL Failure
*******************************************************************************/
LIB_EXPORT extern int Ex_File_AddRecByName (const char *pszFileName, const char *pszRec);
/******************************************************************************
* Function name: Ex_File_UpdateRecByName

* Function Introduction: Updating Records

* Function Description: Modify the record and rewrite the specified record according to the specified record location.
*						At the same time, for creating records, it specifies the need to create indexed files.
*						Index records are updated accordingly.
* Entry parameters:
*			 const char * pszFileName: record file name
*			 const int nRecNo:The record number to be modified by
*			 char * psRec Record Pointer
* Export parameters:
* Return value:
*		SUCC Success
*		FAIL Failure
*******************************************************************************/
LIB_EXPORT extern int Ex_File_UpdateRecByName (const char *pszFileName, const int nRecNo, const char *psRec);
/******************************************************************************
* Function name: Ex_File_ReadRecByName
* Function introduction: read single record by record number
* Function description:
* Entry parameters:
*			const char * pszFileName: Record file name
*			Const int nRecNo: Record number to be modified
*			Char * psRec: Record Pointer
* Export parameters:
* Return value:
*			SUCC Success
*			FAIL Failure
*******************************************************************************/
LIB_EXPORT extern int Ex_File_ReadRecByName(const char *pszFileName, const int nRecNo, char *psRec);
/******************************************************************************
* Function name: DelRecByFileName
* Function Description: Delete Records by Index
* Function Description: Find and delete records from the specified record number according to index field 1/idex field 2.
*						If you specify index field 1/index field 2 at the same time, you need to satisfy both.
*						The output of the condition record is NULL when not specified. If the index condition is satisfied, the output of the condition record is NULL.
*						In the case of duplication, the first record is output.
* Entry parameters:
*			 const char * pszFileName: Record file name
*			 Const char * psIndexStr1: Index field 1
*			Const char * psIndexStr2: Index field 2
* Export parameters:
*			no
* Return value:
*******************************************************************************/
LIB_EXPORT extern int Ex_File_DelRecByName(const char *pszFileName, const char *psIndexStr1,const char *psIndexStr2);
/******************************************************************************
* Function name: Ex_File_ReadRecByHandle
* Function Introduction: Read the pipelining record by record number.
* Function description:
* Entry parameters:
*			const int nFileHandle: Open File Handle
*			 const int nRecNo: The record number to be found
* Export parameters:
*			Char * psRec: Record Pointer
* Return value:
*			SUCC Success
*			FAIL Failure
*******************************************************************************/
LIB_EXPORT extern int Ex_File_ReadRecByHandle (const int nFileHandle, const int nRecNo, char *psRec , const char *pszName);
/******************************************************************************
* Function name: Ex_File_UpdateRecByHandle
* Function Introduction: Updating Records
* Function Description: Modify the record and rewrite the specified record according to the specified record location.
*						At the same time, for creating records, it specifies the need to create indexed files.
*						Index records are updated accordingly.

* Entry parameters:
*			 int nFileHandle: Record File Handle
*			 const int nRecNo: Record number to be modified
*			Char * psRec: Record Pointer
* Export parameters:
* Return value:
*			SUCC Success
*			FAIL Failure

*******************************************************************************/
LIB_EXPORT extern int Ex_File_UpdateRecByHandle (int nFileHandle, const int nRecNo, const char *psRec);
/******************************************************************************
* Function name: Ex_File_FindRec
* Function Description: Find Records by Index
* Function Description: Find records from the specified record number according to index field 1/index field 2.
*						If you specify index field 1/index field 2 at the same time, you need to satisfy both.
*						The output of the condition record is NULL when not specified. If the index condition is satisfied, the output of the condition record is NULL.
*						In the case of duplication, the first record is output.
* Entry parameters:
*			Const char * pszFileName :record file name
*			Const char * psIndexStr1: index field 1
*		   Const char * psIndexStr2 :index field 2
*		   Start record number specified by const int nBeginRecNo
* Export parameters:
*			Char * psRec Record Pointer
*			int * pnRecNo eligible record number
* Return value:
*			SUCC Success
*			FAIL Failure
*******************************************************************************/
LIB_EXPORT extern int Ex_File_FindRec(const char *pszFileName, const char *psIndexStr1,
			   const char *psIndexStr2,const int nBeginRecNo, char *psRec, int *pnRecNo);
/******************************************************************************
 * Function name: Ex_File_GetParam:
 * Function Description: Read parameter information from parameter files
 * Entry parameters: nOff parameter offset address
					nLen parameter data length
 * Export parameter: pszOutData output string pointer
 * Return value
 ******************************************************************************/
LIB_EXPORT int Ex_File_GetParam(char *pszFileName,char *pszOutData, int nOff, int nLen);

//Read parameter information from the lead parameter file
LIB_EXPORT int Ex_FileHead_GetParam(char *pszFileName,char *pszOutData, int nOff, int nLen);
/******************************************************************************
 *  Function name:	Ex_File_SaveParam: 
 *	Function Description: Save parameters to parameter files
 *	Entry parameter:	pszFileName file name
 					nOff parameter offset address
 					nLen parameter data length
 					pszInData String pointer input by pszInData
 *	Export parameters::     
 * 	return  :		SUCC
 					FAIL
 ******************************************************************************/
LIB_EXPORT extern int Ex_File_SaveParam(char *pszFileName,char *pszInData, int nOff, int nLen);
#endif