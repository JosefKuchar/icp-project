
#pragma once

#include <vector>
#include <string>

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

class MapInfo {
   public:
    std::vector<std::vector<Tile>> map;
    int width, height;
    MapInfo(std::string path);
};

