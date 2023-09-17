#pragma once

#include "ClientSocket.h"

namespace tcp
{
class HTTPClientSocket : public ClientSocket
{
public:
	__declspec(dllexport) HTTPClientSocket();
	__declspec(dllexport) HTTPClientSocket(const SocketAddress& socketAddress);
	__declspec(dllexport) HTTPClientSocket(const std::string& address, int port = 80);

private:
};
}	 // namespace tcp
