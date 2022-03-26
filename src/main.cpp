#include "ASocket.hpp"
#include "BindingSocket.hpp"
#include "ListeningSocket.hpp"
#include "Http_server.hpp"

int	main()
{
	Http_server server(AF_INET, SOCK_STREAM, 0, 8500, INADDR_ANY, 10);
	return 0;
}