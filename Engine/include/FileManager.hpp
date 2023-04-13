#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <vector>

#include "GameLevel.hpp"

class FileManager {
   public:
    static FileManager& GetInstance();

    void Initialize();

    int SaveLevel(std::string filename, GameLevel* gameLevel);

    std::string FILE_PATH = "./LevelFiles/";
    std::string FILE_EXT = ".gamefile";

   private:
    FileManager();

    ~FileManager();

    FileManager(FileManager const&);

    void operator=(FileManager const&);
};

#endif
