#ifndef HSERVER_H
#define HSERVER_H

#include "AServer.hpp"
#include <vector>
#include <string>
#include <unistd.h>

class Http_server: AServer
{
private:
	char		arr[1024];
	int			new_socket;
	char		buf[1024];
	void accepter();
	void handler();
	void responder();
public:
	Http_server();
	Http_server(int domain, int service, int protocol, int port,
				u_long interface, int backlog);
	~Http_server();

	void launch();
};




#endif