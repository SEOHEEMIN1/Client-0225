#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{

	WSAData WsaData;

	WSAStartup(MAKEWORD(2, 2), &WsaData);

	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN ServerAddr;
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_family = PF_INET;
	ServerAddr.sin_port = htons(5001);
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		cout << "connent error : " << GetLastError() << endl;
		exit(-1);
	}

	char Message[] = "give me message.";
	send(ServerSocket, Message, strlen(Message) + 1, 0);

	cout << "Server send : " << Message << endl;

	char Buffer[1024] = { 0, };
	int RecvLength = recv(ServerSocket, Buffer, 1024, 0);

	cout << Buffer << endl;

	closesocket(ServerSocket);

	WSACleanup();

}