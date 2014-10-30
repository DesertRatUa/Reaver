/*
 * MD5Task.h
 *
 *  Created on: 27 окт. 2014 г.
 *      Author: maximm
 */

#ifndef MD5TASK_H_
#define MD5TASK_H_

#include "Task.h"
#include <string.h>
#define MD5_DIGEST_LENGTH 16

class MD5Task : public Task
{
	public:
		MD5Task();
		virtual ~MD5Task();

		const static unsigned ID = 2;

		virtual void SerializeRequest( tinyxml2::XMLDocument &doc ) const;
		virtual void DeserializeRequest( const tinyxml2::XMLDocument &doc ) ;

		virtual void SerializeRespond( tinyxml2::XMLDocument &doc ) const;
		virtual void DeserializeRespond( const tinyxml2::XMLDocument &doc ) ;

		virtual void Process();
		virtual unsigned GetID() const;

		void SetHash( const std::string &hash ) throw ( std::exception );
		std::string GetResult();

	protected:
		std::string Hash;
		unsigned begin, end, result;
		unsigned char digest[MD5_DIGEST_LENGTH];
		char mdString[33];

		std::string GetMD5( const std::string &text );
};

#endif /* MD5TASK_H_ */
