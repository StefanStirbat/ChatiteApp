#include "ClientSocket.h"

#define DEFAULT_PORT "80"

int ClientSocket::createSocketAndConnect(PCSTR arg)
{
	int hr;
	hr = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (hr != 0)
	{
		std::cout << "WSAStartup failed" << hr << std::endl;
		return 1; //move above part in another function in main maybe ?
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;	// specify IP V4 family
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	hr = getaddrinfo(arg, DEFAULT_PORT, &hints, &result);
	if (hr != 0)
	{
		std::cout << "getaddrinfo failed" << std::endl;
		return 1;
	}

	this->mClientSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (this->mClientSocket == INVALID_SOCKET)
	{
		std::cout << " Socket creation failed" << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	hr = connect(this->mClientSocket, result->ai_addr, (int)result->ai_addrlen);
	if (hr == SOCKET_ERROR)
	{
		std::cout << "Faied to connect socket" << std::endl;
		freeaddrinfo(result);
		closesocket(this->mClientSocket);
		this->mClientSocket = INVALID_SOCKET;
		WSACleanup();

		return 1;
	}

	freeaddrinfo(result);

	if (this->mClientSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}


	std::cout << "Connected" << std::endl;
	return 0;
}