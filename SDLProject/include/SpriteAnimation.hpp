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

	//visszaadja, hogy az adott anim�ci� h�ny frame-b�l �ll
	inline int getFrameCount() { return SpriteAnimation_FrameCount; }

	//friss�t�s
	virtual void Update(Uint64 dt);

	//ki�r�s
	void Draw(double x, double y, int spriteW, int spriteH, SDL_RendererFlip flip, double angle = 0, double scale = 1, int flipX = 0, int flipY = 0);

	//adatok be�ll�t�sai - l�nyeg�ben mini constructor
	void SetProps(std::string textureID, int spriteRow, int frameCount, int aniSpeed , bool startFrame = false);

	inline auto getSpriteID() { return &SpriteAnimation_TextureID; }

};