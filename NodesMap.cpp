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

void NodesMap::RegisterNode( const std::string& addr, const unsigned threadNum, ServerMessageProcessorInterface &manager ) throw ( std::exception )
{
	std::lock_guard<std::mutex> lock(m_mut);

	Nodes::iterator iter = std::find( m_nodes.begin(), m_nodes.end(), addr );
	if ( iter == m_nodes.end() )
	{
		m_nodes.push_back( Node( addr, threadNum, manager ) );
		Log::Add( "Node: " + addr + " registered with avalible threads: " + Log::IntToStr( threadNum ) );
	}
	else
	{
		throw std::runtime_error( "Node: " + addr + " already registered" );
	}
}

void NodesMap::UnregisterNode( const std::string& addr ) throw ( std::exception )
{
	std::lock_guard<std::mutex> lock(m_mut);

	Nodes::iterator iter = std::find( m_nodes.begin(), m_nodes.end(), addr );
	if ( iter != m_nodes.end() )
	{
		m_nodes.erase( iter );
		Log::AddMessage( "Node: " + addr + " unregistered" );
	}
	else
	{
		throw std::runtime_error( "Node: " + addr + " not registered" );
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

unsigned NodesMap::GetFreeThreadsNum()
{
	std::lock_guard<std::mutex> lock(m_mut);
	unsigned count = 0;
	for ( Nodes::iterator iter = m_nodes.begin(); iter != m_nodes.end(); ++iter )
	{
		count += iter->GetFreeThreadsNum();
	}
	return count;
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
