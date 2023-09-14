#include "Socket.h"
#include "Wsa.h"
#include <ws2tcpip.h>

Socket::~Socket()
{
	close();
}

bool Socket::isValid() const
{
	return socketDescriptor != Socket::invalidSocket;
}

void Socket::close()
{
	if (isValid())
	{
		closesocket(socketDescriptor);
		socketDescriptor = Socket::invalidSocket;
	}
}

Socket::Socket(AddressFamily addressFamily, Socket::Type type, Socket::Protocol protocol/* = Protocol::Auto*/)
{
	open(addressFamily, type, protocol);
}

void Socket::open(AddressFamily addressFamily, Socket::Type type, Socket::Protocol protocol/* = Protocol::Auto*/)
{
	close();

	socketDescriptor = socket(
			static_cast<int>(addressFamily),
			static_cast<int>(type),
			static_cast<int>(protocol)
		);

	if (socketDescriptor == Socket::invalidSocket)
	{
		Wsa::instance().requireNoErrors();
	}
}

Socket& Socket::operator=(Socket&& other) noexcept
{
	close();
	socketDescriptor = other.socketDescriptor;
	addressFamily = other.addressFamily;
	type = other.type;

	other.socketDescriptor = Socket::invalidSocket;

	return *this;
}

Socket::Socket(Socket&& other) noexcept
{
	*this = std::move(other);
}

void SocketAddress::setPort(USHORT port)
{
	this->port = htons(port);
}

USHORT SocketAddress::getPort() const
{
	return ntohs(port);
}

void SocketAddress::setAddress(const std::string& address, AddressFamily addressFamily)
{
	if (addressFamily != AddressFamily::Inet && addressFamily != AddressFamily::Inet6)
	{
		throw std::runtime_error("Invalid Address Family for setting the socket's address. You have to use IPv4 or IPv6");
	}

	addressString = address;
	inet_pton(static_cast<int>(addressFamily), address.c_str(), &this->address);
}

const std::string& SocketAddress::getAddress() const
{
	return addressString;
}

IN_ADDR SocketAddress::getAddressRaw() const
{
	return address;
}

sockaddr_in SocketAddress::generateSocketAddressIn() const
{
	sockaddr_in addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr = address;

	return addr;
}

SocketAddress::SocketAddress(const std::string& address, USHORT port, AddressFamily addressFamily)
{
	setPort(port);
	setAddress(address, addressFamily);
}
