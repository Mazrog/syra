//
// Created by mazrog on 20/10/17.
//

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <syra/buffer.hpp>

#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Socket {
public:
    /* Constructors / Destructors */
    Socket(const char * host, uint16_t port);
    Socket(int file_descriptor);
    ~Socket();

    Socket(Socket const &s) = delete;
    Socket& operator=(Socket const& s) = delete;

    Socket(Socket && socket) = delete;
    Socket& operator=(Socket && s) = delete;

    /* Fonctions */
    int sock_send(std::string const& message);
    int sock_send(uint8_t * data, uint32_t size);
    std::string sock_receive();

    void sock_clean();

    /* Fonctions client */
    void sock_connect();

    /* Fonctions serveurs */
    void sock_listen();
    int sock_accept();
    int sock_select();

    /* Getters Setters */
    int get_ifstate() const { return _ifstate; }

private:
    uint16_t                    _port;

    int                         _socketfd;

    struct sockaddr_in          _hostAddr;
    struct hostent *            _host;
    struct sockaddr_storage     _recep;

    Buffer                      _buffer;

    /* STATE */
    int                         _ifstate;
};


#endif
