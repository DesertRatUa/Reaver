/*
 * ClientsMap.cpp
 *
 *  Created on: 23 окт. 2014 г.
 *      Author: maximm
 */

#include <ClientsMap.h>
#include "Log.h"
#include <algorithm>

ClientsMap::ClientsMap()
{
}

ClientsMap::~ClientsMap()
{
}

void ClientsMap::Init()
{
}

void ClientsMap::Add( ClientPtr& client  )
{
	std::lock_guard<std::mutex> lock( m_clientsM );
	Clients::iterator it = std::find( m_clients.begin(), m_clients.end(), client );
	if( it !=  m_clients.end() )
	{
		throw std::runtime_error( "Client " + Log::AddrToStr( client->addr ) + " already stored " );
	}
	Log::Add( "Client stored: " + Log::AddrToStr( client->addr ) );
	m_clients.push_back( client );
}

void ClientsMap::Remove( const ClientPtr& client)
{
	std::lock_guard<std::mutex> lock( m_clientsM );
	Clients::iterator it = std::find( m_clients.begin(), m_clients.end(), client );
	if( it !=  m_clients.end() )
	{
		RemoveClient( it );
	}
	else
	{
		Log::Add( "Client: " + Log::AddrToStr( client->addr ) +" not found" );
	}
}

Client& ClientsMap::Get( const std::string &addr )
{
	std::lock_guard<std::mutex> lock( m_clientsM );
	Clients::iterator it;
	for( it = m_clients.begin(); it != m_clients.end(); ++it )
	{
		if ( Log::AddrToStr( (*it)->addr ) == addr )
		{
			break;
		}
	}
	if ( it == m_clients.end() )
	{
		throw( std::runtime_error( "Client: " + addr + "  not found!" ) );
	}
	return *it->get();
}

void ClientsMap::RemoveDisconnected()
{
	std::lock_guard<std::mutex> lock( m_clientsM );
	for( Clients::iterator it = m_clients.begin(); it != m_clients.end(); )
	{
		if ((*it)->isDisconnected() )
		{
			RemoveClient( it );
		}
		else
		{
			++it;
		}
	}
}

void ClientsMap::Clear()
{
	for( Clients::iterator it = m_clients.begin(); it != m_clients.end(); )
	{
		RemoveClient( it );
	}
}

void ClientsMap::RemoveClient( Clients::iterator &it )
{
	ClientPtr &client = (*it);
	Log::Add( "Client removed: " + Log::AddrToStr( client->addr ) );
	client->Join();
	it = m_clients.erase( it );
}
