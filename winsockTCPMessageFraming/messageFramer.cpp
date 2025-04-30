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
    /**
     * TCP Send that deals with the messageFraming Issue
     * @param receivingSocket
     * @return char * message
     */
	int safeSend(const char message[], int messageSize, SOCKET receivingSocket)
    {
        std::cout << "STARTING SEND" << '\n';

        std::string messageSizeString = std::to_string(messageSize);
        std::cout << "Sending message of size " << messageSizeString << '\n';
        int iResult = send(receivingSocket, messageSizeString.c_str(), 4, 0);
        if (iResult == SOCKET_ERROR)
        {
            printf("socket length send failed with error: %ld\n", WSAGetLastError());
            closesocket(receivingSocket);
            WSACleanup();
            return 1;
        }
        std::cout << "Sending message " << message << '\n';
        iResult = send(receivingSocket, message, messageSize, 0);
        if (iResult == SOCKET_ERROR)
        {
            printf("socket message send failed with error: %ld\n", WSAGetLastError());
            closesocket(receivingSocket);
            WSACleanup();
            return 1;
        }
        return 0;
    }

    /**
     * TCP Receive that deals with the messageFraming Issue
     * @param receivingSocket
     * @return char * message
     */
	char* safeReceive(SOCKET receivingSocket)
    {
        std::cout << "STARTING RECEIVE" << '\n';
        char incomingMessageSize[4];

        int iResult = recv(receivingSocket, incomingMessageSize, 4, 0);
        if (iResult == SOCKET_ERROR)
        {
            printf("Failed to receive message size with error: %ld\n", WSAGetLastError());
            closesocket(receivingSocket);
            WSACleanup();
        }
        std::cout << "Incoming message size " << strtol(incomingMessageSize, nullptr, 10) << '\n';
        //message allocated to heap remember to free from memory after used
        char* messageReceived = new char[strtol(incomingMessageSize, nullptr, 10)];
        iResult = recv(receivingSocket, messageReceived, strtol(incomingMessageSize, nullptr, 10), 0);
        if (iResult == SOCKET_ERROR)
        {
            printf("Failed to receive message with error: %ld\n", WSAGetLastError());
            closesocket(receivingSocket);
            WSACleanup();
        }
        std::cout << "Message Received is " << messageReceived << '\n';
        return messageReceived;
    }

}
