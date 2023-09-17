#include "HTTPServerSocket.h"

namespace tcp
{

HTTPServerSocket::HTTPServerSocket(const std::string& address, unsigned short port)
	: ServerSocket(AddressFamily::Inet, Socket::Type::Stream)
{
	bind({address, port, AddressFamily::Inet});
}

HTTPServerSocket::HTTPServerSocket() : ServerSocket(AddressFamily::Inet, Socket::Type::Stream)
{
}

}	 // namespace tcp
