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
#include <vector>

class ArgumentsMap
{
public:
	ArgumentsMap();
	virtual ~ArgumentsMap();

	void Init();
	void Set( const std::string &name ) throw ( std::exception );
	void Set( const std::string &name, const std::string &value );
	void UnSet( const std::string &name ) throw ( std::exception );
	void ParseArgument( std::string name );

	Argument& Get( const std::string &name ) throw ( std::exception );
	Argument& GetShort( const std::string &name ) throw ( std::exception );

private:
	typedef std::vector< Argument > Arguments;
	Arguments m_arguments;
	void AddArgument( std::string Name, std::string ShortName, std::string DefaultValue, std::string Description );
	Argument& Get( const Argument &arg ) throw ( std::exception );
};

#endif /* ARGUMENTSMAP_H_ */
