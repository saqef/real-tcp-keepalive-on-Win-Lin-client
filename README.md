set real keepalive tcp connection

The difference from the server is the lack of a server :)
If you want using only socket on client you won't have "clientSocket->socketDescriptor();" -doesn't work.
If you can run server on client -no problem (server->socket->well done)

have tested on win 8.1/10 and ubuntu 16.04

add this code in function.

designed for Qt, but if you don't use it,just replace Qt's types for yours.

Yes, there is standart "keepalive" option but it check connection only one times per 2 hours. That's not enough.
