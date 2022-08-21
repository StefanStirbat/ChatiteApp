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

class ServerSocket
{
public:
	ServerSocket() = default;

	int createSocket();
	int acceptConnection();
	void processConection();
	
	~ServerSocket()
	{
		for (auto &th : mConn)
		{
			th.detach();
		}
	}

	std::vector<std::thread> mConn;
private:

	struct addrinfo* result = nullptr, * ptr = nullptr, hints;
	std::vector<SOCKET> mConnections;
	SOCKET ListenSocket = INVALID_SOCKET;
	WSADATA wsaData;

};

