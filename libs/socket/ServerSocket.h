#pragma once

#include "Socket.h"
#include "ClientSocket.h"
#include <optional>

class ServerSocket : public Socket
{
public:
	__declspec(dllexport) ServerSocket() = default;
	__declspec(dllexport) ServerSocket(AddressFamily addressFamily, Type type, Protocol protocol = Protocol::Auto);

	__declspec(dllexport) void bind(const SocketAddress& socketAddress);
	_NODISCARD __declspec(dllexport) bool isBound() const;
	__declspec(dllexport) void close() override;
	__declspec(dllexport) void listen(int maxConnectionsCount = SOMAXCONN);
	_NODISCARD __declspec(dllexport) ClientSocket accept() const;

private:
	std::optional<sockaddr_in> boundAddress{};
};