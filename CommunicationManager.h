/*
 * CommunicationManager.h
 *
 *  Created on: 13 ����. 2014
 *      Author: maximm
 */

#ifndef COMMUNICATIONMANAGER_H_
#define COMMUNICATIONMANAGER_H_

#include "include.h"
#include "Thread.h"
#include "Module.h"
#include <vector>
#if defined WIN32 || defined WIN64
   #include <winsock2.h>
#else
   #include <sys/socket.h>
   #include <sys/un.h>
#endif

class MessageProcessor;

class CommunicationManager : public ModuleInterface
{
public:
	CommunicationManager( MessageProcessor &processor, bool &isRun );
	virtual ~CommunicationManager();

	virtual void Init();
	virtual void Stop();

protected:
	static void ReadSocket( SOCKET &socket, CommunicationManager &manager, const std::string &addr );
	virtual void CloseAdditionalThreads();

	MessageProcessor &m_processor;

	bool &m_run;
	WSADATA m_wsaData;
	SOCKET m_socket;
	ThreadPtr m_mainThread;
	timeval m_timeout;
	sockaddr_in m_address;
};

#endif /* COMMUNICATIONMANAGER_H_ */
