/*
 * Client.h
 *
 *  Created on: 01 рту. 2014 у.
 *      Author: maximm
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <winsock2.h>
#include <pthread.h>
#include <string>
#include <boost/shared_ptr.hpp>

class ServerCommunicationManager;

class Client
{
public:
	Client( ServerCommunicationManager *Manager );
	virtual ~Client();

	void Send( const std::string& message );

	sockaddr_in addr;

	bool operator==( const Client &client ) const;

protected:

	friend class ServerCommunicationManager;
	ServerCommunicationManager *manager;
	SOCKET socket;
	pthread_t thread;

};

typedef boost::shared_ptr<Client> ClientPtr;

#endif /* CLIENT_H_ */
