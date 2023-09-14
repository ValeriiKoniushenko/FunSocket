#include "ServerSocket.h"
#include "Wsa.h"

ServerSocket::ServerSocket(AddressFamily addressFamily, Type type, Protocol protocol) :
	Socket(addressFamily, type, protocol)
{
}

void ServerSocket::bind(const SocketAddress& socketAddress)
{
	auto socketAddressIn = socketAddress.generateSocketAddressIn();
	::bind(socketDescriptor, reinterpret_cast<sockaddr*>(&socketAddressIn), sizeof(socketAddressIn));
	Wsa::instance().requireNoErrors();

	boundAddress = socketAddressIn;
}
