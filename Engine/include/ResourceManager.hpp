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

class ResourceManager {
   public:
    static ResourceManager& GetInstance();

    void LoadResource(std::string imageFilename);

    std::shared_ptr<SDL_Surface> GetResource(std::string imageFilename);

    void Initialize(std::string imageDirPath);

   private:
    ResourceManager();

    ~ResourceManager();

    ResourceManager(ResourceManager const&);

    void operator=(ResourceManager const&);

    SDL_Surface* mSpriteSheet;

    std::unordered_map<std::string, std::shared_ptr<SDL_Surface>> mResourceMap;
};

#endif
