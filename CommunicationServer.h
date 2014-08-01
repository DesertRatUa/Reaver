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

class CommunicationServer: public CommunicationManager
{
public:
	CommunicationServer();
	virtual ~CommunicationServer();

	virtual void Init();
	void Listen( const std::string &addr, const unsigned port );

protected:
	friend class Client;

	typedef std::vector<Client> Clients;
	Clients m_clients;

	static void *ListenSocketThr( void *arg );
	Client* CreateInputConn();

	void CreateHandlerThread( Client *data );
	static void *DataHandlerThr( void *arg );

	Client& StoreClient( Client &client );
	void RemoveClient( const Client& data );
	virtual void CloseAdditionalThreads();

	pthread_mutex_t m_clientsM;
};

#endif /* COMMUNICATIONSERVER_H_ */
