#ifndef SOCKET_H
#define SOCKET_H

#ifdef _WIN32
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0501
    #endif
    #include <winsock.h>
    #include <winsock2.h>
    #include <Ws2tcpip.h>
#else
    /* Assume that any non-Windows platform uses POSIX-style sockets instead. */
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
    #include <unistd.h> /* Needed for close() */
#endif

namespace sock {
    int initiailizeSockets();
    int destroySockets();
    int socketInit(int af, int type, int protocol);
    int socketInitNonblock(int af, int type, int protocol);
    void socketDestroy();
    void setsockopt(int sock,
                    int level,
                    int optname,
                    const void* optval, int optlen);
    void getsockopt(int sock,
                   int level,
                   int optname,
                   void* optval,
                   int* optlen);
    void getsockopt(int sock,
                   int level,
                   int optname,
                   void* optval,
                   unsigned int* optlen);
}
#endif
