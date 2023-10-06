#pragma once

#include "CopyableAndMoveable.h"
#include "NotCopyableButMovable.h"
#include "winsock2.h"

#include <string>

enum class AddressFamily
{
	None,
	Inet = AF_INET,
	Inet6 = AF_INET6,
};

class SocketAddress : public Utils::CopyableAndMoveable
{
public:
	__declspec(dllexport) SocketAddress() = default;
	__declspec(dllexport) SocketAddress(const std::string& address, USHORT port, AddressFamily addressFamily = AddressFamily::Inet);

	__declspec(dllexport) void setPort(USHORT port);
	_NODISCARD __declspec(dllexport) USHORT getPort() const;

	__declspec(dllexport) void setAddress(const std::string& address, AddressFamily addressFamily);
	_NODISCARD __declspec(dllexport) const std::string& getAddress() const;
	_NODISCARD __declspec(dllexport) IN_ADDR getAddressRaw() const;
	_NODISCARD __declspec(dllexport) sockaddr_in generateSocketAddressIn() const;
	__declspec(dllexport) void fromSockaddrIn(const sockaddr_in& sockaddr);

private:
	USHORT port = 0;
	IN_ADDR address{};
	std::string addressString;
	AddressFamily addressFamily = AddressFamily::Inet;
};

class Socket : public Utils::NotCopyableButMovable
{
public:
	enum class Type
	{
		None,
		Stream = SOCK_STREAM,
		Dgram = SOCK_DGRAM,
	};

	enum class Protocol
	{
		Auto = 0,
		Tcp = IPPROTO_TCP,
		Udp = IPPROTO_UDP,
	};

	inline static SOCKET invalidSocket = INVALID_SOCKET;

	__declspec(dllexport) Socket() = default;
	__declspec(dllexport) Socket(AddressFamily addressFamily, Type type, Protocol protocol = Protocol::Auto);
	__declspec(dllexport) ~Socket() override;
	__declspec(dllexport) Socket(Socket&& other) noexcept;
	__declspec(dllexport) Socket& operator=(Socket&& other) noexcept;

	_NODISCARD __declspec(dllexport) bool isValid() const;
	_NODISCARD __declspec(dllexport) SOCKET getSocket() const;

	__declspec(dllexport) void open(AddressFamily addressFamily, Type type, Protocol protocol = Protocol::Auto);
	__declspec(dllexport) virtual void close();

	_NODISCARD __declspec(dllexport) Type getType() const;

	_NODISCARD __declspec(dllexport) SocketAddress getOwnAddress() const;
protected:
	SOCKET socketDescriptor = Socket::invalidSocket;
	AddressFamily addressFamily = AddressFamily::Inet;
	Type type = Type::None;
};