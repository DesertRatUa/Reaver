/*
 * ClientMessageProcessor.cpp
 *
 *  Created on: 08 ���. 2014 �.
 *      Author: maximm
 */

#include "ClientMessageProcessor.h"
#include "ClientModule.h"

ClientModule *ClientMessageProcessor::m_parent(NULL);

ClientMessageProcessor::ClientMessageProcessor( ClientModule *parent  )
{
	m_parent = parent;
}

ClientMessageProcessor::~ClientMessageProcessor()
{
}

void ClientMessageProcessor::Init()
{
	RegisterProcessor( 1, &ClientMessageProcessor::RecieveEchoMessage );
}

void ClientMessageProcessor::RecieveEchoMessage( const std::string& message, const std::string& addr )
{

}
