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
#include "ClientsMap.h"

class ServerCommunicationManager: public CommunicationManager
{
public:
	ServerCommunicationManager( ServerModule &server, MessageProcessor &processor, bool &isRun );
	virtual ~ServerCommunicationManager();

	virtual void Init();
	void Listen( const std::string &addr, const unsigned port ) throw( std::runtime_error );

	Client& GetClient( const std::string &addr );

protected:
	static void ListenSocketThread( ServerCommunicationManager &parent );
	static void DataHandlerThread( ClientPtr client, ServerCommunicationManager &parent );

	void ListenSocket();
	ClientPtr CreateInputConn();
	virtual void CloseAdditionalThreads();

	ServerModule& m_server;
	ClientsMap m_clients;

	void ClientDisconnect();
	void RemoveDisconnected();
	bool m_haveDisconnected;
	std::mutex m_discon;
};

#endif /* COMMUNICATIONSERVER_H_ */
