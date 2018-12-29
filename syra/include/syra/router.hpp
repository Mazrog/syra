//
// Created by mazrog on 11/01/18.
//

#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <string>
#include <unordered_map>
#include <functional>

#include <syra/request.hpp>
#include <syra/utils/utils.hpp>

class Router {
    using Behaviour = std::function<void(const Request *, Request *)>;
    using ApiTree = std::unordered_map<std::string, Behaviour>;

public:
    Router();
    ~Router();

    void on(const char * path, Behaviour const& behaviour);

    template < class R >
    void operator()(R const&, R &) {}

private:
    ApiTree         apiTree;
};


#endif