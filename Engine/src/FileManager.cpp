#include "FileManager.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "GameObject.hpp"

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

int FileManager::SaveLevel(std::string filename, GameLevel* gameLevel) {
    std::fstream gameFile;

    gameFile.open(FILE_PATH + filename + FILE_EXT, std::ios::out);

    if (!gameFile) {
        return 1;
    }

    for (GameObject* gameObject : gameLevel->gameObjects) {
        std::cout << gameObject->GetTag() << std::endl;
        gameFile << gameObject->GetTag() << std::endl;
        gameFile << gameObject->GetX() << std::endl;
        gameFile << gameObject->GetY() << std::endl;
        gameFile << gameObject->GetWidth() << std::endl;
        gameFile << gameObject->GetHeight() << std::endl;
        gameFile << "---" << std::endl;
    }

    gameFile.close();
    return 0;
}
