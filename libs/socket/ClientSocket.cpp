#include "ClientSocket.h"

#include "Wsa.h"

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

void ClientSocket::connect()
{
	::connect(socketDescriptor, reinterpret_cast<sockaddr*>(&connectedAddress), sizeof(connectedAddress));
	Wsa::instance().requireNoErrors();
	isConnected_ = true;
}

void ClientSocket::connectTo(const SocketAddress& socketAddress)
{
	connectedAddress = socketAddress.generateSocketAddressIn();
	connect();
}

void ClientSocket::send(const std::string& data)
{
	if (!isConnected())
	{
		throw std::runtime_error("Can't send a data to NULL address. Set up a socket and try again");
	}

	::send(socketDescriptor, data.c_str(), data.size() * sizeof(std::string::value_type), 0);
	Wsa::instance().requireNoErrors();
}

void ClientSocket::send(const std::vector<char>& data)
{
	if (!isConnected())
	{
		throw std::runtime_error("Can't send data to NULL address. Set up a socket and try again");
	}

	::send(socketDescriptor, data.data(), data.size() * sizeof(char), 0);
	Wsa::instance().requireNoErrors();
}

std::string ClientSocket::receiveAsString()
{
	if (!isConnected())
	{
		throw std::runtime_error("Can't receive data from NULL address. Set up a socket and try again");
	}

	std::string data;
	const std::size_t size = 2048;
	char buff[size]{};

	while(1)
	{
		memset(buff, 0, size * sizeof(char));
		int len = recv (socketDescriptor, buff, size, 0);
		Wsa::instance().requireNoErrors();
		if ( (len == SOCKET_ERROR) || (len == 0) )
		{
			break;
		}
		data += buff;
	}

	return data;
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
