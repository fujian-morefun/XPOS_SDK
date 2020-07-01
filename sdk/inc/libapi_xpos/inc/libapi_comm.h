#pragma once

#include "libapi_pub.h"


typedef struct __st_wifi_ap_list{
	int ecn;
	char ssid[64];//WiFi name
	char utf8ssid[64];
	int rssi;//Signal strength
	char mac[20];
	int channel;
	int freq;
}st_wifi_ap_list;

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Connect Network
Input : title£ºTips for connecting to the network
		  apn£ºgprs apn
		  timeover : Connection timeout
		
Output : Nothing
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT int comm_net_link(char * title, char * apn , int timeover);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Connect Network with user id and password
Input : title£ºTips for connecting to the network
		  apn£ºgprs apn
		  timeover : Connection timeout
		  user:	gprs apn user id
		  pwd: gprs apn user password
		
Output : Nothing
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT int comm_net_link_ex(char * title, char * apn,  int timeover, char *user,char *pwd);



/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Disconnect from the network
Input : Nothing
Output : Nothing
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT int comm_net_unlink();


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:create socket
Input : index(0/1)
Output : Nothing
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT int comm_sock_create(int index);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:connect to the server
Input : index		sock index
		  ip		server ip
		  port		server port
Output : Nothing			
return: 0,     success
		Other, failure		
*************************************************************************************/
LIB_EXPORT int comm_sock_connect(int index, char * ip, int port);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Receive data
Input : index		sock index
		  buff		Receive buffer
		  len		Receiving length
		  timeover	overtime time
Output : Nothing			
return: 0,     success
		Other, failure		
*************************************************************************************/
LIB_EXPORT int comm_sock_recv(int index, unsigned char * buff, int len, unsigned int timeover);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:send data
Input : index		sock index
		  buff		Send buffer
		  len		Send length
Output : Nothing			
return: 0,     success
		Other, failure		
*************************************************************************************/
LIB_EXPORT int comm_sock_send(int index, unsigned char * buff , int size);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Disconnect the server
Input : index		sock index
Output : Nothing			
return: 0,     success
		Other, failure		
*************************************************************************************/
LIB_EXPORT int comm_sock_close(int index);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:ssl initialization
Input : index		sock index
	      cacert	Server certificate
		  clientcert Client certificate
		  clientkey	Client key
		  level		Verification level 0=Not verified 1=Verify server certificate
Output : Nothing			
return: 0,     success
		Other, failure		
*************************************************************************************/
LIB_EXPORT int comm_ssl_init(int index, char * cacert, char * clientcert, char * clientkey,int level);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:ssl connect to the server
Input : index		sock index
	      ip		server ip
		  port		server port

Output : Nothing			
return: 0,     success
		Other, failure		
*************************************************************************************/
LIB_EXPORT int comm_ssl_connect(int index , char * ip , int port);
/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:ssl connect to the server
Input : index		sock index
	      ip		server ip
		  port		server port
		  func      callback
Output : Nothing			
return: 0,     success
		Other, failure		
*************************************************************************************/

LIB_EXPORT int comm_ssl_connect2(int index , char * ip , int port,void *func);
/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:ssl send data
Input : index		sock index
	      data		ssl data
		  size		Data size
Output : Nothing			
return: 0,     success
		Other, failure		
*************************************************************************************/
LIB_EXPORT int comm_ssl_send(int index, char * pdata, int size);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:ssl Receive data
Input : index		sock index
	      data		ssl data
		  size		Data size
Output : Nothing			
return: 0,     success
		Other, failure		
*************************************************************************************/
LIB_EXPORT int comm_ssl_recv(int index, char * pdata, int size);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:ssl Disconnect
Input : index		sock index
Output : Nothing			
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT int comm_ssl_close(int index);




/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Get the router list
Input : Nothing	
Output : ap_list	Router list data,	The ap_list space is allocated by the caller with an array size of 10	
return: 	Number of routers
*************************************************************************************/
LIB_EXPORT int comm_wifi_list_ap(st_wifi_ap_list * ap_list);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Connecting router
Input : ap_list	Router data	
Input : pwd password	
Output : 
return: 0,     success
Other, failure		
*************************************************************************************/
LIB_EXPORT int comm_wifi_link_ap(st_wifi_ap_list * ap_list , char * pwd);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:unlink router
Input : 
Output : 
return: 0,     success
Other, failure		
*************************************************************************************/
LIB_EXPORT int comm_wifi_unlink_ap();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Get connection status
Input : 
Output : 
return: 1,     connection
		0 ,    disconnect
*************************************************************************************/
LIB_EXPORT int comm_wifi_get_link_state();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lxz
Functions:Getting WIFI signal value
Input : 
Output : 
return: 0 Unregistered Internet  1-4 Signal Lattice Number
*************************************************************************************/
LIB_EXPORT int comm_wifi_get_signal();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:get wifi signal
Input : 
Output : 
return: wifi signal
*************************************************************************************/
LIB_EXPORT char * wifi_get_ssid();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:get wifi ap mac address
Input : 
Output : 
return: ap mac address
*************************************************************************************/
LIB_EXPORT char * wifi_get_ap_mac();


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:get wifi rssi
Input : 
Output : 
return: rssi
*************************************************************************************/
LIB_EXPORT int wifi_get_rssi();


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:get wifi channel
Input : 
Output : 
return: channel
*************************************************************************************/
LIB_EXPORT int wifi_get_channel();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:get wifi local mac address
Input : 
Output : 
return: local mac address
*************************************************************************************/
LIB_EXPORT char * wifi_get_local_mac();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:get wifi local ip
Input : 
Output : 
return: wifi signal
*************************************************************************************/
LIB_EXPORT char * wifi_get_local_ip();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:get Module imei
Input : 
Output : 
return: imei
*************************************************************************************/
LIB_EXPORT const char * comm_atc_imei();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:get Module sim card status
Input : 
Output : 
return: sim card status
*************************************************************************************/
LIB_EXPORT int comm_atc_cpin();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:get Module imsi
Input : 
Output : 
return: imsi
*************************************************************************************/
LIB_EXPORT const char * comm_atc_imsi();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:get Module signal
Input : 
Output : 
return: signal
*************************************************************************************/
LIB_EXPORT int comm_atc_signal();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:get net registered cell
Input : 
Output : 
return: cell
*************************************************************************************/
LIB_EXPORT int comm_atc_cell();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:get net registered lac
Input : 
Output : 
return: lac
*************************************************************************************/
LIB_EXPORT int comm_atc_lac();


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:get Module iccid
Input : 
Output : 
return: iccid
*************************************************************************************/
LIB_EXPORT const char * comm_atc_iccid();
