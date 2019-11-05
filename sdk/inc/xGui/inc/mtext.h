/*! \file mtext.h
	\brief Multi-line Text Functio
*	\author lx
*	\date 2014/02/08
*/
#ifndef ___MTEXT_H___
#define ___MTEXT_H___ 

#include "xgui_pub.h"

#define TEXT_AS_ARROW_NONE	(0 << 0)
#define TEXT_AS_ARROW_UP	(1 << 0)
#define TEXT_AS_ARROW_DOWN	(1 << 1)
#define TEXT_AS_ARROW_BOTH	(TEXT_AS_ARROW_UP | TEXT_AS_ARROW_DOWN)

#define MAX_TEXT_LEN	(1024)

#define TEXT_RET_OK			1
#define TEXT_RET_QUIT		2
#define TEXT_RET_TIMEOVER	3
#define TEXT_RET_PRINT		4
#define TEXT_RET_PAINT		5
#define TEXT_RET_USER_KEY	6

#define TEXT_RET_HANDOFF	-2

typedef struct __st_textnode{
	int nPageIndex;
	int nFirstChIndex;
	int nLastChIndex;
	struct __st_textnode *pNext;
	struct __st_textnode *pPrev;
}_TEXT_ST;

typedef struct __st_xmtext {
	char * m_szText;
	char * m_title;
	void * pfun;
	int m_bCreated;
	int m_bEnable;
	int m_bVisible;
	int m_bInited;
	RECT m_rect;
	int m_nStyle ;


	int m_nLineHeight;
	int m_nCurPos;
	int m_nCount;
	int m_nTimer;
	int m_nArrow;
	int m_bArrowState;
	unsigned int m_nTimeOver;
	unsigned int m_nTick;
	_TEXT_ST * m_pTextHead,* m_pTextTail, * m_pCurPage;
	unsigned int m_nTErrorCode;
	int linePerPage;
	unsigned char * keylist;
	int presskey;
	int showtime;
	char * leftstr;
	char * rightstr;
	char fristshow;
}XMTEXT;

	
/**
* @brief Create multiline text
* @param szText Text content
* @param nStyle Text Style
* @param pRect Display area
* @param nParam timeout
* @return Text structure
*/
LIB_EXPORT XMTEXT * xgui_mtext_Create(char *szText,int nStyle ,RECT *pRect,int nParam );
LIB_EXPORT XMTEXT * xgui_mtext_CreateEx(char * szText, int nStyle,  RECT * pRect, int nParam , char * title , void * pfun);

/**
* @brief Display multiline text
* @param pmt Text structure
* @return 
*/
LIB_EXPORT void xgui_mtext_Show(XMTEXT* pmt);
/**
* @brief Text Display Processi
* @param pmt Text structure
* @return Display processing re
*/
LIB_EXPORT int xgui_mtext_domodal(XMTEXT * pmt);

/**
* @brief Release text
* @param pmt Text structure
* @return 
*/
LIB_EXPORT void xgui_mtext_delete(XMTEXT * pmt);

/**
* @brief Setting text
* @param pmt Text structure
* @param szText
* @return 0 success
*/
LIB_EXPORT int xgui_mtext_SetText(XMTEXT* pmt,const char *szText);
/**
* @brief Read the current text 
* @param pmt Text structure
* @return 
*/
LIB_EXPORT int xgui_mtext_GetTextLength(XMTEXT* pmt);
/**
* @brief Read the current text  
* @param pmt Text structure
* @param szText Text content
* @return 0 success
*/
LIB_EXPORT int xgui_mtext_GetText(XMTEXT* pmt,char * szText);
/**
* @brief Text Buffer Pointer 
* @param pmt Text structure
* @return Text pointer
*/
LIB_EXPORT char * xgui_mtext_GetTextPtr(XMTEXT* pmt);

LIB_EXPORT int xgui_mtext_Key(XMTEXT* pmt, int nKey);


#endif

