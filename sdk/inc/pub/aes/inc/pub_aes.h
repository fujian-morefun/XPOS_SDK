/**
 * \file aes.h
 *
 * \brief AES block cipher
 *
 *  Copyright (C) 2006-2014, Brainspark B.V.
 *
 *  This file is part of PolarSSL (http://www.polarssl.org)
 *  Lead Maintainer: Paul Bakker <polarssl_maintainer at polarssl.org>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef PUB_AES_H
#define PUB_AES_H

/* padlock.c and aesni.c rely on these values! */
#define AES_ENCRYPT     1
#define AES_DECRYPT     0

#define POLARSSL_ERR_AES_INVALID_KEY_LENGTH                -0x0020  /**< Invalid key length. */
#define POLARSSL_ERR_AES_INVALID_INPUT_LENGTH              -0x0022  /**< Invalid data input length. */


#ifdef __cplusplus
extern "C" {
#endif

#include "pub\pub.h"

	/**
	* @brief Setting up background processing functions using TMS threads
	* @param int mode ¡êoAES_ENCRYPT¡ê?AES_DECRYPT
	* @param In	To-be-encrypted string pointer
	* @param Out Output string pointer
	* @param datalen The length of the string to be encrypted must be a multiple of 16 and the size of the buffer of Out should be greater or equal to datalen
	* @param KeyKey (16 bits, 24 bits, 32 bits) supports 3 keys
	* @param Key length, more than 24 bits will be automatically reduced
	* @return Whether Encryption Success 0 Encryption Success < 0 Computing Failure
	*/
LIB_EXPORT int pub_aes_crypt_ecb(char*sin,unsigned int datalen, const char*skey,const unsigned char keylen, int mode,char*sout);


#ifdef __cplusplus
}
#endif

#else

#endif  

