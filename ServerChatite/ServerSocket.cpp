#include "ServerSocket.h"

int ServerSocket::createSocket()
{
	int hr;
	hr = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (hr != 0)
	{
		std::cout << "WSAStartup failed" << hr << std::endl;
		return 1; //move above part in another function in main maybe ?
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;	// specify IP V4 family
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	hr = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (hr != 0)
	{
		std::cout << "getaddrinfo failed" << std::endl;
		return 1;
	}

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (ListenSocket == INVALID_SOCKET)
	{
		std::cout << " Socket creation failed" << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	hr = bind(ListenSocket, result->ai_addr, result->ai_addrlen);
	if (hr != 0)
	{
		std::cout << "Faied to bind socket" << std::endl;
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();

		return 1;
	}
	freeaddrinfo(result);

	hr = listen(ListenSocket, SOMAXCONN);
	if (hr != 0)
	{
		std::cout << "Failed to establish listening" << std::endl;
		closesocket(ListenSocket);
		WSACleanup();
	}
	std::cout << "Server is working" << std::endl;
	return 0;
}

void ServerSocket::processConection()
{
	std::cout << "Connection accepted" << std::endl;
}

int ServerSocket::acceptConnection()
{
	SOCKET tempConnectionSocket;

	std::thread acceptThread([&]() {while (tempConnectionSocket = accept(ListenSocket, nullptr, nullptr))
	{
		if (tempConnectionSocket != INVALID_SOCKET)
		{
			mConnections.emplace_back(tempConnectionSocket);
			mConn.push_back(std::thread([this] {
				//this->processConection();
				}));
		}
	}});
	acceptThread.detach();
	return 0;
}