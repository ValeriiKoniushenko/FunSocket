#pragma once

#include "ServerSocket.h"

namespace tcp
{
class HTTPServerSocket : public ServerSocket
{
public:
	__declspec(dllexport) HTTPServerSocket();
	__declspec(dllexport) HTTPServerSocket(const std::string& address, unsigned short port);

private:
};
}	 // namespace tcp
