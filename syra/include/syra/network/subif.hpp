//
// Created by mazrog on 21/10/17.
//

#ifndef SUBIF_HPP
#define SUBIF_HPP

#include <syra/utils/utils.hpp>
#include <syra/network/socket.hpp>
#include <syra/router.hpp>

#include <set>
#include <thread>
#include <iostream>

using sockList = std::set<Socket *>;

template < class Request >
class SubIf {
public:
    using ReqType = Request;

public:
    SubIf(const char * tag, const char * host, uint16_t port) :
            _tag(tag), _host(host), _port(port),
            _mainSocket(new Socket(host, port)), _sockets() {}

    virtual ~SubIf() {
        for(auto sock : _sockets) {
            delete sock;
        }
        delete _mainSocket;
    }

protected:
    virtual void show_state() {
        std::cout << " open connection : \"" << _tag << "\"" << "\t\tSTATE : " << std::flush;
        get_state_info(_mainSocket->get_ifstate());
        std::cout << "Host : \"" << _host << "\"" << "\t";
        std::cout << "Port : " << _port << std::endl << std::endl;
    }

public:
    void send(std::string const& bytes) {
        _mainSocket->sock_send(bytes);
    }

    void connect() { _mainSocket->sock_connect(); }

    void listen(Router * router, volatile bool * running) {
        _mainSocket->sock_listen();
        int newfd = 0;

        LOG_DEBUG("Attente de connexion");

        /* Appel bloquant à accept */
        while ( *running ) {
            if ( _mainSocket->sock_select() ) {
                newfd = _mainSocket->sock_accept();
                std::thread([this, newfd, router, running]() {
                    this->handleSocket(newfd, router, running);
                }).detach();
            }
        }

        LOG_DEBUG("Connexion terminée");
    }

    virtual void handleSocket(int fd, Router * router, volatile bool * running) {
        Buffer buffer;
        ReqType request, response;

        /* Création de la socket de connexion */
        Socket * socket = new Socket(fd);
        _sockets.insert(socket);

        while ( *running ) {
            request.clear();
            response.clear();
            buffer.clear();

            /* Chargement dans un buffer du contenu reçu */
            buffer.read(fd);

            if ( !buffer.empty() ) {

                /* Création de la requête à partir des données du buffer */
                request.fromBytes(buffer.getBytes());

                /* Application du comportement serveur => modification de la requête réponse */
                (*router)(request, response);

                /* On vide le buffer */
                buffer.clear();
                /* On le remplit avec les données de la requête réponse */
                buffer.fromRequest(response);

                /* On envoie les données du buffer via la socket */
                socket->sock_send(buffer.getBytes());
            }
        }
        _sockets.erase(socket);
    }

    void get_state_info(int ifstate) const {
        if(ifstate) { std::cout << "DOWN (ERR_CODE: " << ifstate << ")"; }
        else { std::cout << "UP"; }
        std::cout << std::endl;
    }


protected:
    const char      * _tag;
    const char      * _host;
    uint16_t          _port;

    Socket     * _mainSocket;
    sockList     _sockets;
};

#endif
