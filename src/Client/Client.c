#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")
int main()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		return -1;
	}

	SOCKET server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock == INVALID_SOCKET)
	{
		return -2;
	}

	// SOCKADDR_IN addr;
	// addr.sin_family = AF_INET;
	// addr.sin_port = htons(7777);
	// addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	// bind(server_sock, (struct sockaddr *)&addr, sizeof(addr));


	SOCKADDR_IN addr_sock;
	addr_sock.sin_family           = AF_INET;
	addr_sock.sin_addr.s_addr      = inet_addr("127.0.0.1");
	addr_sock.sin_port             = htons(7777);
	
	if (connect(server_sock, (LPSOCKADDR)&addr_sock, sizeof(struct sockaddr)) == SOCKET_ERROR)
	{	
		return -3;
	}
	char m[128] = "m Hello!!!";
	send(server_sock, m, 128, 0);
	Sleep(1000);
	char t[128] = "e ipconfig > a.txt";
	send(server_sock, t, 128, 0);

	shutdown(server_sock, 1);
	closesocket(server_sock);
	system("pause");
	return 0;
}

