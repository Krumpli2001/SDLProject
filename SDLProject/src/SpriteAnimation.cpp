#include "SpriteAnimation.hpp"

SpriteAnimation::SpriteAnimation(bool repeat) : AnimationBase(repeat) {}

void SpriteAnimation::Update(double dt)
{
	AnimationBase_CurrentFrame = (SDL_GetTicks64() / SpriteAnimation_AnimationSpeed) % SpriteAnimation_FrameCount;
}

void SpriteAnimation::Draw(double x, double y, int spriteW, int spriteH, SDL_RendererFlip flip, double XScale, double YScale)
{
	TextureManager::GetInstance()->DrawFrame(SpriteAnimation_TextureID, x, y, spriteW, spriteH, SpriteAnimation_SpriteRow, AnimationBase_CurrentFrame, flip);
}

void SpriteAnimation::SetProps(std::string textureID, int spriteRow, int frameCount, int aniSpeed)
{
	SpriteAnimation_TextureID = textureID;
	SpriteAnimation_SpriteRow = spriteRow;
	SpriteAnimation_FrameCount = frameCount;
	SpriteAnimation_AnimationSpeed = aniSpeed;
}
