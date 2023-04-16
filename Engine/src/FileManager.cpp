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
    /*!
     * Singleton FileManager class that manages file processing in the game engine
     */
    std::cout << "File Manager Created" << std::endl;
}

FileManager::FileManager(FileManager const&) {
}

FileManager::~FileManager() {
    /*!
     * Destructor Function for the FileManager class
     */
    std::cout << "File Manager Destroyed" << std::endl;
}

FileManager& FileManager::GetInstance() {
    /*!
     * Returns the singleton instance of the FileManager class for the game engine

     * Arguments: None
     * Returns: FileManager&, the instance of the FileManager class
     */
    static FileManager* sInstance = new FileManager();
    return *sInstance;
}

void FileManager::Initialize() {
    /*!
     * Performs all initializing functions for the FileManager class
     * Arguments: None
     * Returns: void
     */
}

int FileManager::SaveLevel(std::string filename,
                           std::vector<std::vector<std::string>> gameLevelData) {
    /*!
     * Saves the currently created level of in the SceneManager to the local directory
     * Arguments: string, the filename of the level
     *            std::vector<std::vector<std::string>>, the game data for all
     *              game objects in the level
     * Returns: int, success/failure notification
     */
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
    /*!
     * Loads the provided level name to the SceneManager from the local directory
     *
     * Arguments: string, the filename of the desired level
     * Returns: std::vector<std::vector<std::string>>, encoded game object data
     *   for the level
     */
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
