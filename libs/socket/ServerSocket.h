#pragma once

#include "ClientSocket.h"
#include "Socket.h"

#include <optional>

class ServerSocket : public Socket
{
public:
	__declspec(dllexport) ServerSocket() = default;
	__declspec(dllexport) ServerSocket(AddressFamily addressFamily, Protocol protocol = Protocol::Auto);

	__declspec(dllexport) void bind(const SocketAddress& socketAddress);
	_NODISCARD __declspec(dllexport) bool isBound() const;
	__declspec(dllexport) void close() override;

private:
	std::optional<sockaddr_in> boundAddress{};
};

class TCPServerSocket : public ServerSocket
{
public:
	__declspec(dllexport) void listen(int maxConnectionsCount = SOMAXCONN);
	_NODISCARD __declspec(dllexport) TCPClientSocket accept() const;
	_NODISCARD __declspec(dllexport) bool isCanAccept() const;
	__declspec(dllexport) void open(AddressFamily addressFamily, Protocol protocol = Protocol::Auto);
};

class UDPServerSocket : public ServerSocket
{
public:
	struct Result
	{
		SocketAddress client;
		std::vector<char> data;
	};

	__declspec(dllexport) void open(AddressFamily addressFamily, Protocol protocol = Protocol::Auto);
	__declspec(dllexport) Result receive(std::size_t size);
	__declspec(dllexport) void sendTo(const std::string& data, const SocketAddress& address);
	__declspec(dllexport) void sendTo(const std::vector<char>& data, const SocketAddress& address);
};