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
		server.open(AddressFamily::Inet, Socket::Type::Dgram);
		server.bind(SocketAddress("127.0.0.1", 8088));

		char buff[6]{};
		sockaddr_in cliAddr{};
		int cliAddrLen = sizeof(cliAddr);
		auto readStatus = recvfrom(server.getSocket(), buff, 6, 0, (struct sockaddr*) &cliAddr, &cliAddrLen);
		if (readStatus < 0)
		{
			perror("reading error...\n");
			exit(-1);
		}

		cout.write(buff, readStatus);
		cout << endl;

		system("pause");
	}
	catch (std::runtime_error& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}

	return 0;
}