// win32server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);

}

int main()
{
	WSADATA wsaData;
	SOCKET hServSock, hCIntSock;
	SOCKADDR_IN servAddr, cIntAddr;
	int szCIntAddr;
	char message[] = "Hello World!";

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStarup()error");
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("SOCKET()error");
	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(2000);

	if (bind(hServSock,(SOCKADDR*)&servAddr,sizeof(servAddr))== SOCKET_ERROR)
		ErrorHandling("BIND()error");
	if (listen(hServSock,5)==SOCKET_ERROR)
		ErrorHandling("listen()error");
	
	szCIntAddr = sizeof(cIntAddr);
	hCIntSock = accept(hServSock, (SOCKADDR*)&cIntAddr, &szCIntAddr);
	if (hCIntSock == INVALID_SOCKET)
		ErrorHandling("accept()error");
	send(hCIntSock,message,sizeof(message),0);
	closesocket(hCIntSock);
	closesocket(hServSock);
	WSACleanup();
    return 0;
}

