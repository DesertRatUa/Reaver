/*
 * Message.h
 *
 *  Created on: 19 рту. 2014 у.
 *      Author: maximm
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_
#include <string>

class ClientModule;
namespace tinyxml2
{
	class XMLDocument;
}

class Message
{
public:
	Message();
	virtual ~Message();

	virtual std::string Serialize() const = 0;
	virtual void Deserialize( const std::string &message );
	virtual void Deserialize( const tinyxml2::XMLDocument &doc ) = 0;
protected:
	void AddPacketId( tinyxml2::XMLDocument &doc, const unsigned id ) const;
	void AddText( tinyxml2::XMLDocument &doc, const std::string &name, const std::string &text ) const;
};

#endif /* MESSAGE_H_ */
