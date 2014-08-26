/*
 * Message.h
 *
 *  Created on: 19 рту. 2014 у.
 *      Author: maximm
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_
#include <string>
#include <tinyxml2.h>

class ClientModule;

class Message
{
public:
	Message();
	virtual ~Message();

	virtual std::string SerializeReqest() const;
	virtual std::string SerializeRespond() const;

	virtual void _SerializeReqest( tinyxml2::XMLDocument &doc ) const = 0;
	virtual void _SerializeRespond( tinyxml2::XMLDocument &doc ) const = 0;
	virtual void DeserializeReqest( const tinyxml2::XMLDocument &doc ) = 0;
	virtual void DeserializeRespond( const tinyxml2::XMLDocument &doc ) = 0;

protected:
	void AddPacketId( tinyxml2::XMLDocument &doc, const unsigned id ) const;
	void AddText( tinyxml2::XMLDocument &doc, const std::string &name, const std::string &text ) const;
	void AddNum( tinyxml2::XMLDocument &doc, const std::string &name, const int num ) const;
};

#endif /* MESSAGE_H_ */
