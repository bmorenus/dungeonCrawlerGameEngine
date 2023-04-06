#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(std::string filePath, SDL_Renderer* ren){
  m_surfance = SDL_LoadBMP(filePath.c_str());
  if(nullptr == m_surfance){
         SDL_Log("Failed to allocate surface");
  }else{
      SDL_Log("Allocated a bunch of memory to create identical game character");
      // Create a texture from our surface
      // Textures run faster and take advantage
      // of hardware acceleration
      m_texture = SDL_CreateTextureFromSurface(ren, m_surfance);
  }
}

SpriteComponent::~SpriteComponent(){
// TODO: Make sure spritesheet and m_texture are destroyed
// but is this the right place?
    SDL_FreeSurface(m_surfance);
    m_surfance = nullptr;
    SDL_DestroyTexture(m_texture);
}

// Set the sprite position
void SpriteComponent::receive(int message1, int message2){
    if (message1 == 225) {
      mDest.x = message2;
    } else if  (message1 == 226) {
      mDest.y = message2;
    } else if  (message1 == 227) {
      mCurrentFrame = message2;
      if(mCurrentFrame>6){
          mCurrentFrame=0;
      }
    }
}

void SpriteComponent::Update(GameObject* g){
    // Here I am selecting which frame I want to draw
    // from our sprite sheet. Think of this as just
    // using a mouse to draw a rectangle around the
    // sprite that we want to draw.
    mSrc.x = mCurrentFrame*75;
    mSrc.y = 0;
    mSrc.w = 75;
    mSrc.h = 87;

    // Where we want the rectangle to be rendered at.
    // This is an actual 'quad' that will draw our
    // source image on top of.
    mDest.w = 128;
    mDest.h = 128;
}

void SpriteComponent::Render(SDL_Renderer* ren){
    SDL_RenderCopy(ren, m_texture, &mSrc, &mDest);
}
