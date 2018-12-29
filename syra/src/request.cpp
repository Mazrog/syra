//
// Created by mazrog on 01/11/17.
//

#include <syra/request.hpp>
#include <syra/utils/utils.hpp>

Request::Request() : _bytes() {}

Request::~Request() {}

void Request::fromBytes(std::string const&) {}

void Request::clear() {
    _bytes.clear();
    _rel_path.clear();
}

std::string const& Request::getRelPath() const { return _rel_path; }
std::string const& Request::getBytes() const { return _bytes; }