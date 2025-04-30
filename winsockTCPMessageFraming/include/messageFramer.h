#pragma once
#define WIN32_LEAN_AND_MEAN

#include <iosfwd>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

namespace messageFramerTCP
{
	int safeSend(const char message[], int messageSize, SOCKET receivingSocket);

	char* safeReceive(SOCKET receivingSocket);

}
