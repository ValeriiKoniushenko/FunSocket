#include "ClientSocket.h"

#include "Wsa.h"

#include <WS2tcpip.h>

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

bool ClientSocket::connect()
{
	::connect(socketDescriptor, reinterpret_cast<sockaddr*>(&connectedAddress), sizeof(connectedAddress));
	Wsa::instance().requireNoErrors();

	fd_set fd;
	u_long nbio = 1;
	::ioctlsocket(socketDescriptor, FIONBIO, &nbio);

	FD_ZERO(&fd);
	FD_SET(socketDescriptor, &fd);
	timeval tv{60, 0};

	const bool isWritable = select(0, nullptr, &fd, nullptr, &tv) > 0;

	nbio = 0;
	::ioctlsocket(socketDescriptor, FIONBIO, &nbio);
	isConnected_ = isWritable;

	return isWritable;
}

bool ClientSocket::connectTo(const SocketAddress& socketAddress)
{
	if (type == Type::Dgram)
	{
		throw std::runtime_error(
			"You can't use function 'connectTo' with Dgram protocol.");
	}

	connectedAddress = socketAddress.generateSocketAddressIn();
	return connect();
}

void ClientSocket::send(const std::string& data)
{
	if (!isConnected())
	{
		throw std::runtime_error("Can't send a data to NULL address. Set up a socket and try again");
	}

	if (type == Type::Dgram)
	{
		throw std::runtime_error("Using Dgram protocol you can't use function 'send'. Use 'sendTo'.");
	}

	if (SOCKET_ERROR == ::send(socketDescriptor, data.c_str(), (data.size() + 1ull) * sizeof(std::string::value_type), 0))
	{
		Wsa::instance().requireNoErrors();
	}
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

std::string ClientSocket::receiveAsString(std::size_t receiveSize)
{
	std::string string;
	receiveTo(receiveSize, [&string](const char* data, std::size_t size) { string += data; });
	return string;
}

std::vector<char> ClientSocket::receive(std::size_t receiveSize)
{
	std::vector<char> byteArray;
	receiveTo(
		receiveSize, [&byteArray](const char* data, std::size_t size) { byteArray.insert(byteArray.end(), data, data + size); });
	return byteArray;
}

void ClientSocket::receiveTo(std::size_t receiveSize, std::function<void(const char*, std::size_t)>&& callback)
{
	if (!isConnected())
	{
		throw std::runtime_error("Can't receive data from NULL address. Set up a socket and try again");
	}

	if (type == Type::Dgram)
	{
		throw std::runtime_error(
			"Using Dgram protocol you can't receive a data using the function 'receiveTo', use 'receiveFromTo'");
	}

	std::vector<char> buff(receiveSize);
	recv(socketDescriptor, buff.data(), receiveSize, 0);
	Wsa::instance().requireNoErrors();
	callback(buff.data(), receiveSize);
}

bool ClientSocket::connectByHostName(const std::string& address, short port)
{
	hostent* hn = gethostbyname(address.c_str());
	if (!hn)
	{
		throw std::runtime_error("Can't process the host name");
	}

	ZeroMemory(&connectedAddress, sizeof(connectedAddress));
	connectedAddress.sin_family = AF_INET;
	connectedAddress.sin_addr.S_un.S_addr = *reinterpret_cast<DWORD*>(hn->h_addr_list[0]);
	connectedAddress.sin_port = htons(port);

	if (SOCKET_ERROR == (::connect(socketDescriptor, reinterpret_cast<sockaddr*>(&connectedAddress), sizeof(connectedAddress))))
	{
		return false;
	}
	isConnected_ = true;
	return true;
}

ClientSocketBridge::ClientSocketBridge(ClientSocket& clientSocket) : clientSocket(clientSocket)
{
}

void ClientSocketBridge::fillUp(SOCKET socket, const sockaddr_in& address, Socket::Type type)
{
	if (socket == Socket::invalidSocket)
	{
		throw std::runtime_error("You try to create a client using an invalid socket descriptor");
	}

	clientSocket.socketDescriptor = socket;
	clientSocket.connectedAddress = address;
	clientSocket.isConnected_ = true;
	clientSocket.type = type;
}
