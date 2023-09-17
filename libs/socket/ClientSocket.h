#pragma once

#include "Socket.h"

#include <functional>
#include <optional>
#include <vector>

class ClientSocket : public Socket
{
public:
	__declspec(dllexport) ClientSocket();
	__declspec(dllexport) ClientSocket(AddressFamily addressFamily, Type type, Protocol protocol = Protocol::Auto);
	__declspec(dllexport) ClientSocket(ClientSocket&& other) noexcept;
	__declspec(dllexport) ClientSocket& operator=(ClientSocket&& other) noexcept;

	__declspec(dllexport) void close() override;
	_NODISCARD __declspec(dllexport) bool isConnected() const;
	_NODISCARD __declspec(dllexport) SocketAddress getAddress() const;
	__declspec(dllexport) bool connect();
	__declspec(dllexport) bool connectTo(const SocketAddress& socketAddress);
	__declspec(dllexport) bool connectByHostName(const std::string& address, short port = 80);

	__declspec(dllexport) void send(const std::string& data);
	__declspec(dllexport) void send(const std::vector<char>& data);

	__declspec(dllexport) std::string receiveAsString();
	__declspec(dllexport) std::vector<unsigned char> receive();
	__declspec(dllexport) void receiveTo(std::function<void(const char*, std::size_t)>&& callback);

private:
	sockaddr_in connectedAddress;
	bool isConnected_ = false;
	friend class ClientSocketBridge;
};

class ClientSocketBridge
{
public:
	__declspec(dllexport) explicit ClientSocketBridge(ClientSocket& clientSocket);
	__declspec(dllexport) void fillUp(SOCKET socket, const sockaddr_in& address);

private:
	ClientSocket& clientSocket;
};