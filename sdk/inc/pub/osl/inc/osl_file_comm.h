#ifndef _FILE_COMM_H_
#define _FILE_COMM_H_

#include "pub\pub.h"

#ifdef __cplusplus
extern "C"{
#endif


/**
* @brief create folder
* @param dir_name Folder Name
* @return 1 success
*/
LIB_EXPORT int Dir_Create(char * dir_name);

/**
* @brief remove folders
* @param dir_name Folder Name
* @return 1 success
*/
LIB_EXPORT int Delete_Create(char * dir_name);

/**
* @brief create a file
* @param file_name File name
* @return 1 success
*/
LIB_EXPORT int File_Create(char * file_name);
/**
* @brief Delete files
* @param file_name File name
* @return 
*/
LIB_EXPORT int File_Delete(char * file_name);
/**
* @brief Read a piece of data
* @param hfile File handle
* @param read_start Beginning position
* @param read_buff Buffer
* @param read_size Read Length
* @return Read Length
*/
LIB_EXPORT int File_ReadBlock( int hfile, int read_start, char * read_buff, int read_size);
/**
* @brief Read a piece of data
* @param file_name file name
* @param read_start  Beginning position
* @param read_buff Buffer
* @param read_size Read Length
* @return Read Length
*/
LIB_EXPORT int File_ReadBlockByName(char * file_name,int read_start,char * read_buff,int read_size);
/**
* @brief Write a piece of data
* @param hfile File handle
* @param write_start Beginning position
* @param write_buff Buffer
* @param write_size write length
* @return write length
*/
LIB_EXPORT int File_WriteBlock(int hfile,int write_start, char * write_buff,int write_size);
/**
* @brief Write a piece of data
* @param file_name file name
* @param write_start  Beginning position
* @param write_buff Buffer
* @param write_size  write length
* @return write length
*/
LIB_EXPORT int File_WriteBlockByName(char * file_name,int write_start, char * write_buff,int write_size);
/**
* @brief Add a piece of data
* @param hfile File handle
* @param write_buff Buffer
* @param write_size write length
* @return write length
*/
LIB_EXPORT int File_AppendBlock(int hfile,char * write_buff,int write_size);
/**
* @brief  Add a piece of data
* @param file_name file name
* @param write_buff Buffer
* @param write_size  write length
* @return write length
*/
LIB_EXPORT int File_AppendBlockByName(char * file_name,char * write_buff,int write_size);
/**
* @brief Does the file exist?
* @param file_name file name
* @return 1 existence
*/
LIB_EXPORT int File_Exist(char *file_name);
/**
* @brief Get file length
* @param hfile File handle
* @return length
*/
LIB_EXPORT int File_GetLength(int hfile);
/**
* @brief Fill in files
* @param hfile file handle
* @param file_length fill length
* @param fill_char Filled characters
* @return 1 success
*/
LIB_EXPORT int File_SetLength(int hfile, unsigned int file_length, char fill_char);
/**
* @brief write file 
* @param file_name File name
* @param write_buff buffer
* @param write_size length
* @return 1 success
*/
LIB_EXPORT int File_Write(char * file_name,char * write_buff,int write_size);
/**
* @brief read file 
* @param file_name  file name
* @param read_buff buffer
* @param read_size length
* @return 1 success
*/
LIB_EXPORT int File_Read(char * file_name,char * read_buff,int read_size);
/**
* @brief Add a piece of data
* @param file_name file name 
* @param write_buff buffer
* @param write_size length
* @return 1 success
*/
LIB_EXPORT int File_Append(char * file_name,char * write_buff,int write_size);
/**
* @brief Get file length
* @param file_name file name
* @return length
*/
LIB_EXPORT int File_GetLengthByName(char * file_name);
/**
* @brief Get the disk free space
* @return Residual space
*/
LIB_EXPORT int File_GetDataFreeSpace();
/**
* @brief Get the filename
* @param pPath Route
* @return  File Name Pointer
*/
LIB_EXPORT char * File_GetFileName(char * pPath);
/**
* @brief Get the entire file data
* @param FileName file name
* @param pDst buffer
* @return read length
*/
LIB_EXPORT int File_GetData(const char * FileName, void * pDst);
/**
* @brief Read file size
* @param FilePath file name
* @return 
*/
LIB_EXPORT int File_GetFileLength(const char * FilePath);
/**
* @brief Output file content
* @param name file name
* @param flag 0-16mechanism 1-Character mode
* @return 
*/
LIB_EXPORT void File_Trace(char *name , int flag);

/**
* @brief Output file content
* @param pszSrcFn		[IN]	Source file name
* @param pDestFn		[IN]	Target file name
* @return 0 fail  1 succcess
*/
LIB_EXPORT  int File_Copy(const char* pszSrcFn, const char* pDestFn);

#ifdef __cplusplus
}
#endif	

#endif
