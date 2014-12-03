/*
 * Message.h
 *
 *  Created on: 19 рту. 2014 у.
 *      Author: maximm
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_
#include <include.h>

class Message
{
public:
	Message();
	virtual ~Message();

	std::string SerializeReqestStr() const;
	std::string SerializeRespondStr() const;
	void DeserializeReqestStr( const std::string &xml );
	void DeserializeRespondStr( const std::string &xml );

	virtual void SerializeReqest( tinyxml2::XMLDocument &doc ) const = 0;
	virtual void SerializeRespond( tinyxml2::XMLDocument &doc ) const = 0;
	virtual void DeserializeReqest( const tinyxml2::XMLDocument &doc ) = 0;
	virtual void DeserializeRespond( const tinyxml2::XMLDocument &doc ) = 0;
};

#endif /* MESSAGE_H_ */
