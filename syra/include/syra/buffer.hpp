//
// Created by mazrog on 05/02/18.
//

#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <string>
#include <syra/request.hpp>

constexpr unsigned BUFFER_SIZE = 512;

class Buffer {
public:
    Buffer();
    ~Buffer();

    void read(int fd);
    int readPRP(int fd);
    void fromRequest(Request const& request);
    void clear();

    bool empty() const;
    int size() const;

    std::string const& getBytes() const { return bytes; }

private:
    std::string     bytes;
};


#endif //FIRST_TEST_BUFFER_HPP
