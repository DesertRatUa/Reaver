/*
 * MessageProcessor.h
 *
 *  Created on: 06 рту. 2014 у.
 *      Author: maximm
 */

#ifndef MESSAGEPROCESSOR_H_
#define MESSAGEPROCESSOR_H_

#include <include.h>
#include <map>

class MessageProcessor
{
public:
	MessageProcessor();
	virtual ~MessageProcessor();

	virtual void Init() = 0;
	void ProcessMessage( const std::string& message, const std::string& addr );

protected:
	typedef void (*Processor)( const tinyxml2::XMLDocument& doc, const std::string& addr );
	typedef std::map< unsigned, Processor > Processors;
	Processors m_processors;

	void RegisterProcessor( const unsigned id, Processor processor ) throw (std::runtime_error);

};

#endif /* MESSAGEPROCESSOR_H_ */
