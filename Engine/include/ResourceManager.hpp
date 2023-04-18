#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

/*!
 * Singleton ResourceManager class that manages resources for the game engine
 */
class ResourceManager {
   public:
    /*!
     * Returns the singleton instance of the ResourceManager class for the game engine
     */
    static ResourceManager& GetInstance();

    /*!
     * Loads the images in the provided directory to the resource manager
     */
    void LoadResource(std::string imageFilename);

    /*!
     * Returns the desired resource from the resource manager
     */
    std::shared_ptr<SDL_Surface> GetResource(std::string imageFilename);

    /*!
     * Performs all initializing functions for the ResourceManager class
     */
    void Initialize(std::string imageDirPath);

   private:
    /*!
     * Constructor Function for the ResourceManager class
     */
    ResourceManager();

    /*!
     * Destructor Function for the ResourceManager class
     */
    ~ResourceManager();

    ResourceManager(ResourceManager const&);

    void operator=(ResourceManager const&);

    SDL_Surface* mSpriteSheet;

    std::unordered_map<std::string, std::shared_ptr<SDL_Surface>> mResourceMap;
};

#endif
