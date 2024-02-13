#pragma once

#include <SDL.h>

#include "TextureManager.hpp"

class SpriteAnimation
{
private:
	bool SpriteAnimation_Repeat{};
	bool SpriteAnimation_Ended{};
	int SpriteAnimation_CurrentFrame{};
	bool SpriteAnimation_StartFrame{};
	int SpriteAnimation_AnimationSpeed{};
	int SpriteAnimation_SpriteRow{};
	int SpriteAnimation_FrameCount{};
	std::string SpriteAnimation_TextureID{};
	Uint64 epoch = SDL_GetTicks64();
public:

	SpriteAnimation(bool repeat = false);
	inline int getFrameCount() { return SpriteAnimation_FrameCount; }


	virtual void Update(Uint64 dt);
	void Draw(double x, double y, int spriteW, int spriteH, SDL_RendererFlip flip, double angle = 0, double scale = 1, int flipX = 0, int flipY = 0);
	void SetProps(std::string textureID, int spriteRow, int frameCount, int aniSpeed , bool startFrame = false);

};