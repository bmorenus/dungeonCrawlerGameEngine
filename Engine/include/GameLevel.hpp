#ifndef GAME_LEVEL_HPP
#define GAME_LEVEL_HPP

#include <string>
#include <vector>

class GameObject;

class GameLevel {
    std::string filename;
    std::vector<GameObject*> gameObjects;

    GameLevel(std::string _filename, std::vector<GameObject*> _gameObjects) {
        filename = _filename;
        gameObjects = _gameObjects;
    }
};

#endif