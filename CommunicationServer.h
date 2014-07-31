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

	virtual void Init();
	void Listen( const std::string &addr, const unsigned port );

	struct SocketData
	{
		SocketData( CommunicationServer *Manager );
		CommunicationServer *manager;
		SOCKET socket;
		pthread_t thread;
		sockaddr_in addr;

		bool operator==( const SocketData &data ) const;
	};

protected:
	typedef std::vector<SocketData> Clients;
	Clients m_clients;

	static void *ListenSocketThr( void *arg );
	SocketData* CreateInputConn();

	void CreateHandlerThread( SocketData *data );
	static void *DataHandlerThr( void *arg );

	SocketData& AddClient();
	void RemoveClient( const SocketData& data );
	virtual void CloseAdditionalThreads();

	pthread_mutex_t m_clientsM;
};

#endif /* COMMUNICATIONSERVER_H_ */
