#include "ClientSocket.h"
#include "ServerSocket.h"
#include "Wsa.h"

#include <iostream>

using namespace std;

int main()
{
	try
	{
		Wsa::instance().initialize(1, 1);

		ServerSocket server;
		server.open(AddressFamily::Inet, Socket::Type::Stream);
		server.bind(SocketAddress("127.0.0.1", 8088));
		server.listen();
		auto client = server.accept();
		cout << "Connected client: " << client.getAddress().getAddress() << ":" << client.getAddress().getPort() << endl;

		client.send("Hello");
		cout << client.receiveAsString(6) << endl;
		system("pause");
	}
	catch (std::runtime_error& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}

	return 0;
}