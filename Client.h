/*
 * Client.h
 *
 *  Created on: 01 ���. 2014 �.
 *      Author: maximm
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <winsock2.h>
#include <pthread.h>

class CommunicationServer;

class Client
{
public:
	Client( CommunicationServer *Manager );
	virtual ~Client();

	SOCKET socket;
	pthread_t thread;
	sockaddr_in addr;
	CommunicationServer *manager;

	bool operator==( const Client &client ) const;

protected:


};

#endif /* CLIENT_H_ */
