#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else 
    #include <SDL.h>
#endif

#include <unordered_map>
#include <string>
#include <memory>

class ResourceManager{

public:
    static ResourceManager& GetInstance();

    void LoadResource(std::string image_filename);
    
    std::shared_ptr<SDL_Surface> GetResource(std::string image_filename);

    int StartUp();

private:
	ResourceManager();

    ~ResourceManager();
    
    ResourceManager(ResourceManager const&);

    void operator=(ResourceManager const&);
    
    SDL_Surface* mSpriteSheet;

    std::unordered_map<std::string, std::shared_ptr<SDL_Surface>> mResourceMap;
};


#endif
