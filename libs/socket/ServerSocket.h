#pragma once

#include "Socket.h"

class ServerSocket : public Socket
{
public:
	__declspec(dllexport) ServerSocket(AddressFamily addressFamily, Type type, Protocol protocol = Protocol::Auto);
	__declspec(dllexport) void bind(const SocketAddress& socketAddress);
private:
	sockaddr_in boundAddress{};
};