/*
 * Node.cpp
 *
 *  Created on: 26 рту. 2014 у.
 *      Author: maximm
 */

#include <Node.h>
#include "Client.h"

Node::Node( Client &client, const unsigned id ) : m_busy( false ), m_id( id ), m_client( &client )
{
}

Node::~Node()
{
}

bool Node::isBusy() const
{
	return m_busy;
}

unsigned Node::GetID() const
{
	return m_id;
}

bool Node::operator==( const Node& node ) const
{
	return m_id == node.m_id;
}

bool Node::operator==( const Client& client ) const
{
	return *m_client == client;
}

bool Node::operator==( const std::string& addr ) const
{
	return m_client->GetAddr() == addr;
}

bool Node::operator==( const unsigned id ) const
{
	return m_id == id;
}
