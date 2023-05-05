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
    width = 0;
    height = 0;
}

MapInfo::MapInfo(std::string path) {
    std::fstream newfile;
    newfile.open(path, std::ios::in);

    if (!newfile.is_open()) {
        throw InvalidFileException(path);
    }

    std::smatch matches;
    std::string line;

    int i;

    for (i = 0; getline(newfile, line); i++) {
        if (i == 0) {
            if (std::regex_search(line, matches, std::regex("^(\\d+) (\\d+)$"))) {
                width = std::stoi(matches[1]);
                height = std::stoi(matches[2]);
                continue;
            } else {
                throw InvalidMapException();
            }
        }

        if (line.size() != (long unsigned int)width) {
            throw InvalidMapException();
        }

        std::vector<Tile> line_vec;
        for (auto& c : line) {
            line_vec.push_back(to_tile(c));
        }

        map.push_back(line_vec);
    }
    if (i - 1 != height) {
        throw InvalidMapException();
    }
}
