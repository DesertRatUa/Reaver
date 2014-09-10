/*
 * NodesMap.h
 *
 *  Created on: 10 сент. 2014 г.
 *      Author: maximm
 */

#ifndef NODESMAP_H_
#define NODESMAP_H_
#include <string>
#include <pthread.h>
#include <vector>
#include "Node.h"

class ServerMessageProcessor;

class NodesMap
{
public:
	NodesMap( ServerMessageProcessor &processor );
	virtual ~NodesMap();

	void Init();

	void RegisterNode( const std::string& addr, const unsigned threadNum );
	void UnregisterNode( const std::string& addr );
	Node& GetNode( const std::string& addr );
	Node* GetFreeNode();
	void TaskComplete( const std::string& addr );

protected:

	typedef std::vector<Node> Nodes;
	Nodes m_nodes;
	pthread_mutex_t m_mut;
	ServerMessageProcessor &m_processor;
};

#endif /* NODESMAP_H_ */
