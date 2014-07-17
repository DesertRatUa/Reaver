/*
 * CommunicationManager.h
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#ifndef COMMUNICATIONMANAGER_H_
#define COMMUNICATIONMANAGER_H_

#include <string>
#include <vector>
#ifdef WIN32
   #include <winsock2.h>
#else
   #include <sys/socket.h>
   #include <sys/un.h>
#endif
#include <pthread.h>

class CommunicationManager
{
public:
	CommunicationManager();
	virtual ~CommunicationManager();

	void Init();
	void Connect( const std::string &addr, const unsigned port );
	void Listen( const std::string &addr, const unsigned port );
	void Close();

protected:
	struct SocketData
	{
		SocketData( CommunicationManager *Manager, pthread_t &Thread );
		CommunicationManager *manager;
		SOCKET socket;
		pthread_t *thread;
		sockaddr_in addr;
	};
	typedef std::vector<pthread_t> ThreadsList;

	void Update();
	static void *Run( void *arg );
	static void *ConnectionThread( void *arg );

	pthread_t& AddThread();
	void RemoveThread( const pthread_t *thread );

	bool m_run;
	WSADATA m_wsaData;
	SOCKET m_socket;
	pthread_t m_mainThread;
	timeval m_timeout;
	pthread_mutex_t m_threadList;

	ThreadsList m_listenThreads;
};

#endif /* COMMUNICATIONMANAGER_H_ */
