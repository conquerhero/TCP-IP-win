// win32client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")
void ErrorHandling(char* message)
{
	fputs(message,stderr);
	fputc('\n', stderr);
	exit(1);

}

int main()
{
	unsigned short port = 2000;
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;
	struct sockaddr_in ser_addr;
	int str_len = 0;
	int idx = 0, read_len = 0;

	char message[30];
	

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAtaruo()error!");
	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket()error!");
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(port);

	if (connect(hSocket,(SOCKADDR*)&servAddr,sizeof(servAddr))==SOCKET_ERROR)
		 ErrorHandling("connect()error!");
	//strLen = recv(hSocket, message, sizeof(message) - 1, 0);

	while (read_len= recv(hSocket,&message[idx++],1,0))
	{
		if (read_len == -1)
			ErrorHandling("connect()error");
		str_len += read_len;
	}
	
	printf("Message from server : %s\n",message);
	printf("Function read call count: %d\n", str_len);

	getchar();
	closesocket(hSocket);	
	WSACleanup();
	
    return 0;
}

