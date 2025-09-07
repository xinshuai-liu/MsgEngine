#include "platform.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Network create_network(ProtocolType protocol, int port) {

    Network  network;
    network.id = -1;

    switch (protocol)
    {
        case tcp: 
        {
            network.id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (network.id < 0) 
            {
                puts("openNetworkInterface: tcp: error");
                exit(1);
            }

            struct sockaddr_in address;
            memset(&address, 0, sizeof(address));
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = INADDR_ANY;
            address.sin_port = htons(port);

            if (bind(network.id, (struct sockaddr *)&address, sizeof(address)) < 0) 
            {
                perror("bind failed");
                exit(EXIT_FAILURE);
            }

            if (listen(network.id, 3) < 0) {
                perror("listen");
                exit(EXIT_FAILURE);
            }

            printf("Server listening on port %d...\n", port);


            break;
        }
        default:
            puts("unknown");
        break;
    }
    return network;
}

Network open_network(ProtocolType protocol, const char *ip, int port) {
    Network  network;
    network.id = -1;

    switch (protocol)
    {
        case tcp: 
        {
            network.id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (network.id < 0) 
            {
                puts("openNetworkInterface: tcp: error");
                exit(1);
            }

            struct sockaddr_in address;
            memset(&address, 0, sizeof(address));
            address.sin_family = AF_INET;
            address.sin_port = htons(port);
            address.sin_addr.s_addr = inet_addr(ip);

            if (connect(network.id, (struct sockaddr *)&address, sizeof(address)) < 0) 
            {
                perror("bind failed");
                exit(EXIT_FAILURE);
            }

            printf("connect to %s:8080\n\n", ip);


            break;
        }
        default:
            puts("unknown");
        break;
    }
    return network;
}

int close_network(Network network) {
    return close(network.id);
}

ssize_t read_network(Network network, void *buf, size_t len, int flags) {
    return recv(network.id, buf, len, flags);
}

ssize_t write_network(Network network, const void *buf, size_t len, int flags) {
    return send(network.id, buf, len, 0);
}