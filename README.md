# client-server-multi-plat
<h2>Cliente para Windows 10, servidor para Linux ubuntu 18.04 LTS, shell remoto de comandos simple</h2>

<p>Para compilar en windows 10, instalar minGW (POSIX compliant environment):</p>
<a href="https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download">Download minGW</a>
<p>Setear en la variable de entorno PATH la ruta al directorio bin, y dentro de bin renombrar el archivo mingw-*make.exe a -> make.exe</p>
<p>Con esto al abrir una consola debería reconocer el comando make</p>
<br>
<h4>Para compilar en Windows 10:</h4>
<p>git checkout client</p>
<p>make client</p>
<p>./bin/client.exe</p>

<h4>Para compilar en Linux Ubuntu 18.04LTS:</h4>
<p>git checkout master</p>
<p>make server</p>
<p>./bin/server</p>

<h4>Algunos links interesantes:</h4>

<a href="https://www.binarytides.com/winsock-socket-programming-tutorial/">Programing tutorial winsock</a>
<a href="https://beej.us/guide/bgnet/html//index.html">C sockets</a>
<a href="https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/">tcp client server implementation</a>
