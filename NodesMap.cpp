/*
 * NodesMap.cpp
 *
 *  Created on: 10 сент. 2014 г.
 *      Author: maximm
 */

#include <NodesMap.h>
#include "ServerMessageProcessor.h"
#include "Log.h"
#include <stdexcept>
#include <thread>
#include <algorithm>

NodesMap::NodesMap( ServerMessageProcessor &processor ) : m_processor(processor)
{
}

NodesMap::~NodesMap()
{
}

void NodesMap::Init()
{
}

void NodesMap::RegisterNode( const std::string& addr, const unsigned threadNum )
{
	std::lock_guard<std::mutex> lock(m_mut);

	Nodes::iterator iter = std::find( m_nodes.begin(), m_nodes.end(), addr );
	if ( iter == m_nodes.end() )
	{
		m_nodes.push_back( Node( addr, threadNum, m_processor ) );
		m_processor.SendRegisterMessage( addr, NULL );
		Log::Add( "Node: " + addr + " registered with avalible threads: " + Log::UnsignedToStr( threadNum ) );
	}
	else
	{
		std::string error = "Node: " + addr + " already registered";
		Log::Add( error );
		m_processor.SendRegisterMessage( addr, &error );
	}
}

void NodesMap::UnregisterNode( const std::string& addr )
{
	std::lock_guard<std::mutex> lock(m_mut);

	Nodes::iterator iter = std::find( m_nodes.begin(), m_nodes.end(), addr );
	if ( iter == m_nodes.end() )
	{
		Log::AddMessage( "Node: " + addr + " not registered" );
	}
	else
	{
		m_nodes.erase( iter );
		Log::AddMessage( "Node: " + addr + " unregistered" );
	}
}

Node& NodesMap::GetNode( const std::string& addr ) throw ( std::exception )
{
	std::lock_guard<std::mutex> lock(m_mut);

	Nodes::iterator iter = std::find( m_nodes.begin(), m_nodes.end(), addr );
	if ( iter == m_nodes.end() )
	{
		throw std::runtime_error( "Node: " + addr + " Not registered" );
	}
	Node& node = *iter;
	return node;
}

Node* NodesMap::GetFreeNode()
{
	Node* node = NULL;
	std::lock_guard<std::mutex> lock(m_mut);
	for ( Nodes::iterator iter = m_nodes.begin(); iter != m_nodes.end(); ++iter )
	{
		if ( iter->isThreadsAvalible() )
		{
			node = &(*iter);
			break;
		}
	}
	return node;
}

void NodesMap::TaskComplete( const std::string& addr )
{
	std::lock_guard<std::mutex> lock(m_mut);

	Nodes::iterator iter = std::find( m_nodes.begin(), m_nodes.end(), addr );
	if ( iter == m_nodes.end() )
	{
		throw std::runtime_error( "Node: " + addr + " Not registered" );
	}
	iter->TaskComplete();
}
