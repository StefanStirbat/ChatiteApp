#include <iostream>
#include "ClientSocket.h"

int main(int argc, char **argv)
{
	ClientSocket client;
	client.createSocketAndConnect(argv[1]);

	getchar();
	return 0;
}