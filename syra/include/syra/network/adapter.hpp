//
// Created by mazrog on 23/10/17.
//

#ifndef ADAPTER_HPP
#define ADAPTER_HPP

#include <syra/network/subif.hpp>
#include <syra/request.hpp>

#include <thread>
#include <unordered_map>
#include <iostream>

template < class Children >
class Adapter{
public:
    using Type = Children;
    using sub_ifs_map = std::unordered_map<std::string, Type *>;

    Adapter() {}

    virtual ~Adapter() {
        for(auto subif: _subifs){
            delete subif.second;
        }

        _subifs.clear();
    }

    void show_state() const {
        std::cout << "\nListe des sous-interfaces : " << std::endl;

        for(auto const& subif: _subifs){
            static_cast<Type *>(subif.second)->show_state();
        }
    }

protected:
    Type * get_interface(const char * tag) {
        return static_cast<Type *>(_subifs.at(tag));
    }

    void listen(const char * tag, uint16_t port, volatile bool * running) {
        if(_subifs.find(tag) == _subifs.end()) {
            Type * tmp = new Type(tag, NULL, port);
            _subifs[tag] = tmp;

            std::thread t{&Type::listen, tmp, _router, running};
            t.detach();
        } else {
            std::cerr << "Deux interfaces déclarées avec le même nom : " << tag << EOL;
            std::cerr << "Annulation de la seconde..." << std::endl;
        }
    }

    void connect(const char * tag, const char * host, uint16_t port) {
        if(_subifs.find(tag) == _subifs.end()) {
            Type * tmp = new Type(tag, host, port);
            tmp->connect();

            _subifs[tag] = tmp;
        } else {
            std::cerr << "Deux interfaces déclarées avec le même nom : " << tag << EOL;
            std::cerr << "Annulation de la seconde..." << std::endl;
        }
    }

    void send(const char * tag, std::string const& bytes) {
        if(_subifs.find(tag) != _subifs.end()) {
            _subifs[tag]->send(bytes);
        } else {
            std::cerr << "Tag de sous interface non trouvé : " << tag << EOL;
        }
    }

protected:
    sub_ifs_map           _subifs;
    Router              * _router;
};


#endif
