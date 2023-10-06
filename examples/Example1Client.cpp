#include "ClientSocket.h"
#include "Wsa.h"

#include <iostream>

using namespace std;

int main()
{
	try
	{
		Wsa::instance().initialize(1, 1);

		TCPClientSocket client;
		client.open(AddressFamily::Inet);
		client.connectTo({"127.0.0.1", 8088});

		cout << "Response: " << client.receiveAsString(6) << endl;
		client.send("World");

		cout << "Response: " << client.receiveAsString(6) << endl;
		client.send("World");

		system("pause");
	}
	catch (std::runtime_error& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}

	return 0;
}