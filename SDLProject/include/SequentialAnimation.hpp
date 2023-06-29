#pragma once

#include <string>
#include <map>
#include <vector>
#include <SDL.h>

#include "AnimationBase.hpp"

class Sequence
{
public:
	int Sequence_Speed;
	int Sequence_FrameCount;
	int Sequence_W;
	int Sequence_H;
	std::vector<std::string> Sequence_TextureIDs;
};

class SequentialAnimation : public AnimationBase
{
private:
	Sequence SequentialAnimation_CurrentSequence;
	std::map<std::string, Sequence> SequentialAnimation_SequenceMap;

public:
	SequentialAnimation(bool repeat = true);

	virtual void Update(double dt);
	void Parse(std::string source);
	void setCurrentSequence(std::string seqID);

	inline void setRepeat(bool repeat) { AnimationBase_Repeat = repeat; }

	void DrawFrame(double x, double y, SDL_RendererFlip flip, double XScale = 1, double YScale = 1);
};

