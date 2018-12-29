//
// Created by mazrog on 01/11/17.
//

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "utils/path.hpp"
#include "utils/utils.hpp"

constexpr char EOL[] = "\r\n";

class Request {
public:
    Request();
    virtual ~Request();

    virtual const std::string data() const = 0;
    virtual void fromBytes(std::string const& bytes);
    virtual void clear();
    virtual void notFound() = 0;

    virtual void sendJSON(std::string const&) {}

    std::string const& getRelPath() const;
    std::string const& getBytes() const;

protected:
    std::string       _bytes;
    std::string       _rel_path;
};


#endif
