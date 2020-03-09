#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <WinSock2.h>
#include <stdio.h>

#include "Common.h"
#pragma comment(lib,"ws2_32.lib")
int main()
{

    WORD version = MAKEWORD(2, 2);
    WSAData wsadata;
    WSAStartup(version, &wsadata);


    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4567);
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    if (SOCKET_ERROR == bind(sock, (sockaddr*)&addr, sizeof(addr))) {
        printf("bind failed!\n");
    }
    else
    {
        printf("bind success!\n");
    }

 
    if (SOCKET_ERROR == listen(sock, 5)) {
        printf("listen failed!\n");
    }
    else
    {
        printf("listen success!\n");
    }


    sockaddr_in clientAddr = {};
    int nAddrLen = sizeof(clientAddr);

    SOCKET clientSock = INVALID_SOCKET;
    char msgBuf[] = "Hello From Server!";

    while (true)
    {
        clientSock = accept(sock, (sockaddr*)&clientAddr, &nAddrLen);

        if (INVALID_SOCKET == clientSock) {
            printf("accept failed!\n");
        }
        else
        {
            printf("accept success!\n");
        }
        printf("new client join:%s\n", inet_ntoa(clientAddr.sin_addr));
        send(clientSock, msgBuf, strlen(msgBuf) + 1, 0);
        closesocket(clientSock);
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}