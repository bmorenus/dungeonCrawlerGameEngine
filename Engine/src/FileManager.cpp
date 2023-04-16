#include "FileManager.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "GameObject.hpp"

int TAG_INDEX = 0;
int X_POS_INDEX = 1;
int Y_POS_INDEX = 2;
int WIDTH_INDEX = 3;
int HEIGHT_INDEX = 4;

FileManager::FileManager() {
    std::cout << "File Manager Created" << std::endl;
}

FileManager::FileManager(FileManager const&) {
}

FileManager::~FileManager() {
    std::cout << "File Manager Destroyed" << std::endl;
}

FileManager& FileManager::GetInstance() {
    static FileManager* sInstance = new FileManager();
    return *sInstance;
}

void FileManager::Initialize() {
}

int FileManager::SaveLevel(std::string filename,
                           std::vector<std::vector<std::string>> gameLevelData) {
    std::fstream gameFile;

    gameFile.open(FILE_PATH + filename + FILE_EXT, std::ios::out);

    if (!gameFile) {
        return 1;
    }

    for (std::vector<std::string> gameObjectData : gameLevelData) {
        gameFile << gameObjectData.at(TAG_INDEX) << std::endl;
        gameFile << gameObjectData.at(X_POS_INDEX) << std::endl;
        gameFile << gameObjectData.at(Y_POS_INDEX) << std::endl;
        gameFile << gameObjectData.at(WIDTH_INDEX) << std::endl;
        gameFile << gameObjectData.at(HEIGHT_INDEX) << std::endl;
    }

    gameFile.close();
    return 0;
}

std::vector<std::vector<std::string>> FileManager::LoadLevel(std::string filename) {
    std::fstream gameFile;

    gameFile.open(FILE_PATH + filename + FILE_EXT, std::ios::in);
    std::vector<std::vector<std::string>> gameLevelData;

    if (gameFile.is_open()) {
        std::cout << "gamefile is open" << std::endl;
        while (!gameFile.eof()) {
            std::string tag;
            std::string xPos;
            std::string yPos;
            std::string width;
            std::string height;
            getline(gameFile, tag);
            getline(gameFile, xPos);
            getline(gameFile, yPos);
            getline(gameFile, width);
            getline(gameFile, height);
            std::cout << tag << std::endl;

            std::vector<std::string> gameObjectData;

            gameObjectData.push_back(tag);
            gameObjectData.push_back(xPos);
            gameObjectData.push_back(yPos);
            gameObjectData.push_back(width);
            gameObjectData.push_back(height);

            gameLevelData.push_back(gameObjectData);
        }
    }
    std::cout << gameLevelData.size() << std::endl;

    gameFile.close();
    return gameLevelData;
}
