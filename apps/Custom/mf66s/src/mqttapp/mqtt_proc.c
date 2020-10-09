#include <string.h>
#include "ucosii\ucos_ii.h"
#include "pub/osl/inc/osl_system.h"
#include "mqtt_proc.h"
#include "mqtt_embed/MQTTClient/src/MQTTClient.h"
#include "pub\inc\taskdef.h"
#include "pub/tracedef.h"
#include "usermessage.h"
#include "pub\common\misc\inc\mfmalloc.h"
static MQTTClient c;
static Network n;
static e_status s_status;
static int s_paused;

static unsigned char sendbuf[512];
static unsigned char readbuf[512];
static char cid[32];
static unsigned char s_statustext[64];
static MQTTClient *s_client=0;

static int m_payload_lock = -1;
#define MQTT_LOCK	 if(m_payload_lock == -1){m_payload_lock =(int)OSSemCreate((unsigned short)1);}  {unsigned char nErr; OSSemPend((OS_EVENT *)m_payload_lock,TIMEOUT_INFINITE, &nErr); }
#define	MQTT_UNLOCK	 OSSemPost((OS_EVENT *)m_payload_lock);

#define MAXPAYLOADSIZE   1024
static unsigned char s_payload[MAXPAYLOADSIZE];
static unsigned int s_payloadlen;


static int mqtt_getpayload(char *payload, int size)
{
	int payloadlen;
	MQTT_LOCK
	memcpy( payload, s_payload ,s_payloadlen );
	payload[s_payloadlen]=0;
	payloadlen = s_payloadlen;
	MQTT_UNLOCK

	return payloadlen;
}

static void mqtt_comm_messageArrived(MessageData* md)
{
	MQTTMessage* m = md->message;

	if ( m->payloadlen>0)
	{
		if ( onmessageArrived_thread( m->payload, m->payloadlen ) == 0)
		{
			MQTT_LOCK
			s_payloadlen= m->payloadlen;
			memcpy( s_payload, (char*)m->payload ,s_payloadlen );
			s_payload[s_payloadlen] = 0;
			MQTT_UNLOCK
			xgui_PostMessage( XM_MESSAGEARRIVED , 0,0);
		}
	}
}
int mqtt_proc_Pause()
{
	s_paused = 1;
	while ( s_status == status_Recving )
	{
		osl_Sleep(100);
	}

}

int mqtt_proc_Resume()
{
	s_paused = 0;
}

int mqtt_proc_default_msg(st_gui_message * pmsg)
{
	if (pmsg->message_id == XM_MESSAGEARRIVED){
		unsigned char *payload = MALLOC(MAXPAYLOADSIZE);
		unsigned int payloadlen;
		payloadlen = mqtt_getpayload( payload , MAXPAYLOADSIZE);
		if ( payloadlen )
		{
			onmessageArrived(payload,payloadlen);
		}
		FREE(payload);
		return 1;
	}	
	return 0;
}


static int mqtt_subscribe_yield( MQTTClient *c ) 
{
	int rc;
	int subsqos = 2;
	char topic[64];
	
	MQTTSubackData suback;

	sprintf(topic,"testNode/handshake/pub" , cid);
	//sprintf(topic,"iot/v1/pXgzbzmjON5RQQv3/%s/user/task" , cid);

	APP_TRACE("Subscribe...\r\n");
	sprintf(s_statustext,"Subscribe..");
	APP_TRACE("topic %s\r\n", topic);
	rc = MQTTSubscribeWithResults(c,topic, subsqos, mqtt_comm_messageArrived, &suback);
	APP_TRACE("MQTTSubscribeWithResults:%d\r\n", rc);
	if ( rc == 0)
	{
		sprintf(s_statustext,"Recving..");
		s_status = status_Recving;
		while( MQTTIsConnected(c) )
		{					
			rc = MQTTYield(c, 300);
			if ( rc != SUCCESS)
			{
				break;
			}
			Sys_Sleep(300);
			if ( s_paused == 1)
			{
				break;
			}
		}
	}
	else{
		sprintf(s_statustext,"Subscribe failed,%d",rc);
	}
	return rc;
}

//WebSocket
#if 0
#define OVER_WS		
#define HOST		"tailor.cloudmqtt.com"
#define PORT		33152
#define USERNAME	"sygmkdxc"
#define PASSWORD	"bdr-qqlflnoy"

#endif

//AWS
#if 1
#define CLIENT_CRT	
#define HOST		"a1a356lyfwt72z-ats.iot.us-west-2.amazonaws.com"
#define PORT		8883
#define USERNAME	"iot-devices"
#define PASSWORD	"IoT-deVIceIntern@L"
#endif

//AWS
#if 0
//#define CLIENT_CRT
#define OVER_WS		
#define HOST		"a3ri26a4bhtu9s-ats.iot.ap-south-1.amazonaws.com"
#define PORT		443
#define USERNAME	"iot-devices"
#define PASSWORD	"IoT-deVIceIntern@L"
#endif


#if 0	
#define HOST		"iot-dev.paytm.in"
#define PORT		1883
#define USERNAME	"iot-devices"
#define PASSWORD	"IoT-deVIceIntern@L"

#endif
static int mqtt_comm_run() 
{
	int rc = 0;
	char ip[64]={0};
	int port= 0;
	
	strcpy(s_statustext,"Connecting..");
	s_status = status_Connecting;

	APP_TRACE("Connecting\r\n");
	strcpy(ip,HOST);
	port = PORT;

	memset(&n,0x00,sizeof(n));
	NetworkInit(&n);
#ifndef CLIENT_CRT
	n.tls = 1;
	rc = NetworkConnect(&n, ip, port);
#else
	//Note: use a lot of memory
	//rc = NetworkConnect2(&n, ip, port,"xxxx\\ca.der","xxxx\\cli.crt","xxxx\\pri.key");
	rc = NetworkConnect2(&n, ip, port,"xxxx\\ca.der","xxxx\\cli.crt","xxxx\\pri.key");
#endif

#ifdef OVER_WS
	if ( rc == 0)
	{
		rc = NetworkOverWebSocket( &n ,ip, port );
	}
#endif
	APP_TRACE("NetworkConnect:%d\r\n", rc);
	if ( rc == 0 )
	{
		MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
		MQTTClientInit(&c, &n, 20000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));
		//data.willFlag = 0;
		//data.MQTTVersion = 4;
		osl_getTerminalID(cid,sizeof(cid));
		data.clientID.cstring = cid;
		data.keepAliveInterval = 0;
		data.cleansession = 1;


		data.username.cstring = USERNAME;
		data.password.cstring = PASSWORD;

		//data.willFlag         = 1;
		//data.will.topicName.cstring = "/unRegister";
		//data.will.message.cstring   = cid;
		//data.will.retained          = 0;
		//data.will.qos              =  0;

		rc = MQTTConnect(&c, &data);
		s_client = &c;
		APP_TRACE("rc from connect:%d\r\n", rc);
		if ( rc == 0 )
		{
			mqtt_subscribe_yield(&c);

			MQTTDisconnect(&c);
		}
		else{
			sprintf(s_statustext,"Connect,%d",rc);
		}
		NetworkDisconnect(&n);
	}	
	else{
		sprintf(s_statustext,"NET Anomaly,%d",rc);
	}

	s_client = 0;
	return 0;
}

int mqtt_proc_publish(const char *payload)
{
	if ( s_client != 0)
	{
 		int ret =0;
		char topic[64];


 		MQTTMessage msg;
 		memset(&msg,0x00,sizeof(msg)); 
 		msg.payloadlen = strlen(payload);
 		msg.payload = (void*)payload;

 		//sprintf(topic,"iot/v1/pXgzbzmjON5RQQv3/%s/user" , cid);
		//sprintf(topic,"/%s/server" , cid);
		//sprintf(topic,"testNode/handshake/sub");
		sprintf(topic,"testNode/handshake/pub");

		ret = MQTTPublish( s_client,topic,&msg);

 		APP_TRACE("publish (%s):\r\n%s\r\n", topic, payload);

 		return ret;
	}

	return -1;
}


const char * mqtt_status_text()
{
	return s_statustext;
}

e_status mqtt_status()
{
	return s_status;
}



static void mqtt_comm_task(void * p) 
{
	while(1)
	{		
		if ( s_paused == 1)
		{
			if ( s_status != status_Paused )
			{
				s_status = status_Paused;
				sprintf(s_statustext,"Paused..");
			}
			osl_Sleep(100);
			continue;
		}
		//Wait one second and try again
		osl_Sleep(1000);


		//Waiting network..
		if ( net_func_link_state() == 0 ){
			sprintf(s_statustext,"Wait network..");
			s_status = status_WaitNetwork;
			osl_Sleep(1000);
			continue;
		}

		if ( net_func_link("", "Paytm.com", 1, 10000) == 0)
		{	//mqtt run
			mqtt_comm_run();
		}
		else{
			osl_Sleep(1000);
		}


	}
}





#pragma data_alignment=8
#define _MQTT_TASK_SIZE		2048
#define _MQTT_TASK_PRIO		(_APP_TASK_MIN_PRIO + 4)
static unsigned int pTaskStk[_MQTT_TASK_SIZE];

int mqtt_proc_init()
{
	s_paused = 0;
	memset(s_payload,0x00, sizeof(s_payload));
	s_payloadlen = 0;
	s_status = status_Connecting;

	memset(cid, 0x00, sizeof(cid));
	sprintf(s_statustext,"Loading..");
	//xgui_default_msg_func_add((void*)mqtt_proc_default_msg);

	osl_task_create((void*)mqtt_comm_task,_MQTT_TASK_PRIO,pTaskStk ,_MQTT_TASK_SIZE );
	return 0;
}

