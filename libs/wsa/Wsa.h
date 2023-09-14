#pragma once
#include "Singleton.h"
#include "winsock2.h"

class Wsa : public Singleton<Wsa>
{
public:
	__declspec(dllexport) static std::string errorCodeToString(int code);
	__declspec(dllexport) void initialize(int major, int minor);
	__declspec(dllexport) void requireNoErrors();

private:
	WSADATA ws;
};