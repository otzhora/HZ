// server


#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")
// #pragma comment (lib, "AdvApi32.lib")


using namespace std;

int main()
{
	WSADATA wsaData;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET client1Socket = INVALID_SOCKET;
	SOCKET client2Socket = INVALID_SOCKET;

	string bufstr;
	int iResult;
	int recvlen;
	
	struct addrinfo *result = NULL;
	struct addrinfo hints;
	
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		cout << "startup fail" << iResult << endl;
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo(NULL, "27015", &hints, &result);
	if (iResult != 0)
	{
		cout << "getaddrinfo error" << iResult << endl;
		WSACleanup();
		return 1;
	}

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		cout << "socket error" << WSAGetLastError() << endl;
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		cout << "bind error" << WSAGetLastError() << endl;
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		cout << "listen client1 error" << WSAGetLastError() << endl;
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	client1Socket = accept(ListenSocket, NULL, NULL);
	if (client1Socket == INVALID_SOCKET) {
		cout << "listen client1 error" << WSAGetLastError() << endl; 
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		cout << "listen client1 error" << WSAGetLastError() << endl;
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	client1Socket = accept(ListenSocket, NULL, NULL);
	if (client1Socket == INVALID_SOCKET) {
		cout << "listen client1 error" << WSAGetLastError() << endl;
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	closesocket(ListenSocket);

	for (;;)
	{
		bufstr = "send messege";
		iResult = send(client1Socket, (char*)&bufstr, bufstr.length(), 0);
		if (iResult == SOCKET_ERROR) {
			cout << "send failed with error: " <<  WSAGetLastError() << endl;
			closesocket(client1Socket);
			closesocket(client2Socket);
			WSACleanup();
			return 1;
		}
		bufstr = "wait client 1 messege";
		iResult = send(client2Socket, (char*)&bufstr, bufstr.length(), 0);
		if (iResult == SOCKET_ERROR) {
			cout << "send failed with error: " << WSAGetLastError() << endl;
			closesocket(client2Socket);
			closesocket(client2Socket);
			WSACleanup();
			return 1;
		}

		iResult = recv(client1Socket, (char*)&bufstr, 512, 0);
		if (iResult == SOCKET_ERROR) {
			cout << "recv failed with error: " << WSAGetLastError() << endl;
			closesocket(client2Socket);
			closesocket(client2Socket);
			WSACleanup();
			return 1;
		}

		iResult = send(client2Socket, (char*)&bufstr, bufstr.length(), 0);
		if (iResult == SOCKET_ERROR) {
			cout << "send failed with error: " << WSAGetLastError() << endl;
			closesocket(client2Socket);
			closesocket(client2Socket);
			WSACleanup();
			return 1;
		}
	}
	return 0;
}
