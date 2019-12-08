
#include "main.h"

int sockfd, new_fd;

int main( int argc, char** argv ) {
    int res, quit = 0, con = 0;
    char buffer[4096];
    char output[0xffff];
    memset( buffer, '\0', sizeof(buffer) );
    memset( output, '\0', sizeof(output) );

    printf( DECORATOR_1 LF DECORATOR_2 TAB "Iniciando servidor..." TAB DECORATOR_2 LF DECORATOR_1 LF );
    exec( "hostname -I", buffer );
    printf( "Direccion IP del servidor para conexiones: %s", buffer );

    while( !quit ) {
        res = esperarConexion();
        if(res == OK) con = 1;
        while( con ) {
            memset( buffer, '\0', sizeof(buffer) );
            memset( output, '\0', sizeof(output) );
            res = recibir( buffer );
            //printf( "len[%d] Recibido del cliente:\n[%s]" LF, res, buffer );
            printf( "$ %s\n", buffer );
            if( res < 1 ) {
                printf( "Conexion cerrada con el cliente" LF );
                close( new_fd );
                con = 0;
                break;
            } else if( !(quit = isExit( buffer )) ) {
                if(exec( buffer, output )) {
                //if((res = system( buffer ))) {
                    printf( "Tipee Ctrl+C localmente o el comando remoto 'exit-server' para salir del programa." LF );
                }
                res = enviar( output );
                printf( "%s", output );
            } else {
                con = 0;
            }
        }
        close( sockfd );
    }
    
    close( new_fd );
    close( sockfd );

    printf( DECORATOR_1 LF DECORATOR_2 TAB "Servidor finalizado." TAB DECORATOR_2 LF DECORATOR_1 LF LF );

    return OK;
}//___________________________________________________________________________

int exec( const char* cmd, char* out ) {
    char buffer[1024];
    int res = OK;
    FILE* pipe = popen( cmd, "r" );
    if (!pipe) {
        pclose(pipe);
        return ERROR;
    }

    while (fgets(buffer, sizeof buffer, pipe) != NULL) {
        strcat( out, buffer );
    }

    //int l = strlen( out );
    //out[l] = '\0';

    pclose(pipe);
    return res;
}//___________________________________________________________________________

int enviar( char* buffer ) {
    int len;

    len = strlen( buffer );
    return send( new_fd, buffer, len, 0 );
}//___________________________________________________________________________

int esperarConexion() {
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    struct addrinfo hints, *res;
    char buffer[4096];
    memset( buffer, '\0', sizeof( buffer ));

    memset( &hints, 0, sizeof hints );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo( NULL, PUERTO, &hints, &res );

    sockfd = socket( res->ai_family, res->ai_socktype, res->ai_protocol );
    bind( sockfd, res->ai_addr, res->ai_addrlen );
    listen( sockfd, BACKLOG );

    addr_size = sizeof their_addr;
    new_fd = accept( sockfd, (struct sockaddr *)&their_addr, &addr_size );
    struct sockaddr_in addr;
    socklen_t addr_s = sizeof(struct sockaddr_in);
    getpeername( new_fd, (struct sockaddr *)&addr, &addr_s );
    strcpy( buffer, inet_ntoa(addr.sin_addr));
    printf( "Cliente conectado desde la IP [%s]\n", buffer );
    return OK;
}//___________________________________________________________________________

int recibir( char * buffer ) {
    int ret;
    char tmp[4096];
    memset( tmp, '\0', sizeof(tmp) );

    ret = recv( new_fd, (void*) tmp, sizeof(tmp), 0 );
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
        return 2;
    }

    //printf("Direccion IP del servidor para conexiones: [%s]\n", dns );

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

    return 0;
}

int isExit( char* in ) {
    int ret = 0;
    if( !strcmp( in, "exit-server" )) {
        ret = 1;
    }
    return ret;
}

