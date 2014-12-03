/*
 * EchoMessage.h
 *
 *  Created on: 19 рту. 2014 у.
 *      Author: maximm
 */

#ifndef ECHOMESSAGE_H_
#define ECHOMESSAGE_H_
#include <Messages/Message.h>

class EchoMessage : public Message
{
public:
	EchoMessage();
	EchoMessage( std::string text );
	virtual ~EchoMessage();

	virtual void SerializeReqest( tinyxml2::XMLDocument &doc ) const;
	virtual void SerializeRespond( tinyxml2::XMLDocument &doc ) const;
	virtual void DeserializeReqest( const tinyxml2::XMLDocument &doc );
	virtual void DeserializeRespond( const tinyxml2::XMLDocument &doc );

	std::string Text;
protected:
};

#endif /* ECHOMESSAGE_H_ */
