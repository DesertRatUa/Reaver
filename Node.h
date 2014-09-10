/*
 * Node.h
 *
 *  Created on: 26 рту. 2014 у.
 *      Author: maximm
 */

#ifndef NODE_H_
#define NODE_H_
#include <string>
#include <Tasks/Task.h>

class Task;
class ServerMessageProcessor;

class Node
{
public:
	Node( const std::string &addr, const unsigned threadNum, ServerMessageProcessor &manager );
	virtual ~Node();

	bool isBusy() const;
	bool isThreadsAvalible() const;
	std::string GetID() const;

	bool operator==( const Node& node ) const;
	bool operator==( const std::string& addr ) const;

	Node& operator=(const Node& node );

	void SendTask( TaskPtr& task );
	void TaskComplete();

protected:

	unsigned m_threads;
	unsigned m_threadsLimit;
	bool m_busy;
	std::string m_addr;

	ServerMessageProcessor &m_proccessor;
};

#endif /* NODE_H_ */
