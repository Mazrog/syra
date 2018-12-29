//
// Created by mazrog on 05/02/18.
//

#include <syra/buffer.hpp>

#include <cstring>
#include <sys/socket.h>
#include <iostream>

Buffer::Buffer() {}

Buffer::~Buffer() {}

void Buffer::read(int fd) {
    char buffer[BUFFER_SIZE];
    bool end;
    unsigned i;

    bytes.clear();

    do {
        memset(buffer, 0, BUFFER_SIZE);
        recv(fd, buffer, BUFFER_SIZE, 0);

        i = 0;
        end = false;
        while( i < BUFFER_SIZE && !end ) {
            end = buffer[i++] == 0;
        }
        bytes.append(buffer, (end) ? i-1 : BUFFER_SIZE);
    } while( !end );
}

void Buffer::fromRequest(Request const& request) {
    bytes = request.data();
}

void Buffer::clear() {
    bytes.clear();
}

bool Buffer::empty() const {
    return bytes.empty();
}

int Buffer::size() const {
    return bytes.size();
}
