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
#include <boost/shared_ptr.hpp>

class CommunicationServer: public CommunicationManager
{
public:
	CommunicationServer();
	virtual ~CommunicationServer();

	virtual void Init();
	void Listen( const std::string &addr, const unsigned port );

protected:
	friend class Client;

	typedef boost::shared_ptr<Client> ClientPtr;
	typedef std::vector<ClientPtr> Clients;
	Clients m_clients;


	static void *ListenSocketThr( void *arg );
	ClientPtr CreateInputConn();

	void CreateHandlerThread( ClientPtr &client );
	static void *DataHandlerThr( void *arg );

	void StoreClient( ClientPtr& client );
	void RemoveClient( const ClientPtr& data );
	virtual void CloseAdditionalThreads();

	pthread_mutex_t m_clientsM;
};

#endif /* COMMUNICATIONSERVER_H_ */
