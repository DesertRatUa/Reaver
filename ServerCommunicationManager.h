/*
 * CommunicationServer.h
 *
 *  Created on: 23 лип. 2014
 *      Author: maximm
 */

#ifndef COMMUNICATIONSERVER_H_
#define COMMUNICATIONSERVER_H_

#include "include.h"
#include "CommunicationManager.h"
#include "Client.h"
#include <stdexcept>
#include <mutex>

class ServerCommunicationManager: public CommunicationManager
{
public:
	ServerCommunicationManager( ServerModule &server, MessageProcessor &processor, bool &isRun );
	virtual ~ServerCommunicationManager();

	virtual void Init();
	void Listen( const std::string &addr, const unsigned port ) throw( std::runtime_error );

	Client& GetClient( const std::string &addr );

protected:
	friend class Client;

	static void ListenSocketThr( ServerCommunicationManager &parent );
	ClientPtr CreateInputConn();

	void CreateHandlerThread( ClientPtr &client );
	static void DataHandlerThr( ClientPtr client );

	ClientPtr* StoreClient( ClientPtr& client );
	void RemoveClient( const ClientPtr& data );
	virtual void CloseAdditionalThreads();

	typedef std::vector<ClientPtr> Clients;
	Clients m_clients;
	std::mutex m_clientsM;
	ServerModule& m_server;
};

#endif /* COMMUNICATIONSERVER_H_ */
