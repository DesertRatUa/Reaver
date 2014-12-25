/*
 * Client.cpp
 *
 *  Created on: 01 рту. 2014 у.
 *      Author: maximm
 */

#include "Client.h"
#include "Log.h"
#include <Messages/Message.h>

Client::Client() : socket( 0 ), m_disconnected( false )
{
}

Client::~Client()
{
	//thread->detach();
	Log::Add( "Destroy client: " + Log::AddrToStr( addr ) );
}

bool Client::operator==( const Client &client ) const
{
	return inet_ntoa(addr.sin_addr) == inet_ntoa(client.addr.sin_addr) && addr.sin_port == client.addr.sin_port;
}

void  Client::Send( const std::string& message ) const
{
	std::lock_guard<std::mutex> lock(m_mut);
	send( socket, message.c_str(), message.length(), 0);
}

void Client::SendRespond( const Message& message ) const
{
	Send( message.SerializeRespondStr() );
}

void Client::SendRequest( const Message& message ) const
{
	Send( message.SerializeReqestStr() );
}

std::string Client::GetAddr() const
{
	return Log::AddrToStr( addr );
}

void Client::Disconnect()
{
	m_disconnected = true;
}

bool Client::isDisconnected()
{
	return m_disconnected;
}

void Client::Join()
{
	if (thread.get())
	{
		thread->join();
	}
}
