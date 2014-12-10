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

		virtual void Process();
		virtual unsigned GetID() const;
		virtual Task* Clone();
		virtual bool isDone();

		virtual Tasks SeperateTask( const unsigned threadNums, const unsigned plannerID ) const;

		void SetHash( const std::string &hash ) throw ( std::exception );
		std::string GetResult();

	protected:
		std::string Hash;
		unsigned begin, end, result;
		unsigned char digest[MD5_DIGEST_LENGTH];
		char mdString[33];

		std::string GetMD5( const std::string &text );

		virtual void _SerializeRequest( tinyxml2::XMLDocument &doc ) const;
		virtual void _DeserializeRequest( const tinyxml2::XMLDocument &doc ) ;

		virtual void _SerializeRespond( tinyxml2::XMLDocument &doc ) const;
		virtual void _DeserializeRespond( const tinyxml2::XMLDocument &doc ) ;
};

#endif /* MD5TASK_H_ */
