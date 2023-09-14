#include "ClientSocket.h"
#include <stdexcept>

ClientSocket::ClientSocket(AddressFamily addressFamily, Socket::Type type, Socket::Protocol protocol)
	: Socket(addressFamily, type, protocol)
{
	ZeroMemory(&connectedAddress, sizeof(connectedAddress));
}

ClientSocket::ClientSocket()
{
	ZeroMemory(&connectedAddress, sizeof(connectedAddress));
}

void ClientSocket::close()
{
	Socket::close();

	ZeroMemory(&connectedAddress, sizeof(connectedAddress));
	isConnected_ = false;
}

ClientSocket::ClientSocket(ClientSocket&& other) noexcept
{
	*this = std::move(other);
}

ClientSocket& ClientSocket::operator=(ClientSocket&& other) noexcept
{
	connectedAddress = other.connectedAddress;
	isConnected_ = other.isConnected_;

	ZeroMemory(&other.connectedAddress, sizeof(other.connectedAddress));
	other.isConnected_ = false;

	return *this;
}

bool ClientSocket::isConnected() const
{
	return isConnected_;
}

SocketAddress ClientSocket::getAddress() const
{
	SocketAddress socketAddress;
	socketAddress.fromSockaddrIn(connectedAddress);
	return socketAddress;
}

ClientSocketBridge::ClientSocketBridge(ClientSocket& clientSocket) : clientSocket(clientSocket)
{

}

void ClientSocketBridge::fillUp(SOCKET socket, const sockaddr_in& address)
{
	if (socket == Socket::invalidSocket)
		throw std::runtime_error("You try to create a client using an invalid socket descriptor");

	clientSocket.socketDescriptor = socket;
	clientSocket.connectedAddress = address;
	clientSocket.isConnected_ = true;
}
