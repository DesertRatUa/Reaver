/*
 * CommunicationServer.h
 *
 *  Created on: 23 ���. 2014
 *      Author: maximm
 */

#ifndef COMMUNICATIONSERVER_H_
#define COMMUNICATIONSERVER_H_

#include "CommunicationManager.h"
#include "Client.h"

class CommunicationServer: public CommunicationManager
{
public:
	CommunicationServer( MessageProcessor &processor );
	virtual ~CommunicationServer();

	virtual void Init();
	void Listen( const std::string &addr, const unsigned port );

	Client& GetClient( const std::string &addr );

protected:
	friend class Client;

	typedef std::vector<ClientPtr> Clients;
	Clients m_clients;

	static void *ListenSocketThr( void *arg );
	ClientPtr CreateInputConn();

	void CreateHandlerThread( ClientPtr &client );
	static void *DataHandlerThr( void *arg );

	ClientPtr* StoreClient( ClientPtr& client );
	void RemoveClient( const ClientPtr& data );
	virtual void CloseAdditionalThreads();

	pthread_mutex_t m_clientsM;
};

#endif /* COMMUNICATIONSERVER_H_ */
