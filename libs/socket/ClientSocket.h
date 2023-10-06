#pragma once

#include "Socket.h"

#include <functional>
#include <optional>
#include <vector>

class TCPClientSocket : public Socket
{
public:
	__declspec(dllexport) TCPClientSocket();
	__declspec(dllexport) TCPClientSocket(AddressFamily addressFamily, Protocol protocol = Protocol::Auto);
	__declspec(dllexport) TCPClientSocket(TCPClientSocket&& other) noexcept;
	__declspec(dllexport) TCPClientSocket& operator=(TCPClientSocket&& other) noexcept;

	__declspec(dllexport) void close() override;
	_NODISCARD __declspec(dllexport) bool isConnected() const;
	_NODISCARD __declspec(dllexport) SocketAddress getAddress() const;
	__declspec(dllexport) bool connect();
	__declspec(dllexport) bool connectTo(const SocketAddress& socketAddress);
	__declspec(dllexport) bool connectByHostName(const std::string& address, short port = 80);

	__declspec(dllexport) void send(const std::string& data);
	__declspec(dllexport) void send(const std::vector<char>& data);

	__declspec(dllexport) void open(AddressFamily addressFamily, Protocol protocol = Protocol::Auto);

	__declspec(dllexport) std::string receiveAsString(std::size_t receiveSize);
	__declspec(dllexport) std::vector<char> receive(std::size_t receiveSize);
	__declspec(dllexport) void receiveTo(std::size_t receiveSize, std::function<void(const char*, std::size_t)>&& callback);

private:
	sockaddr_in connectedAddress;
	bool isConnected_ = false;
	friend class TCPClientSocketBridge;
};

class TCPClientSocketBridge
{
public:
	__declspec(dllexport) explicit TCPClientSocketBridge(TCPClientSocket& clientSocket);
	__declspec(dllexport) void fillUp(SOCKET socket, const sockaddr_in& address);

private:
	TCPClientSocket& clientSocket;
};

class UDPClientSocket : public Socket
{
public:
	struct Result
	{
		SocketAddress server;
		std::vector<char> data;
	};

	__declspec(dllexport) UDPClientSocket() = default;
	__declspec(dllexport) explicit UDPClientSocket(AddressFamily addressFamily, Protocol protocol = Protocol::Auto);
	__declspec(dllexport) void sendTo(const std::string& message, const SocketAddress& socketAddress);
	__declspec(dllexport) Result receive(std::size_t size);

private:
	friend class UDPClientSocketBridge;
};
