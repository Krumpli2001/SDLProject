#pragma once

#include <SDL.h>

#include "TextureManager.hpp"
#include "AnimationBase.hpp"

class SpriteAnimation : public AnimationBase
{
private:
	int SpriteAnimation_AnimationSpeed;
	int SpriteAnimation_SpriteRow;
	int SpriteAnimation_FrameCount;
	std::string SpriteAnimation_TextureID;
public:
	SpriteAnimation(bool repeat = true);

	virtual void Update(double dt);
	void Draw(double x, double y, int spriteW, int spriteH, SDL_RendererFlip flip, double XScale = 1, double YScale = 1);
	void SetProps(std::string textureID, int spriteRow, int frameCount, int aniSpeed);

};

//class Animation : public AnimationBase {
//private:
//	int Animation_SpriteRow;
//	int Animation_SpriteFrame;
//	int Animation_AniSpeed;
//	int Animation_FrameCount;
//	std::string Animation_TextureID;
//	//Uint64 A_Delta;
//	//SDL_RendererFlip Animation_Flip;
//
//public:
//	Animation() {};
//
//	//inline void setDelta(Uint64 delta) { A_Delta = delta; }
//
//	void Update();
//	void Draw(double x, double y, int spriteW, int spriteH, SDL_RendererFlip flip = SDL_FLIP_NONE);
//	void SetProps(std::string textureID, int spriteRow, int frameCount, int aniSpeed);// , SDL_RendererFlip flip = SDL_FLIP_NONE);
//};