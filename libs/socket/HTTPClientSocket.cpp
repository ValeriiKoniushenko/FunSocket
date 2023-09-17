#include "HTTPClientSocket.h"

namespace tcp
{
HTTPClientSocket::HTTPClientSocket() : ClientSocket(AddressFamily::Inet, Type::Stream)
{
}

HTTPClientSocket::HTTPClientSocket(const SocketAddress& socketAddress) : HTTPClientSocket()
{
	connectTo(socketAddress);
}

HTTPClientSocket::HTTPClientSocket(const std::string& address, int port) : HTTPClientSocket()
{
	connectByHostName(address, port);
}
}	 // namespace tcp