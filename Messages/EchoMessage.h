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

	virtual std::string Serialize() const;
	virtual void Deserialize( const tinyxml2::XMLDocument &doc );

	std::string Text;
protected:
};

#endif /* ECHOMESSAGE_H_ */
