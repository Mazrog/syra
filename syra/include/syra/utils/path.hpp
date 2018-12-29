#ifndef PATH_HPP
#define PATH_HPP

#include <vector>
#include <string>

using Path = std::vector<std::string>;

namespace PATH {
    bool valid_char(char c);

    bool valid_string(std::string const &string);

    Path getPath(std::string const &path);

    bool isApiCall(std::string const& path);

    bool fileExists(std::string const& file);
}

#endif