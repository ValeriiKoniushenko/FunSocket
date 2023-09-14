#include "Wsa.h"
#include "Socket.h"

#include <iostream>

int main()
{
	try
	{
		Wsa::instance().initialize(1, 1);
		Socket socket(AddressFamily::Inet, Socket::Type::Stream);

	}
	catch (std::runtime_error& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}

	return 0;
}