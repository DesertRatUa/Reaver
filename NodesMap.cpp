/*
 * NodesMap.cpp
 *
 *  Created on: 10 сент. 2014 г.
 *      Author: maximm
 */

#include <NodesMap.h>
#include "Log.h"
#include <stdexcept>
#include <thread>
#include <algorithm>

NodesMap::NodesMap()
{
}

NodesMap::~NodesMap()
{
}

void NodesMap::Init()
{
}

void NodesMap::RegisterNode( const Client& client, const unsigned threadNum, ServerMessageProcessorInterface &manager ) throw ( std::exception )
{
	std::lock_guard<std::mutex> lock(m_mut);

	Nodes::iterator iter = std::find( m_nodes.begin(), m_nodes.end(), client.GetAddr() );
	if ( iter == m_nodes.end() )
	{
		m_nodes.push_back( Node( client, threadNum, manager ) );
		Log::Add( "Node: " + client.GetAddr() + " registered with avalible threads: " + Log::IntToStr( threadNum ) );
	}
	else
	{
		throw std::runtime_error( "Node: " + client.GetAddr() + " already registered" );
	}
}

void NodesMap::UnregisterNode( const Client& client ) throw ( std::exception )
{
	std::lock_guard<std::mutex> lock(m_mut);

	Nodes::iterator iter = std::find( m_nodes.begin(), m_nodes.end(), client.GetAddr() );
	if ( iter != m_nodes.end() )
	{
		m_nodes.erase( iter );
		Log::AddMessage( "Node: " + client.GetAddr() + " unregistered" );
	}
	else
	{
		throw std::runtime_error( "Node: " + client.GetAddr() + " not registered" );
	}
}

Node& NodesMap::GetNode( const Client& client ) throw ( std::exception )
{
	std::lock_guard<std::mutex> lock(m_mut);

	Nodes::iterator iter = std::find( m_nodes.begin(), m_nodes.end(), client.GetAddr() );
	if ( iter == m_nodes.end() )
	{
		throw std::runtime_error( "Node: " + client.GetAddr() + " Not registered" );
	}
	Node& node = *iter;
	return node;
}


unsigned NodesMap::GetThreadsCount() const
{
	std::lock_guard<std::mutex> lock(m_mut);
	unsigned count = 0;

	for ( Nodes::const_iterator iter = m_nodes.begin(); iter != m_nodes.end(); ++iter )
	{
		count += iter->GetThreadsCount();
	}
	return count;
}

void NodesMap::TaskComplete(  const Client& client, const TaskPtr &task  )
{
	std::lock_guard<std::mutex> lock(m_mut);

	Nodes::iterator iter = std::find( m_nodes.begin(), m_nodes.end(), client.GetAddr() );
	if ( iter == m_nodes.end() )
	{
		throw std::runtime_error( "Node: " + client.GetAddr() + " Not registered" );
	}
	iter->TaskComplete( task );
}
