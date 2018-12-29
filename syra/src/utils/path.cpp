#include <syra/utils/path.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

namespace PATH {
    bool valid_char(char c) {
        return (c > 'A' && c < 'Z') || (c > '0' && c < '9')
               || (c > 'a' && c < 'z') || (c == '-') || (c == '_');
    }

    bool valid_string(std::string const &) {
        bool res = true;
//    unsigned i = 0, n = string.size();
//    while ( res && i < n ) {
//        res = valid_char(string.at(i));
//    }
        return res;
    }

    Path getPath(std::string const &path_string) {
        Path path;
        std::istringstream iss(path_string);
        std::string tmp;
        iss.ignore(1, '/');

        while ( iss.good() ) {
            tmp.clear();
            std::getline(iss, tmp, '/');
            if (valid_string(tmp)) {
                path.push_back(tmp);
            } else {
                throw std::runtime_error("Invalid path");
            }
        }

        return path;
    }

    bool isApiCall(std::string const& path){
        std::istringstream iss(path);
        iss.ignore(1, '/');

        std::string option;
        std::getline(iss, option, '/');
        return option == "api";
    }

    bool fileExists(std::string const& file) {
        std::ifstream iss(file);
        return iss.is_open();
    }
}