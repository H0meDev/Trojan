#include "Server.h"

// #pragma comment (lib, "Mswsock.lib")
// #pragma comment(linker, "/MERGE:.rdata=.text")
// #pragma comment(linker, "/FILEALIGN:512 /SECTION:.text,EWRX /IGNORE:4078")
// #pragma comment(linker, "/ENTRY:WinMain")

int __cdecl main(char** argv, int argc)
{
	// Copy2Sysdir();
	/*SOCKET socket = InitServer();
	if (socket = INVALID_SOCKET)
	{
		printf("Cannot initialize server\n");

		system("pause");
		return -1;
	}
		*/
	RunServer();
	
	//closesocket();
	WSACleanup();
	system("pause");
	return 0;
}

