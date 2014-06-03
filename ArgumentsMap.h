/*
 * ArgumentsMap.h
 *
 *  Created on: 3 черв. 2014
 *      Author: maximm
 */

#ifndef ARGUMENTSMAP_H_
#define ARGUMENTSMAP_H_

#include "Argument.h"
#include <exception>
#include <map>

class ArgumentsMap
{
public:
	ArgumentsMap();
	virtual ~ArgumentsMap();

	void Init();
	void Set( const std::string &name );
	void Set( const std::string &name, const std::string &value );
	void UnSet( const std::string &name );
	Argument& Get( const std::string &name ) throw ( std::exception );

private:
	typedef std::map< std::string, Argument > ArgumentMap;
	typedef std::pair< std::string, Argument > ArgumentPair;
	ArgumentMap m_arguments;
	void AddArgument( std::string Name, std::string ShortName, std::string DefaultValue, std::string Description );
};

#endif /* ARGUMENTSMAP_H_ */
