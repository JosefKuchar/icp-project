
#pragma once

#include <vector>
#include <string>

#include "boost_libs/boost/archive/text_iarchive.hpp"
#include "boost_libs/boost/archive/text_oarchive.hpp"

class InvalidMapException : public std::exception {
public:
  char *what() { return (char *)"Invalid map file"; }
};

class InvalidFileException : public std::exception {
    private:
        std::string msg;
    
    public:
        char* what() {
            return (char *)("Invalid file path: " + msg).c_str();
        }
        InvalidFileException(std::string path) {
            msg = path;
        }
};

enum class Tile {
    Empty, Wall, Player, Ghost, Key, Target
};

namespace boost {
    namespace serialization {
        template <class Archive>
        void serialize(Archive& ar, Tile& t, const unsigned int version) {
            ar& t;
        }
    }  // namespace serialization
}  // namespace boost

class MapInfo {
    private:
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive &a, const unsigned version) {
            a & map & width & height;
        };

    public:
        std::vector<std::vector<Tile>> map;
        int width, height;
        MapInfo();
        MapInfo(std::string path);
};

