#pragma once
#include "pub/pub.h"

#define RET_SIGN_OK  1
#define RET_SIGN_CANCEL  0
#define RET_SIGN_EXIST  2
#define RET_SIGN_TIMEOUT  3


 typedef struct _procs{
	 //Interface Drawing Watermarking
	 int (*page_paint)(const char *m_watermark);  
	 int (*page_getbackcount)();  
	 //Is Cancellation Permissible
	 int (*page_usecancel)(); 

	 //Cancel or not prompt
	 int (*page_usecancelask)();  
	 
	 //Cancellation of Watermark Acquisition
	 int (*page_getwatermark)( char *outwatermark);


	 //Track Minimum Points
	 int (*page_getwritepointcount)();  

	 //Whether to use the cashier confirmation page or not
	 int (*page_usesigntype)(); 

	 //Does the picture use 320*130 resolution?
	 int (*page_use320_130)(); 

	 //Minimum number of strokes in trajectory
	 int (*page_getpointupcount)();  

	 int (*page_buffwidth)();
	 int (*page_buffheight)();
	 
 }ap_sign_procs;

 //Setting Processing Function
LIB_EXPORT void ap_setprocs( ap_sign_procs *procs );

//Have you signed or not?
LIB_EXPORT int ap_sign_exist( const char *xlh );

//Signature Processing
LIB_EXPORT int ap_sign_proc( const char *xlh,const char * date,const char * ckh );

//Signature Processing
LIB_EXPORT int ap_sign_proc2( const char *xlh,const char * date,const char * ckh , int timeout );


//Get the print string
LIB_EXPORT extern const char * ap_sign_print(const char *xlh );

//JBIG Coding Interface
LIB_EXPORT int ap_sign_encode( const char *xlh,char **jbigencode );

//JBIG Result Release
LIB_EXPORT int ap_sign_encode_free( char *jbigencode );


//Clean up signature data
LIB_EXPORT extern int ap_sign_clean();

LIB_EXPORT extern void ap_sign_test();

LIB_EXPORT int ap_sign_savetofile(char * data, const char *xlh);
