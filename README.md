# HTTP_server
HTTP server on C++

Write an HTTP 1.1 server in C++ 98

External functs:
htons, htonl, ntohs, ntohl, select, poll,
epoll (epoll_create, epoll_ctl, epoll_wait),
kqueue (kqueue, kevent), socket,
accept, listen, send, recv, bind, connect,
inet_addr, setsockopt, getsockname, fcntl

Implemented methods - GET, POST, and DELETE;

Server can listen on multiple ports;

Server support cookies and Session management;

Server can Handle multiple CGI;

Server is non-blocking and use only 1 poll (or equivalent)
for all the IO between the client and the server;
# Build
- make

# Usage
- ./webserv

open in browser: 
http://localhost:9000/
http://localhost:9001/
http://localhost:9002/
http://localhost:9003/
http://localhost:9004/
http://localhost:9005/

- bash siege
(stress test)
# Correction
correction config in config/webserv.conf
config same as Nginx