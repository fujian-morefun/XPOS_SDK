#ifndef ___ICON_H___
#define ___ICON_H___

#include "xgui_pub.h"
#include "2ddraw.h"

//Pic style
#define PIC_NORMAL			(1 << 0)
#define	PIC_WITH_FRAME		(1 << 1)
#define PIC_TRANSPARENT		(1 << 2)
#define PIC_DEFAULT			PIC_NORMAL


typedef struct _st_xicon {
	char * m_szText;
	
	int m_bCreated;
	int m_bEnable;
	int m_bVisible;
	int m_bInited;
	RECT m_rect;
	int m_nStyle ;

//	PUTRESOPTS m_nDrawMode;
	char *m_toolStr;
	GUIRES m_Res[20];
	int m_nResCount;
	struct _guires_list *m_pResList_head;
	struct _guires_list *m_pResList_tail;
	struct _guires_list *m_pResList_cur;
	unsigned int m_nTimer;
	unsigned int m_nTErrorCode;
	int m_bXor;
	int m_nCurPaint;
}XICON;


LIB_EXPORT XICON * xgui_icon_Create( char *szName ,int nStyle ,RECT *pRect,int nParam );
LIB_EXPORT void xgui_icon_delete(XICON * pi);
LIB_EXPORT void xgui_icon_Show(XICON * pi);
LIB_EXPORT int xgui_icon_AddImage(XICON * pi, GUIRES * pImage);
LIB_EXPORT void xgui_icon_SetDrawMode(XICON * pi, int bXor);
LIB_EXPORT void xgui_icon_SetToolTitle(XICON * pi, const char *pTitle);
LIB_EXPORT void xgui_icon_Paint(XICON * pi);
LIB_EXPORT int xgui_icon_Enable(XICON * pi, int nDelay);
LIB_EXPORT int xgui_icon_Disable(XICON * pi);
LIB_EXPORT int xgui_icon_LoadResource(XICON * pi, GUIRES * pGuiRes, int x , int y  );
LIB_EXPORT int xgui_icon_OutResource(XICON * pi);


#endif
