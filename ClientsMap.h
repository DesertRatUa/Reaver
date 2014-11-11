/*
 * ClientsMap.h
 *
 *  Created on: 23 окт. 2014 г.
 *      Author: maximm
 */

#ifndef CLIENTSMAP_H_
#define CLIENTSMAP_H_

#include "Client.h"

class ClientsMap
{
	public:
		ClientsMap();
		virtual ~ClientsMap();

		void Init();

		Client& Get( const std::string &addr );

		void Add( ClientPtr& client );
		void Remove( const ClientPtr& data );
		void RemoveDisconnected();
		void Clear();

	protected:
		typedef std::vector<ClientPtr> Clients;

		void RemoveClient( Clients::iterator &it );

		Clients m_clients;
		std::mutex m_clientsM;
};

#endif /* CLIENTSMAP_H_ */
