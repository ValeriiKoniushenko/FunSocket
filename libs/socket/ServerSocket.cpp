#include "ServerSocket.h"

#include "Wsa.h"

ServerSocket::ServerSocket(AddressFamily addressFamily, Type type, Protocol protocol) : Socket(addressFamily, type, protocol)
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

ClientSocket ServerSocket::accept() const
{
	sockaddr_in connectedAddress{};
	int new_len = sizeof(connectedAddress);
	ZeroMemory(&connectedAddress, sizeof(connectedAddress));
	SOCKET connectedSocket = ::accept(socketDescriptor, reinterpret_cast<sockaddr*>(&connectedAddress), &new_len);
	Wsa::instance().requireNoErrors();

	ClientSocket clientSocket;
	ClientSocketBridge clientSocketBridge(clientSocket);
	clientSocketBridge.fillUp(connectedSocket, connectedAddress);

	return clientSocket;
}

bool ServerSocket::isCanAccept() const
{
	fd_set fd;
	u_long nbio = 1;
	::ioctlsocket(socketDescriptor, FIONBIO, &nbio);
	FD_ZERO(&fd);
	FD_SET(socketDescriptor, &fd);
	timeval tv{60, 1};
	const auto result = select(0, &fd, nullptr, nullptr, &tv) > 0;
	::ioctlsocket(socketDescriptor, FIONBIO, &nbio);
	return result;
}