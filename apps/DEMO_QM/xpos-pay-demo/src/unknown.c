

#if defined(DEV_MF66B) || defined(DEV_MF68) 
int mf_magtek_open(unsigned char *trackbuf, unsigned short len){ return 0; }
int mf_magtek_close(void){ return 0; }
#endif

