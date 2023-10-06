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
		UDPServerSocket server;
		server.open(AddressFamily::Inet);
		server.bind({"127.0.0.1", 8088});

		auto result = server.receiveAsString(6);

		std::string str(result.data.begin(), result.data.end());
		cout << str << "\nFrom: " << result.client.getAddress() << ":" << result.client.getPort() << endl;

		system("pause");
	}
	catch (std::runtime_error& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}

	return 0;
}