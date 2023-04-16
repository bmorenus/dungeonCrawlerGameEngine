#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <vector>

/*!
 * Singleton FileManager class that manages file processing in the game engine
 */
class FileManager {
   public:
    /*!
     * Returns the singleton instance of the FileManager class for the game engine
     */
    static FileManager& GetInstance();

    /*!
     * Performs all initializing functions for the FileManager class
     */
    void Initialize();

    /*!
     * Saves the currently created level of in the SceneManager to the local directory
     */
    int SaveLevel(std::string filename, std::vector<std::vector<std::string>> gameLevel);

    /*!
     * Loads the provided level name to the SceneManager from the local directory
     */
    std::vector<std::vector<std::string>> LoadLevel(std::string filename);

    std::string FILE_PATH = "./LevelFiles/";
    std::string FILE_EXT = ".gamefile";

   private:
    /*!
     * Constructor Function for the FileManager class
     */
    FileManager();

    /*!
     * Destructor Function for the FileManager class
     */
    ~FileManager();

    FileManager(FileManager const&);

    void operator=(FileManager const&);
};

#endif
