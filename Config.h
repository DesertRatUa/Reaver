/*
 * Config.h
 *
 *  Created on: 29 трав. 2014
 *      Author: maximm
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

class Config
{
	public:
		Config( std::string path );
		virtual ~Config();

		void Init();
		void Read();
		void Write();

	protected:
		std::string m_configFile;
		std::string m_path;
};

#endif /* CONFIG_H_ */
