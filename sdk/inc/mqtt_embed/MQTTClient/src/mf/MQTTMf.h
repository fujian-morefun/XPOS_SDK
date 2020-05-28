/*******************************************************************************
 * Copyright (c) 2014 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Allan Stockdill-Mander - initial API and implementation and/or initial documentation
 *******************************************************************************/

#pragma once
#include "pub/pub.h"


/*
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <stdlib.h>
#include <string.h>
#include <signal.h>
*/


typedef struct MqttTimer
{
	unsigned int timeval;
	unsigned int tickval;
} MqttTimer;

void TimerInit(MqttTimer*);
char TimerIsExpired(MqttTimer*);
void TimerCountdownMS(MqttTimer*, unsigned int);
void TimerCountdown(MqttTimer*, unsigned int);
int TimerLeftMS(MqttTimer*);

typedef struct Network
{
	int my_socket;
	int tls;
	int tickrecv;
	int (*mqttread) (struct Network*, unsigned char*, int, int);
	int (*mqttwrite) (struct Network*, unsigned char*, int, int);
} Network;

LIB_EXPORT int mf_read(Network*, unsigned char*, int, int);
LIB_EXPORT int mf_write(Network*, unsigned char*, int, int);

LIB_EXPORT void NetworkInit(Network*);
LIB_EXPORT int NetworkConnect(Network*, char*, int);
LIB_EXPORT int NetworkConnect2(Network* n, char* addr, int port,char * cacert, char * clientcert, char * clientkey);

LIB_EXPORT void NetworkDisconnect(Network*);


