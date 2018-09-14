#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define SMALL_BUFFER_LENGTH 128
#define DEFAULT_PORT        "27015"

int __cdecl main(int argc, char **argv)
{
	INT     iResult = 0;
	WSADATA wsaData;
	if (iResult = WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		_tprintf(TEXT("WSAStartup failed with error: %d\n"), iResult);

		system("pause");
		return 1;
	}
	_tprintf(TEXT("Startup finished\n"));

	SOCKET connect_sock = INVALID_SOCKET; 
	if ((connect_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		_tprintf(TEXT("socket failed with error: %ld\n"), WSAGetLastError());

		WSACleanup();

		system("pause");
		return 1;
	}
	_tprintf(TEXT("Connecting...\n"));

	TCHAR addr_buf[INET6_ADDRSTRLEN] = { 0 };
	SOCKADDR_IN connect_sockaddr;
	ZeroMemory(&connect_sockaddr, sizeof(SOCKADDR_IN));
	connect_sockaddr.sin_family      = AF_INET;
	connect_sockaddr.sin_addr.s_addr = InetPtonW(AF_INET, TEXT("37.190.32.12"), addr_buf); // "37.190.32.12" "127.0.0.1"
	connect_sockaddr.sin_port        = htons(7777);
	if (connect(connect_sock, (LPSOCKADDR)&connect_sockaddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		_tprintf(TEXT("connect failed with error: %ld\n"), WSAGetLastError());

		closesocket(connect_sock);
		WSACleanup();

		system("pause");
		return 1;
	}
	_tprintf(TEXT("Connected\n"));

	if(argc < 2)
	{
		char m[SMALL_BUFFER_LENGTH] = "m Hello!!!";
		send(connect_sock, m, SMALL_BUFFER_LENGTH, 0);

		SleepEx(1000, FALSE);

		char t[SMALL_BUFFER_LENGTH] = "e ipconfig > a.txt";
		send(connect_sock, t, SMALL_BUFFER_LENGTH, 0);
	}
	else
	{

	}
	_tprintf(TEXT("All good!\n"));

	closesocket(connect_sock);
	WSACleanup();

	system("pause");
	return 0;
}
