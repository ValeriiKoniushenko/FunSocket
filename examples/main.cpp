#include "Wsa.h"
#include "ServerSocket.h"

#include <iostream>

int main()
{
	try
	{
		Wsa::instance().initialize(1, 1);
		ServerSocket listener;
		listener.open(AddressFamily::Inet, Socket::Type::Stream);
		listener.bind({"127.0.0.1", 27080, AddressFamily::Inet});
		listener.listen();

		ClientSocket connectedClient = listener.accept();
		std::cout << "Connected client: " << connectedClient.getAddress().getAddress() << ":"
				  << connectedClient.getAddress().getPort() << std::endl;

	}
	catch (std::runtime_error& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}

	return 0;
}