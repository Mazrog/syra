//
// Created by mazrog on 23/10/17.
//

#include <syra/node.hpp>

#include <mutex>

using Guard = std::unique_lock<std::mutex>;

int main(){
    Node<> server;

    return 0;
}
