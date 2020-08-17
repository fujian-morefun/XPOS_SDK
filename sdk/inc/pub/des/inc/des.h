#ifndef _CDES_H_CAESAR__DEF_
#define _CDES_H_CAESAR__DEF_

#ifdef __cplusplus
extern "C" {
#endif

#include "pub\pub.h"

//! Crypto
enum	
{
	ENCRYPT	=	0,	///<encryption
	DECRYPT			///<Decrypt
};

//! Model of DES algorithm
enum
{
	ECB		=	0,	///<ECB
	CBC				///<CBC
};

#define false 0
#define true 1
//#define FALSE 0
//#define TRUE 1

typedef char DES_BOOLEAN;
typedef DES_BOOLEAN (*PSubKey)[16][48];

//!PadFilling pattern
enum
{
	PAD_ISO_1 =	0,	///<ISO_1Fill in: Data length is less than 8 bits of multiple, complemented by 0x00, if 8 bits of multiple, supplemented by 8 0x00
	PAD_ISO_2,		///<ISO_2Fill: The data length is less than 8 bits, which is supplemented by 0x80, 0x00. If it is 8 bits, fill 0x80, 0x00... 0x00.
	PAD_PKCS_7		///<PKCS7Fill in: Data length divided by 8 residuals is n, multiplied by (8-n) complement of 8
};

/**
* @brief Fill in the data before encryption according to the protocol
* @param nType PAD type
* @param In Data String Pointer
* @param datalen Length of data
* @param Out Fill in output string pointer
* @param padlen Output buffer length, filled length
* @return Successful Filling
*/
LIB_EXPORT DES_BOOLEAN RunPad(int nType,const char * In,unsigned datalen,char * Out,unsigned * padlen);

LIB_EXPORT DES_BOOLEAN RunDes_l(DES_BOOLEAN bType,DES_BOOLEAN bMode,char* In,char* Out,unsigned datalen,const char* Key,const unsigned char keylen);
/**
* @brief Encryption and decryption of text by executing DES algorithm
* @param DES_BOOLEAN bType Type: Encrypt ENCRYPT, decrypt DECRYPT
* @param DES_BOOLEAN bMode bMode mode£ºECB,CBC
* @param In	To-be-encrypted string pointer
* @param Out Output string pointer
* @param datalen The length of the string to be encrypted, and the buffer size of Out should be greater or equal to datalen
* @param Key Key (8-bit, 16-bit, 24-bit) supports 3 keys
* @param keylen Key length, more than 24 bits will be automatically reduced
* @return Is encryption successful?
*/
LIB_EXPORT DES_BOOLEAN RunDes(DES_BOOLEAN bType,DES_BOOLEAN bMode,char* In,char* Out,unsigned datalen,const char* Key,const unsigned char keylen);

	//Compute and populate subkeys into SubKey data
static void SetSubKey(PSubKey pSubKey, const char Key[8]);
	
	//DES unit operation
static void DES(char Out[8], char In[8], const PSubKey pSubKey, DES_BOOLEAN Type);




#ifdef __cplusplus
}
#endif

#endif

// DES algorithm corresponding description:

/* How to Realize DES Algorithms



Original: Matthew Fischer



		  DES (Data Encryption Standard) algorithm, formally licensed by the U.S. government in 1977, is a method of encrypting 64-bit data with 56-bit keys. DES algorithm is applied to many occasions which need secure encryption. For example, UNIX's cryptographic algorithm is based on DES algorithm. Below is a linguistic description of how to implement the DES algorithm. If you want the source code, you can download it from Http//Assassin.yeah.net, which you can write to me if you have any questions (Assassin@ynmail.com).



		  1-1. Transform key



		  Gets a 64-bit key, each 8th bit being the parity bit.



		  1-2. Transform key.



		  1-2-1, discard parity bits in 64-bit keys, and transform the keys according to the following table (PC-1) to get 56-bit keys. In the transformation, parity bits are discarded.



		  Permuted Choice 1 (PC-1)



		  57 49 41 33 25 17 9



		  1 58 50 42 34 26 18



		  10 2 59 51 43 35 27



		  19 11 3 60 52 44 36



		  63 55 47 39 31 23 15



		  7 62 54 46 38 30 22



		  146 61 53 45 37 29



		  21 13 5 28 20 12 4



		  1-2-2. The transformed key is divided into two parts. The first 28 bits are called C [0], and the last 28 bits are called D [0].



		  1-2-3, generate 16 sub-keys, initial I = 1.



		  1-2-3-1. Move C[I], D[I] to one or two bits at the same time, and decide the number of bits to move left according to the value of I. See table below.



I: 1 2 3 4 5 6 7 8 9 11 12 13 14 15 16



   Left shift number: 1 12 2 2 2 2 2 2 2 2 2 2 1



   1-2-3-2, C[I]D[I] as a whole is transformed according to the following table (PC-2), and a 48-bit K[I]is obtained.





   Permuted Choice 2 (PC-2)



   14 17 11 24 15



   3 28 15 6 21 10



   23 19 12 4 26 8



   16 7 27 20 13 2



   41 52 31 37 47 55



   30 40 51 45 33 48



   44 49 39 56 34 53



   46 42 50 36 29 32



   1-2-3-3 and 1-2-3-1 are executed circularly until K[16] is calculated.




   2. Processing 64-bit data



   2-1. Get 64-bit data. If the data length is less than 64 bits, it should be expanded to 64 bits (e.g. zero-filling)



   2-2. Transform 64-bit data into the following table (IP)



   Initial Permutation (IP)



   58 50 42 34 26 18 102



   60 52 44 36 28 20 12 4



   62 54 46 38 30 22 14 6



   64 56 48 40 32 24 16 8



   57 49 41 33 25 17 9 1



   59 51 43 35 27 19 11 3



   61 53 45 37 29 21 13 5



   63 55 47 39 31 23 15 7



   2-3. The transformed data is divided into two parts. The first 32 bits are called L [0], and the last 32 bits are called R [0].



   2-4. Encrypt data with 16 sub-keys, initial I = 1.



   2-4-1. Expand 32-bit R [I-1] to 48-bit E [I-1] by table (E) below



   Expansion (E)



   32 1 2 3 4 5



   4 5 6 7 8 9



   8 9 10 11 12 13



   12 13 14 15 16 17



   16 17 18 19 20 21



   20 21 22 23 24 25



   24 25 26 27 28 29



   28 29 30 31 32 1



   2-4-2, XOR E [I-1] and K [I], namely E [I-1] XOR K [I]



2-4-3. The XOR results are divided into 8 6-bit long parts, the first to the sixth is called B [1], the seventh to the twelfth is called B [2], and so on, the forty-third to the forty-eighth is called B [8].



2-4-4. Transform all B[J] according to S table, initial J=1. All values in the S table are treated as 4-bit lengths.



2-4-4-1. Combine the first and sixth bits of B[J] into a two-bit length variable M, M as the line number in S[J].



2-4-4-2. Combine the 2nd to 5th bits of B [J] as a 4-bit length variable N, and N as a column number in S [J].



2-4-4-3. Replace B [J] with S [J] [M] [N].



Substitution Box 1 (S [1])



14 4 13 1 2 15 11 8 3 10 6 12 5 9 07



0 157 4 14 2 13 1 10 6 12 11 9 5 3 8



41 148 13 6 2 11 15 12 9 7 3 10 50



15 12 8 2 4 9 1 7 5 11 3 14 10 0613



S[2]



15 1 8 14 6 11 3 4 9 7 2 13 12 0 5 10



3 13 4 7 15 2 8 14 12 0 1 10 6 9 11 5



0 147 11 10 4 13 1 5 8 12 6 9 3 2 15



13 8 10 1 3 15 4 2 11 6 7 12 0 5 14 9



S[3]



10 09 14 6 3 15 5 1 13 12 7 11 4 2 8



13 7 0 9 3 4 6 10 2 8 5 14 12 11 15 1



13 6 4 9 8 15 3 0 11 1 2 12 5 10 14 7



1 10 13 0 6 9 8 7 4 15 14 3 11 5 2 12



S[4]



7 13 14 3 0 6 9 10 1 2 8 5 11 12 4 15



13 8 11 5 6 15 0 3 4 7 2 12 1 10 14 9



10 6 9 0 12 11 7 13 15 1 3 14 5 2 8 4



3 150 6 10 1 13 8 9 4 5 11 12 7 2 14



S[5]



2 12 4 1 7 10 11 6 8 5 3 15 13 0 14 9



14 11 2 12 4 7 13 1 5 0 15 10 3 9 8 6



42 1 11 10 13 7 8 15 9 12 5 6 3 0 14



11 8 12 7 1 14 2 13 6 15 0 9 10 4 5 3



S[6]



121 10 15 9 2 6 8 0 13 3 4 7 5 11



10 154 2 7 12 9 5 6 1 13 14 0 11 3 8



9 14 15 5 2 8 12 3 7 0 4 10 1 13 11 6



43 2 129 5 15 10 11 14 1 7 6 0813



S[7]



4 11 2 14 15 0 8 13 3 12 9 7 5 10 6 1



13 0 11 7 4 9 1 10 14 3 5 12 2 15 8 6



14 11 13 12 3 7 14 10 15 6 8 0 5 9 2



6 11 13 8 1 4 10 7 9 5 0 15 14 2 3 12



S[8]



13 2 8 4 6 15 11 1 10 9 3 14 5 0 12 7



1 15 13 8 10 3 7 4 12 5 6 11 0 14 9 2



7 11 4 1 9 12 14 2 0 6 10 13 15 3 5 8



21 14 7 4 10 8 13 15 12 9 0 3 5 6 11



2-4-4-4 and 2-4-4-1 are executed circularly until B [8] is replaced.



2-4-4-5. Combine B [1] to B [8] and transform it into P in the following table.



Permutation P



16 7 20 21



29 12 28 17



1 15 23 26



5 18 31 10



28 24 14



32 27 3 9



19 13 306



22 11 4 25



The results of 2-4-6, XOR P and L [I-1] are placed in R [I], that is, R [I] = P XOR L [I-1].



2-4-7, L[I]=R[I-1]



2-4-8, starting from 2-4-1 loop execution, until K [16] is transformed.



2-4-5, R[16]L[16] (Note: R is the 32-bit starting point) after combination transformation, the final result is obtained by following table (IP-1) transformation.



Final Permutation (IP**-1)

Final Permutation (IP**-1)

40 8 48 16 56 24 64 32

39 7 47 15 55 23 63 31

38 6 46 14 54 22 62 30

37 5 45 13 53 21 61 29

36 4 44 12 52 20 60 28

35 3 43 11 51 19 59 27

34 2 42 10 50 18 58 26

33 1 41 9 49 17 57 25

*/

