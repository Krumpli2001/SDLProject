#include "SpriteAnimation.hpp"

SpriteAnimation::SpriteAnimation(bool repeat) {
	SpriteAnimation_Repeat = repeat;
	SpriteAnimation_Ended = false;
}

void SpriteAnimation::Update(Uint64 dt)
{
	if (SpriteAnimation_StartFrame)	{
		if ((SpriteAnimation_AnimationSpeed * SpriteAnimation_FrameCount) < (SDL_GetTicks64() - epoch)) { epoch = SDL_GetTicks64(); }
		SpriteAnimation_CurrentFrame = ((SDL_GetTicks64() - epoch) / SpriteAnimation_AnimationSpeed) % SpriteAnimation_FrameCount;
	}
	else {
		SpriteAnimation_CurrentFrame = (SDL_GetTicks64() / SpriteAnimation_AnimationSpeed) % SpriteAnimation_FrameCount;
	}
}

void SpriteAnimation::Draw(double x, double y, int spriteW, int spriteH, SDL_RendererFlip flip, double XScale, double YScale)
{
	TextureManager::GetInstance()->DrawFrame(SpriteAnimation_TextureID, x, y, spriteW, spriteH, SpriteAnimation_SpriteRow, SpriteAnimation_CurrentFrame, SpriteAnimation_StartFrame, flip);
}

void SpriteAnimation::SetProps(std::string textureID, int spriteRow, int frameCount, int aniSpeed, bool startFrame)
{
	SpriteAnimation_StartFrame = startFrame;
	SpriteAnimation_TextureID = textureID;
	SpriteAnimation_SpriteRow = spriteRow;
	SpriteAnimation_FrameCount = frameCount;
	SpriteAnimation_AnimationSpeed = aniSpeed;
}