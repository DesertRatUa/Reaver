/*
 * Node.h
 *
 *  Created on: 26 ���. 2014 �.
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
	Node( const std::string &addr, ServerMessageProcessor &manager );
	virtual ~Node();

	bool isBusy() const;
	std::string GetID() const;

	bool operator==( const Node& node ) const;
	bool operator==( const std::string& addr ) const;

	Node& operator=(const Node& node );

	void SendTask( TaskPtr& task );
	void TaskComplete();

protected:

	bool m_busy;
	std::string m_addr;

	ServerMessageProcessor &m_proccessor;
};

#endif /* NODE_H_ */
