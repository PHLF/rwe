#ifndef RWE_VIRTUALFILESYSTEM_H
#define RWE_VIRTUALFILESYSTEM_H

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace rwe
{
    class AbstractVirtualFileSystem
    {
    public:
        virtual ~AbstractVirtualFileSystem() = default;
        virtual boost::optional<std::vector<char>> readFile(const std::string& filename) const = 0;
    };
}

#endif
