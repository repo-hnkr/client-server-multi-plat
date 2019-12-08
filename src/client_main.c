
#include "main.h"

int sockfd, new_fd;

//____________________________________________________________________________

int main( int argc, char** argv ) {
#ifdef __WIN32__
   WORD versionWanted = MAKEWORD(1, 1);
   WSADATA wsaData;
   WSAStartup( versionWanted, &wsaData );
#endif
    int res, quit = 0;
    char buffer[4096], ip[1024], port[64];

    memset( buffer, '\0', sizeof(buffer) );
    memset( ip, '\0', sizeof(ip) );
    memset( port, '\0', sizeof(port) );

    printf( DECORATOR_1 LF DECORATOR_2 TAB "Iniciando cliente..." TAB DECORATOR_2 LF DECORATOR_1 LF );
    printf( "Nodos de la red local:" );
    system( "arp -a" );

    if( argc > 1 ) {
        sprintf( ip, "%s", argv[1] );
        if( getIP( ip )) {
            printf( "IP incorrecta: [%s]" LF, ip );
            return 1;
        }
        if(argc==3) {
            sprintf( port, "%s", argv[2] );
        } else {
            sprintf( port, "%s", PUERTO );
        }
    } else {
        //do {
            do {
                printf( "Ingrese la IP del servidor: " );
                gets( buffer );
            } while( getIP( buffer ));
            sprintf( ip, "%s", buffer );
            
            printf( "Ingrese el puerto del servidor (enter para el default %s): ", PUERTO );
            res = gets( buffer );
            if(!res) {
                sprintf( port, "%s", buffer );
            } else {
                sprintf( port, "%s", PUERTO );
            }
        //} while (res = conectar( ip, port ) != -1);
    }

    // error de conexion -> res = -1
    res = conectar( ip, port );
    if( res == -1 ) {
        printf( "Error al conectarse al servidor [%s] y puerto [%s]: codigo [%d]\n", ip, port, res );
        return ERROR;
    }

    printf( "Conectando al servidor en IP [%s] y puerto [%s]: [%d]\n", ip, port, res );

    while( !quit ) {
        if( argc == 1 ) {
            printf( "> " );
            gets( buffer );
        } else {
            argc = 1;
        }

        if( !(quit = isExit( buffer )) ) {
            res = enviar( buffer );
            //printf( "[%d] = enviar: [%s]\n", res, buffer );

            if( res == -1 ) {
                printf( "Conexion cerrada con el servidor, codigo [%d]\n", res );
                break;
            } else if(res != strlen( buffer )) {
                printf( "Error enviando [%s], codigo [%d]\n", buffer, res );
                //printf( "Diferencia: enviado [%d] - entrada [%d]" LF, res, strlen(buffer) );
            } else {
                res = recibir( buffer );
                printf( "%s", buffer );
            }
        }
    }

    close(sockfd);

    printf( DECORATOR_1 LF DECORATOR_2 TAB "Cliente finalizado." TAB DECORATOR_2 LF DECORATOR_1 LF LF );

    return OK;
}//___________________________________________________________________________

int conectar( char * address, char* port ) {
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo( address, port, &hints, &res);
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    return connect(sockfd, res->ai_addr, res->ai_addrlen);
}//___________________________________________________________________________

int enviar( char* buffer ) {
    int len;

    len = strlen( buffer );
    return send( sockfd, buffer, len, 0 );
}//___________________________________________________________________________

int recibir( char * buffer ) {
    int ret;
    char tmp[4096];
    memset( tmp, '\0', sizeof(tmp) );

    ret = recv( sockfd, (void*) tmp, sizeof(tmp), 0 );
    sprintf( buffer, "%s", tmp );
    //printf( "[%d] - recv: [%s]" LF LF, ret, buffer );

    return ret;
}//___________________________________________________________________________

int getIP( char* dns ) {
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    if( !dns ) {
        return ERROR;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo( dns, NULL, &hints, &res)) != 0 ) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return ERROR;
    }

    printf("IP para %s:\n\n", dns );

    for(p = res;p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;

        // get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        // convert the IP to a string and print it:
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("  %s: %s\n", ipver, ipstr);
    }

    freeaddrinfo(res); // free the linked list

    return OK;
}//___________________________________________________________________________

int isExit( char* in ) {
    int ret = 0;
    if( !strcmp( in, "x" )) {
        ret = 1;
    } else if( !strcmp( in, "exit" )) {
        ret = 1;
    } else if( !strcmp( in, "quit" )) {
        ret = 1;
    }
    return ret;
}//___________________________________________________________________________

