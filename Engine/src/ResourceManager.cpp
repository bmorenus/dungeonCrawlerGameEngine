#include "ResourceManager.hpp"
#include <iterator>
#include <iostream>
#include <unordered_map>
#include <string>

ResourceManager::ResourceManager(){
    std::cout << "Created" << std::endl;
}

ResourceManager::ResourceManager(ResourceManager const&){
}

ResourceManager::~ResourceManager(){
    std::cout << "Destroyed" <<  std::endl; 
}

ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager* s_instance = new ResourceManager;
    return *s_instance;
}

void ResourceManager::Initialize(std::string imageDirPath) {
    for (const auto & imageFileEntry : std::filesystem::directory_iterator(imageDirPath)) {
        ResourceManager::GetInstance().LoadResource(imageFileEntry.path());
    }
}

void ResourceManager::LoadResource(std::string imageFilename){
    std::unordered_map<std::string, std::shared_ptr<SDL_Surface>>::iterator it; 
    it = mResourceMap.find(imageFilename);

    if (it == mResourceMap.end()) {
        SDL_Surface* spriteSheet = SDL_LoadBMP(imageFilename.c_str());
        std::shared_ptr<SDL_Surface> spriteSheetPtr = 
            std::make_shared<SDL_Surface>(*spriteSheet);

        mResourceMap.insert({imageFilename, spriteSheetPtr});

        std::cout << "New copy of " << imageFilename << " has been loaded\n";
    } else {
        std::cout << "Resource has already been loaded\n"; 
    }
}

std::shared_ptr<SDL_Surface> ResourceManager::GetResource(std::string imageFilename){
    std::unordered_map<std::string, std::shared_ptr<SDL_Surface>>::iterator it; 
    it = mResourceMap.find(imageFilename);

    if (it != mResourceMap.end()) {
        std::cout << "Retrieved saved copy of " << imageFilename << " from GetResource\n"; 
        return it->second;
    } else {
        std::cout << "The desired SDL_Surface has not yet been loaded.\n";
        return NULL;
    }
}
