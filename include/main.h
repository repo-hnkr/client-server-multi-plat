#ifndef _MAIN_H
#define _MAIN_H

#include "globals.h"

int isExit( char* in );
int getIP( char* dns );
int conectar( char * address, char* port );
int esperarConexion();
int enviar( char* buffer );
int recibir( char * buffer );
int exec( const char* cmd, char* out );

#endif //_MAIN_H
