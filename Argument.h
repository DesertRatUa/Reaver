/*
 * Argument.h
 *
 *  Created on: 3 черв. 2014
 *      Author: maximm
 */

#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include <string>

class Argument
{
public:
	Argument( const std::string &name, const std::string &shortName, const std::string &defaultValue, const std::string &description );
	virtual ~Argument();

	std::string m_name;
	std::string m_shortName;
	std::string m_defaultValue;
	std::string m_description;

	const bool isSet();
	void Set();
	void Set( const std::string &value );
	void UnSet();

protected:
	bool m_set;
};

#endif /* ARGUMENT_H_ */
