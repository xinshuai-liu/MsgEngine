#ifndef _PLATFORM_
#define _PLATFORM_

#include <sys/types.h>

typedef enum {
    localhost = 0,
    tcp = 31,
    udp = 32,
} ProtocolType;

typedef struct {
    int id;
} Network;


Network create_network(ProtocolType protocol, int port);
Network open_network(ProtocolType protocol, const char *ip, int port);
ssize_t read_network(Network network, void *buf, size_t len, int flags);
ssize_t write_network(Network network, const void *buf, size_t len, int flags);
int close_network(Network network);


#endif