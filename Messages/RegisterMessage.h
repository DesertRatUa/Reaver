/*
 * RegisterMessage.h
 *
 *  Created on: 26 рту. 2014 у.
 *      Author: maximm
 */

#ifndef REGISTERMESSAGE_H_
#define REGISTERMESSAGE_H_

#include <Messages/Message.h>

class RegisterMessage: public Message {
public:
	RegisterMessage();
	RegisterMessage( const unsigned threadNum );
	virtual ~RegisterMessage();

	virtual void _SerializeReqest( tinyxml2::XMLDocument &doc ) const;
	virtual void _SerializeRespond( tinyxml2::XMLDocument &doc ) const;
	virtual void DeserializeReqest( const tinyxml2::XMLDocument &doc );
	virtual void DeserializeRespond( const tinyxml2::XMLDocument &doc );

	std::string ClientId;
	std::string ErrorMsg;
	unsigned ThreadNum;
};

#endif /* REGISTERMESSAGE_H_ */
