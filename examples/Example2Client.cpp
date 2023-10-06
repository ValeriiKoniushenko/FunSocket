#include "ClientSocket.h"
#include "Wsa.h"

#include <iostream>

using namespace std;

int main()
{
	try
	{
		Wsa::instance().initialize(1, 1);
		UDPClientSocket client(AddressFamily::Inet);

		client.sendTo("Hello", {"127.0.0.1", 8088});
		cout << client.getOwnAddress().getAddress() << ":" << client.getOwnAddress().getPort() << endl;

		auto result = client.receive(5);

		string str(result.data.begin(), result.data.end());
		cout << str << endl;
		cout << result.server.getAddress() << ":" << result.server.getPort() << endl;

		system("pause");
	}
	catch (std::runtime_error& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}

	return 0;
}