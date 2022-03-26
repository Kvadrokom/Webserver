#include "Http_server.hpp"
#include "BindingSocket.hpp"
#include <sstream>

Http_server::Http_server(int domain, int service, int protocol, int port,
			u_long interface, int backlog) : AServer(domain, service, protocol, port, interface, backlog)
{
	// arr = "";
	launch();
}

Http_server::Http_server() : AServer(AF_INET, SOCK_STREAM, 0, 8500, INADDR_ANY, 10)
{
	launch();
};

void Http_server::launch()
{
	while (true)
	{
		std::cout << "===========Waiting==========\n";
		accepter();
		handler();
		responder();
		std::cout << "============Done============\n\n";
	}
}

void Http_server::accepter()
{
	struct sockaddr_in addr = getsocket()->get_address();
	socklen_t addrlen = sizeof addr;
	new_socket = accept((getsocket())->get_sock(), (struct sockaddr *)&addr,
						(socklen_t *)&addrlen);
	BindingSocket test;
	test.test_connection(new_socket);
	recv(new_socket, arr, sizeof(arr), 0);
	// read(new_socket, arr, 30000);
}

void Http_server::handler()
{
	std::cout << arr << "\n";
}

void Http_server::responder()
{
	std::stringstream response; // сюда будет записываться ответ клиенту
	std::stringstream response_body; // тело ответа
	response_body << "<title>Test C++ HTTP Server</title>\n"
        << "<h1>Test page</h1>\n"
        << "<p>This is body of the test page...</p>\n"
        << "<h2>Request headers</h2>\n"
        << "<pre>" << buf << "</pre>\n"
        << "<em><small>Test C++ Http Server</small></em>\n";

    // Формируем весь ответ вместе с заголовками
    response << "HTTP/1.1 200 OK\r\n"
        << "Version: HTTP/1.1\r\n"
        << "Content-Type: text/html; charset=utf-8\r\n"
        << "Content-Length: " << response_body.str().length()
        << "\r\n\r\n"
        << response_body.str();
	int result = send(new_socket, response.str().c_str(),
        response.str().length(), 0);
	if (result < 0) 
	{
        // произошла ошибка при отправле данных
        std::cerr << "send failed: " << "\n";
    }
	close(new_socket);
}

Http_server::~Http_server(){};