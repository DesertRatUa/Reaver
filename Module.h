/*
 * Module.h
 *
 *  Created on: 11 лип. 2014
 *      Author: maximm
 */

#ifndef MODULE_H_
#define MODULE_H_

#include "Config.h"
#include "ArgumentsMap.h"

class Module
{
public:
	Module( Config &config, ArgumentsMap &arguments );
	virtual ~Module();

	virtual void Init() = 0;
	virtual void Run() = 0;

	void ParseIp ( const std::string &addr, std::string &ip, unsigned &port );
	static Module* CreateModule( Config &config, ArgumentsMap &arguments );

protected:
	Config &m_config;
	ArgumentsMap &m_arguments;
};

#endif /* MODULE_H_ */
