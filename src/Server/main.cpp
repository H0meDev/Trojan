#include "pch.h" 

#include "Application.hpp"

// #pragma comment (lib, "Mswsock.lib")
// #pragma comment(linker, "/MERGE:.rdata=.text")
// #pragma comment(linker, "/FILEALIGN:512 /SECTION:.text,EWRX /IGNORE:4078")
// #pragma comment(linker, "/ENTRY:WinMain")

int __cdecl main(int argc, char **argv)
{
	Application app;
	if (!app.init())
	{
		system("pause");
		return -1;
	}
		
	app.run();
	
	system("pause");
	return 0;
}

