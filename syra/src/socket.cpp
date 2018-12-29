//
// Created by mazrog on 20/10/17.
//

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cassert>
#include <netdb.h>

#include <syra/utils/utils.hpp>
#include <syra/network/socket.hpp>
#include <syra/buffer.hpp>

Socket::Socket(const char *host, uint16_t port) : _port(port), _ifstate(0) {
    if(host) {
        /* Resolving host */
        std::cout << "Resolving host \"" << host << "\"..." << std::flush;
        _host = gethostbyname(host);
        if (!_host) {
            std::cout << "[FAIL]" << std::endl;
            _ifstate = 1;
            error("Resolving hostname : ");
        }
        std::cout << "[OK]" << std::endl;
    }

    /* Creating the socket */
    int domain = AF_INET;

    /* Setting the host configuration */
    memset(&_hostAddr, 0, sizeof(_hostAddr));
    _hostAddr.sin_family = static_cast<sa_family_t>(domain);
    _hostAddr.sin_port = htons(port);

    /* SOCK_STREAM => TCP      */
    _socketfd = socket(domain, SOCK_STREAM, 0);
    if(!_socketfd){
        std::cout << "Cannot create socket (host : \"" << host << "\", port : " << port << ")" << std::endl;
        _ifstate = 2;
        error("Creating socket : ");
    }
    int enable = 1;
    setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
}

Socket::Socket(int file_descriptor) : _socketfd(file_descriptor) {}

Socket::~Socket() {
    sock_clean();
}


void Socket::sock_clean() {
    if(_socketfd) {
        close(_socketfd);
    }
}

void Socket::sock_connect() {
    /* Finalizing the host configuration */
    memcpy((char *) &_hostAddr.sin_addr.s_addr,
            _host->h_addr,
            (size_t) _host->h_length);

    /* Connecting the socket */
    int ret = connect(_socketfd, (const sockaddr *) &_hostAddr, sizeof(struct sockaddr_in));
    if(ret < 0){
        std::cerr << "Cannot connect socket to (host : \"" << _host->h_name << "\", port : " << _port << ")" << std::endl;
        _ifstate = 3;
        error("Connection error");
    }
}

void Socket::sock_listen() {
    /* Finalizing the host configuration */
    _hostAddr.sin_addr.s_addr = INADDR_ANY;

    /* Binding the socket */
    int ret = bind(_socketfd, (const sockaddr *) &_hostAddr, sizeof(struct sockaddr_in));
    if(ret < 0){
        std::cout << "Cannot bind the socket (host : \"" << _host << "\", port : " << _port << ")" << std::endl;
        _ifstate = 4;
    }

    /* Starts listening */
    if( listen(_socketfd, 5) < 0 ) {
        error("ERROR on listening");
    }
}

int Socket::sock_accept() {
    int recep_len, newfd = 0;
    /* Accepting the connection */
    newfd = accept(_socketfd,
                        (struct sockaddr *) &_recep,
                            (socklen_t *) &recep_len);

    if ( newfd <= 0 ) {
        error("ERROR on accept");
    }

    return newfd;
}

int Socket::sock_select() {
    fd_set readset;
    int result;

    FD_ZERO(&readset);
    FD_SET(_socketfd, &readset);

    struct timeval t{0, 200};

    result = select(_socketfd + 1, &readset, NULL, NULL, &t);

    if ( result < 0 ) {
        error("Error on select()");
    }

    return FD_ISSET(_socketfd, &readset);
}

int Socket::sock_send(std::string const& message) {
    if ( send(_socketfd, message.c_str(), message.size(), 0) < 0) {
        error("Socket send");
        return 1;
    }
    return 0;
}

int Socket::sock_send(uint8_t * data, uint32_t size) {
    if ( send(_socketfd, data, size, 0) < 0) {
        error("Socket send");
        return 1;
    }
    return 0;
}

std::string Socket::sock_receive() {
    _buffer.clear();
    _buffer.read(_socketfd);
    return _buffer.getBytes();
}