/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file maploader.cpp
 * @brief Map loader implementation
 */

#include "maploader.hpp"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

/**
 * @brief Convert char to tile enum
 * @param c Char
 *
 * Throws InvalidMapException if char is invalid
 */
constexpr auto to_tile(char c) {
    switch (c) {
        case 'T':
            return Tile::Target;
        case 'X':
            return Tile::Wall;
        case 'G':
            return Tile::Ghost;
        case 'K':
            return Tile::Key;
        case '.':
            return Tile::Empty;
        case 'S':
            return Tile::Player;
        default:
            throw InvalidMapException();
    }
}

MapInfo::MapInfo() {
    this->width = 0;
    this->height = 0;
}

MapInfo::MapInfo(std::string path) {
    // Open file
    std::fstream newfile;
    newfile.open(path, std::ios::in);

    // If file does not exist, throw exception
    if (!newfile.is_open()) {
        throw InvalidFileException(path);
    }

    std::smatch matches;
    std::string line;
    int i;

    // Read file line by line
    for (i = 0; getline(newfile, line); i++) {
        // First line contains map dimensions
        if (i == 0) {
            // Parse dimensions with regex
            if (std::regex_search(line, matches, std::regex("^(\\d+) (\\d+)$"))) {
                this->width = std::stoi(matches[1]);
                this->height = std::stoi(matches[2]);
                continue;
                // If regex does not match, throw exception
            } else {
                throw InvalidMapException();
            }
        }
        // Line width does not match map width, throw exception
        if (line.size() != (long unsigned int)width) {
            throw InvalidMapException();
        }
        // Parse line
        std::vector<Tile> line_vec;
        for (auto& c : line) {
            line_vec.push_back(to_tile(c));
        }
        // Add line to map
        map.push_back(line_vec);
    }
    // Height does not match map height, throw exception
    if (i - 1 != height) {
        throw InvalidMapException();
    }
}
