#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")
int main0()
{

    WORD version = MAKEWORD(2, 2);
    WSAData wsadata;
    WSAStartup(version, &wsadata);


    WSACleanup();

    return 0;
}