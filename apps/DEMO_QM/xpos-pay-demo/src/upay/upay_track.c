#include "upay_track.h"

int upay_track_get_expdate(struct magtek_track_info * track_info , char *expdate)
{
	int i;

	for(i=0; i< strlen((char *) track_info->b_chars.chars); i++){

		if (track_info->b_chars.chars[i] == '=' || track_info->b_chars.chars[i] == 'd'|| track_info->b_chars.chars[i] == 'D')	{
			memcpy(expdate, & track_info->b_chars.chars[i+1], 4);
			return 0;
		}
	}
	return -1;
}

int upay_track_get_service_code24(struct magtek_track_info * track_info ,char *code24 )
{
	int i;

	for(i = 0; i < strlen((char *)track_info->b_chars.chars); i++){
		if (track_info->b_chars.chars[i] == '=' || track_info->b_chars.chars[i] == 'd'|| track_info->b_chars.chars[i] == 'D')		{
			memcpy(code24, & track_info->b_chars.chars[i+5], 3);
			return 0;
		}
	}
	return -1;
}


int upay_track_get_pan(struct magtek_track_info * track_info , char *pan )
{
	int i;

	if (0 != track_info->b_chars.chars[0]){
		for (i = 0; i < 37; i++)	{
			if (track_info->b_chars.chars[i] == '=' || track_info->b_chars.chars[i] == 'd'|| track_info->b_chars.chars[i] == 'D')	{
				break;
			}
		}

		if (i == 37){
			return -1;
		}

		if (i > 19){
			memcpy(pan, track_info->b_chars.chars, 19);
		}
		else{
			memcpy(pan, track_info->b_chars.chars, i);
		}
		return 0;
	}
	else if (0 != track_info->c_chars.chars[0]){
		for (i = 0; i < 104; i++){
			if (track_info->c_chars.chars[i] == '=' || track_info->c_chars.chars[i] == 'd'|| track_info->c_chars.chars[i] == 'D')	{
				break;
			}
		}

		if (i == 104)	{
			return -1;
		}

		if (i > 19+2){
			memcpy(pan, track_info->c_chars.chars + 2, 19);
		}
		else{
			memcpy(pan, track_info->c_chars.chars + 2, i);
		}
		return 0;
	}
	return -1;
}


int upay_track_is_valid(struct magtek_track_info * track_info)
{
	int i;
	int nCardLenth = 0;

	if (strlen((char *)track_info->b_chars.chars)>37
		||strlen((char *)track_info->b_chars.chars)<24){
		return -1;
	}
	if (strlen((char *)track_info->c_chars.chars)>104){
		return -1;
	}

	if (0 != track_info->b_chars.chars[0]){
		for(i=0; i<strlen((char *)track_info->b_chars.chars); i++){
			if ( (track_info->b_chars.chars[i] < '0' || track_info->b_chars.chars[i] > '9') && track_info->b_chars.chars[i] != '=' 
				&& track_info->b_chars.chars[i] != 'd' && track_info->b_chars.chars[i] != 'D'){
				return -1;
			}
			if (track_info->b_chars.chars[i] == '=' ||track_info->b_chars.chars[i] == 'd'||track_info->b_chars.chars[i] == 'D')	{
				nCardLenth = i;
				break;
			}
		}
		if (nCardLenth<13 || nCardLenth>19)	{
			return -1;
		}
	}
	else if (0 != track_info->c_chars.chars[0]){
		for(i=2; i<strlen((char *)track_info->c_chars.chars); i++){
			if (track_info->c_chars.chars[i] == '=' ||track_info->c_chars.chars[i] == 'd'||track_info->c_chars.chars[i] == 'D')
			{
				nCardLenth = i - 2;
				break;
			}
		}	
		if (nCardLenth<13 || nCardLenth>19){
			return -1;
		}
	}
	return 0;
}

int upay_track_get_chname(struct magtek_track_info * track_info , char *chname )
{
	int i,j;
	int nMaxNameLen = 26;
	int nLen;

	for(i=0; i<strlen((char *)track_info->a_chars.chars); i++){
		if (track_info->a_chars.chars[i] == '^' ){
			i++;
			break;
		}

	}

	for(j=i; j<strlen((char *)track_info->a_chars.chars);j++){
		if (track_info->a_chars.chars[j] == '^' ){
			break;
		}
	}

	nLen = j-i;
	if((nLen <= nMaxNameLen) && (nLen > 1)){
		memcpy(chname, &track_info->a_chars.chars[i], nLen);
		return 0;
	}	
	return -1;
}

int upay_track_is_icc(struct magtek_track_info * track_info)
{
	int i;
	int nKeyIn;
	
	for(i = 0; i < 38; i++){
		if ('=' == track_info->b_chars.chars[i]){
			break;
		}
	}

	if (38 == i){
		return -1;
	}

	if (('2' == track_info->b_chars.chars[i+5]) || ('6' == track_info->b_chars.chars[i+5])){
		return 0;
	}
	return -1;
}


