# client-server-multi-plat
Cliente para Windows 10, servidor para Linux ubuntu 18.04 LTS, shell remoto de comandos simple

Para compilar en windows 10, instalar minGW (POSIX compliant environment):
https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download
Setear en la variable de entorno PATH la ruta al directorio bin, y dentro de bin renombrar el archivo mingw-*make.exe a -> make.exe
Con esto al abrir una consola debería reconocer el comando make

Para compilar en Windows 10: 
git checkout client
make client
./bin/client.exe

Para compilar en Linux Ubuntu 18.04LTS:
git checkout master
make server
./bin/server

Algunos links interesantes:

https://www.binarytides.com/winsock-socket-programming-tutorial/
https://beej.us/guide/bgnet/html//index.html
https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
