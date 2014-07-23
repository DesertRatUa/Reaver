/*
 * CommunicationServer.h
 *
 *  Created on: 23 лип. 2014
 *      Author: maximm
 */

#ifndef COMMUNICATIONSERVER_H_
#define COMMUNICATIONSERVER_H_

#include "CommunicationManager.h"

class CommunicationServer: public CommunicationManager
{
public:
	CommunicationServer();
	virtual ~CommunicationServer();

	void Listen( const std::string &addr, const unsigned port );

protected:
	struct SocketData
	{
		SocketData( CommunicationServer *Manager );
		CommunicationServer *manager;
		SOCKET socket;
		pthread_t *thread;
		sockaddr_in addr;
	};

	static void *ListenSocketThr( void *arg );
	SocketData* CreateInputConn();

	void CreateHandlerThread( SocketData *data );
	static void *DataHandlerThr( void *arg );

	pthread_t& AddThread();
	void RemoveThread( const pthread_t *thread );
};

#endif /* COMMUNICATIONSERVER_H_ */
