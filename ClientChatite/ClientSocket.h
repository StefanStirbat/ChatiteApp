#pragma once

#ifdef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>
#include <iostream>

#include <vector>
#include <thread>

#define DEFAULT_PORT "80"
#pragma comment(lib, "Ws2_32.lib")

class ClientSocket
{
public:
	int createSocketAndConnect(PCSTR arg);

private:
	struct addrinfo* result = nullptr, * ptr = nullptr, hints;
	SOCKET mClientSocket = INVALID_SOCKET; 
	WSADATA wsaData;
};

