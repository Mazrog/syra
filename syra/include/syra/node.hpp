//
// Created by mazrog on 21/10/17.
//

#ifndef NODE_HPP
#define NODE_HPP

#include <mutex>
#include <tuple>
#include <syra/utils/utils.hpp>
#include <syra/network/adapter.hpp>

template <typename ...Adapters>
class Node {
public:
    Node() {}
    ~Node() {}

    template < typename T >
    decltype(auto) operator()() {
        return std::get<T>(_adapters);
    }


    /* Mutex handling */
    std::mutex & mutex() {
        return data_guard;
    }

private:
    std::tuple<Adapters...>     _adapters;

    std::mutex                  data_guard;
};

#endif //FIRST_TEST_CLIENT_H
