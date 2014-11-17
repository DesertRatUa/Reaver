/*
 * include.h
 *
 *  Created on: 08 сент. 2014 г.
 *      Author: maximm
 */
#ifndef INCLUDE_H_
#define INCLUDE_H_

#include <string>
#include <exception>

class Task;
class ServerModule;
class ServerMessageProcessorInterface;
class ClientMessageProcessorInterface;
class ClientCommunicationManagerInterface;
class Message;
class ClientModule;

namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
}

namespace std
{
	class thread;
}

#endif /* INCLUDE_H_ */
