#pragma once

#include "CopyableAndMoveable.h"
#include "NotCopyableButMovable.h"
#include "winsock2.h"

#include <string>

enum class AddressFamily
{
	Unspec = AF_UNSPEC,
	Unix = AF_UNIX,
	Inet = AF_INET,
	Implink = AF_IMPLINK,
	Pup = AF_PUP,
	Chaos = AF_CHAOS,
	Ns = AF_NS,
	Ipx = AF_IPX,
	Iso = AF_ISO,
	Osi = AF_OSI,
	Ecma = AF_ECMA,
	Datakit = AF_DATAKIT,
	Ccitt = AF_CCITT,
	Sna = AF_SNA,
	Decnet = AF_DECnet,
	Dli = AF_DLI,
	Lat = AF_LAT,
	Hylink = AF_HYLINK,
	Appletalk = AF_APPLETALK,
	Netbios = AF_NETBIOS,
	Voiceview = AF_VOICEVIEW,
	Firefox = AF_FIREFOX,
	Unknown1 = AF_UNKNOWN1,
	Ban = AF_BAN,
	Atm = AF_ATM,
	Inet6 = AF_INET6,
	Cluster = AF_CLUSTER,
	AF12844 = AF_12844,
	Irda = AF_IRDA,
	Netdes = AF_NETDES
};

class SocketAddress : public Utils::CopyableAndMoveable
{
public:
	__declspec(dllexport) SocketAddress() = default;
	__declspec(dllexport) SocketAddress(const std::string& address, USHORT port, AddressFamily addressFamily);

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
		Stream = SOCK_STREAM,
		Dgram = SOCK_DGRAM,
		Raw = SOCK_RAW,
		Rdm = SOCK_RDM,
		Seqpacket = SOCK_SEQPACKET,
	};

	enum class Protocol
	{
		Auto = 0,
		Icmp = IPPROTO_ICMP,
		Igmp = IPPROTO_IGMP,
		Tcp = IPPROTO_TCP,
		Udp = IPPROTO_UDP,
		Icmpv6 = IPPROTO_ICMPV6
	};

	inline static SOCKET invalidSocket = INVALID_SOCKET;

	__declspec(dllexport) Socket() = default;
	__declspec(dllexport) Socket(AddressFamily addressFamily, Type type, Protocol protocol = Protocol::Auto);
	__declspec(dllexport) ~Socket() override;
	__declspec(dllexport) Socket(Socket&& other) noexcept ;
	__declspec(dllexport) Socket& operator=(Socket&& other) noexcept ;

	_NODISCARD __declspec(dllexport) bool isValid() const;

	__declspec(dllexport) void open(AddressFamily addressFamily, Type type, Protocol protocol = Protocol::Auto);
	__declspec(dllexport) virtual void close();

protected:
	SOCKET socketDescriptor = Socket::invalidSocket;
	AddressFamily addressFamily = AddressFamily::Inet;
	Type type = Type::Stream;
};