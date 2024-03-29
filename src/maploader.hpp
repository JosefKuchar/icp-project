/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file maploader.hpp
 * @brief Map loader header
 */

#pragma once

#include <string>
#include <vector>

#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"

/**
 * @brief Invalid map exception
 */
class InvalidMapException : public std::exception {
   public:
    char* what() { return (char*)"Invalid map file"; }
};

/**
 * @brief Invalid file exception
 */
class InvalidFileException : public std::exception {
   private:
    std::string msg;

   public:
    char* what() { return (char*)("Invalid file path: " + msg).c_str(); }
    InvalidFileException(std::string path) { msg = path; }
};

/**
 * @brief Map tile
 */
enum class Tile { Empty, Wall, Player, Ghost, Key, Target };

/**
 * @brief Map info
 */
class MapInfo {
   private:
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive& a, [[maybe_unused]] const unsigned version) {
        a& map& width& height;
    };

   public:
    std::vector<std::vector<Tile>> map;
    int width, height;
    MapInfo();
    MapInfo(std::string path);
};
