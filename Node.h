/*
 * Node.h
 *
 *  Created on: 26 рту. 2014 у.
 *      Author: maximm
 */

#ifndef NODE_H_
#define NODE_H_
#include <string>

class Client;

class Node
{
public:
	Node( Client &client, const unsigned id );
	virtual ~Node();

	bool isBusy() const;
	std::string GetID() const;

	bool operator==( const Node& node ) const;
	bool operator==( const Client& client ) const;
	bool operator==( const std::string& addr ) const;

protected:
	bool m_busy;
	Client *m_client;
};

#endif /* NODE_H_ */
