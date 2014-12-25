/*
 * Node.h
 *
 *  Created on: 26 рту. 2014 у.
 *      Author: maximm
 */

#ifndef NODE_H_
#define NODE_H_

#include "include.h"
#include "Tasks/Task.h"
#include <vector>
#include <mutex>
#include "Client.h"

class Node
{
public:
	Node( const Client &client, const unsigned threadNum, ServerMessageProcessorInterface &manager );
	virtual ~Node();

	std::string GetAddr() const;
	unsigned GetThreadsCount() const;

	bool operator==( const Node& node ) const;
	bool operator==( const std::string& addr ) const;
	void SendTask( const TaskPtr& task ) throw ( std::exception );
	void TaskComplete( const TaskPtr& task ) throw ( std::exception );

protected:
	unsigned m_threads;
	const Client *m_client;
	std::shared_ptr<std::mutex> m_mut;

	ServerMessageProcessorInterface *m_proccessor;
};

#endif /* NODE_H_ */
