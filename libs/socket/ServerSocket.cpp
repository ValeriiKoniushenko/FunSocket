#include "ServerSocket.h"
#include "Wsa.h"

ServerSocket::ServerSocket(AddressFamily addressFamily, Type type, Protocol protocol) :
	Socket(addressFamily, type, protocol)
{
}

void ServerSocket::bind(const SocketAddress& socketAddress)
{
	if (isBound())
	{
		throw std::runtime_error("The socket already was bound.");
	}

	auto socketAddressIn = socketAddress.generateSocketAddressIn();
	::bind(socketDescriptor, reinterpret_cast<sockaddr*>(&socketAddressIn), sizeof(socketAddressIn));
	Wsa::instance().requireNoErrors();

	boundAddress = socketAddressIn;
}

bool ServerSocket::isBound() const
{
	return boundAddress.has_value();
}

void ServerSocket::close()
{
	Socket::close();

	boundAddress.reset();
}

void ServerSocket::listen(int maxConnectionsCount)
{
	::listen(socketDescriptor, maxConnectionsCount);
	Wsa::instance().requireNoErrors();
}
