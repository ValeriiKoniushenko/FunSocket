#pragma once

#include "Socket.h"

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
	__declspec(dllexport) void connect();
	__declspec(dllexport) void connectTo(const SocketAddress& socketAddress);

	__declspec(dllexport) void send(const std::string& data);
	__declspec(dllexport) void send(const std::vector<char>& data);

	__declspec(dllexport) std::string receiveAsString();

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