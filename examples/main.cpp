#include "Wsa.h"
#include "ServerSocket.h"

#include <iostream>

int main()
{
	try
	{
		Wsa::instance().initialize(1, 1);
		ServerSocket listener(AddressFamily::Inet, Socket::Type::Stream);
		listener.bind({"127.0.0.1", 27080, AddressFamily::Inet});
		listener.listen();

		ClientSocket connectedClient = listener.accept();
		std::cout << "Connected client: " << connectedClient.getAddress().getAddress() << ":"
				  << connectedClient.getAddress().getPort() << std::endl;

		connectedClient.send("HTTP/1.0\r\nContent-length: 11\r\n\r\nHello world");
	}
	catch (std::runtime_error& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}

	return 0;
}