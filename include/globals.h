
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#ifdef __linux__ 
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#elif _WIN32
#include <winsock2.h>
#include <WS2tcpip.h>
#else

#endif




#define OK              0
#ifdef ERROR
#undef ERROR
#endif
#define ERROR           1

#define CR              "\r"
#define LF              "\n"
#define CRLF            CR LF

#define DECORATOR_1     "***********************************************************"
#define DECORATOR_2     "***"
#define TAB             "\t"

#define PUERTO "8081"
#define BACKLOG 10

