/*
 * CommunicationServer.h
 *
 *  Created on: 23 лип. 2014
 *      Author: maximm
 */

#ifndef COMMUNICATIONSERVER_H_
#define COMMUNICATIONSERVER_H_

#include "CommunicationManager.h"
#include "Client.h"

class ServerCommunicationManager: public CommunicationManager
{
public:
	ServerCommunicationManager( MessageProcessor &processor, bool &isRun );
	virtual ~ServerCommunicationManager();

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
