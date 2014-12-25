/*
 * Client.h
 *
 *  Created on: 01 ���. 2014 �.
 *      Author: maximm
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include "include.h"
#include "Thread.h"
#if defined WIN32 || defined WIN64
   #include <winsock2.h>
#else
   #include <sys/socket.h>
   #include <sys/un.h>
#endif

class Client
{
public:
	Client();
	virtual ~Client();

	void Send( const std::string& message ) const;
	void SendRequest( const Message& message ) const;
	void SendRespond( const Message& message ) const;
	void Disconnect();
	void Join();
	bool isDisconnected();
	std::string GetAddr() const;


	sockaddr_in addr;

	bool operator==( const Client &client ) const;

protected:

	bool m_disconnected;
	friend class ServerCommunicationManager;
	SOCKET socket;
	ThreadPtr thread;
	mutable std::mutex m_mut;
};

typedef std::shared_ptr<Client> ClientPtr;

#endif /* CLIENT_H_ */
