#include "ResourceManager.hpp"

#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>

ResourceManager::ResourceManager() {
    /*!
     * Singleton ResourceManager class that manages resources for the game engine
     */
    std::cout << "Resource Manager Created" << std::endl;
}

ResourceManager::ResourceManager(ResourceManager const&) {
}

ResourceManager::~ResourceManager() {
    /*!
     * Destructor Function for the ResourceManager class
     */
    std::cout << "Resource Manager Destroyed" << std::endl;
}

ResourceManager& ResourceManager::GetInstance() {
    /*!
     * Returns the singleton instance of the ResourceManager class for the game engine
     * Arguments: None
     * Returns: ResourceManager&, the instance of the ResourceManager class
     */
    static ResourceManager* s_instance = new ResourceManager;
    return *s_instance;
}

void ResourceManager::Initialize(std::string imageDirPath) {
    /*!
     * Performs all initializing functions for the ResourceManager class
     * Arguments: String, the directory where all images are stored for loading
     * Returns: void
     */
    for (const auto& imageFileEntry : std::filesystem::recursive_directory_iterator(imageDirPath)) {
        if (!std::filesystem::is_directory(imageFileEntry)) {
            ResourceManager::GetInstance().LoadResource(imageFileEntry.path().generic_string());
        }
    }
}

void ResourceManager::LoadResource(std::string imageFilename) {
    /*!
     * Loads the images in the provided directory to the resource manager
     *
     * Arguments: string, the filename of the image for loading
     * Returns: void
     */
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

std::shared_ptr<SDL_Surface> ResourceManager::GetResource(std::string imageFilename) {
    /*!
     * Returns the desired resource from the resource manager
     *
     * Arguments: string, the filename of the desired image
     * Returns: std::shared_ptr<SDL_Surface>, shared pointer of image
     */
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
