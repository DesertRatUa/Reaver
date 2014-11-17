/*
 * Config.h
 *
 *  Created on: 29 трав. 2014
 *      Author: maximm
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <boost/property_tree/ptree.hpp>

class Config
{
	public:
		Config( std::string path );
		virtual ~Config();

		void Init();
		void Read();
		void Write();

		enum Type
		{
			UNDEFINED = 0,
			SERVER = 1,
			CLIENT = 2
		} NodeType;

		std::string ServerIp;
		unsigned ServerPort;
		std::string ListenIp;
		unsigned ListenPort;
		unsigned ThreadNums;

	protected:
		boost::property_tree::ptree m_configTree;

		std::string m_configFile;
		std::string m_path;

	template< typename T >
	void GetValue( std::string ValueName, T& ValueStorage );
};

#endif /* CONFIG_H_ */
