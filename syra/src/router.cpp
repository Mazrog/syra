//
// Created by mazrog on 11/01/18.
//

#include "../include/syra/router.hpp"

#include <iostream>

Router::Router() {}

Router::~Router() {}

void Router::on(const char *path, Behaviour const& behaviour) {
    auto it = apiTree.find(path);
    if ( it == apiTree.end() ) {
        apiTree[path] = behaviour;
    } else {
        std::cerr << "You tried to mount two behaviours on the same entry point : " << path << std::endl;
        throw std::runtime_error("Router tree error");
    }
}