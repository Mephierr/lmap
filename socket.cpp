#include "socket.h"
#include <fcntl.h>
namespace sock {
int initializeSockets(){
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1,1), &wsa_data);
#else
    return 0;
#endif
}
int destroySockets() {
#ifdef _WIN32
    return WSACleanup();
#else
    return 0;
#endif
}
int socketInit(int af, int type, int protocol) {
    return socket(af, type, protocol);
}
int socketInitNonblock(int af, int type, int protocol) {
#ifdef _WIN32
    int sock = socket(af, type, protocol);
    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);
    return sock;
#else
    return socket(af, type | SOCK_NONBLOCK, protocol);
#endif
}
void socketDestroy(int socket) {
    close(socket);
}
bool isFailure(int sock) {
#ifdef _WIN32
    return sock == SOCKET_ERROR;
#else
    return sock == -1;
#endif
}
void setsockopt(int sock,
                int level,
                int optname,
                const void* optval, int optlen) {
#ifdef _WIN32
    setsockopt(sock, level, optname, (const char*) optval, optlen);
#else
    setsockopt(sock, level, optname, optval, optlen);
#endif
}
void getsockopt(int sock,
               int level,
               int optname,
               void* optval,
               int* optlen) {
    getsockopt(sock, level, optname, optval, optlen);
}
void getsockopt(int sock,
               int level,
               int optname,
               void* optval,
               unsigned int* optlen) {
    getsockopt(sock, level, optname, optval, optlen);
}
}
