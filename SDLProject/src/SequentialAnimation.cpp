#include "SequentialAnimation.hpp"
#include "TextureManager.hpp"
#include "tinyxml.h"

SequentialAnimation::SequentialAnimation(bool repeat) : AnimationBase(repeat) {}

void SequentialAnimation::Update(double dt)
{
	if (AnimationBase_Repeat or !AnimationBase_Ended)
	{
		AnimationBase_Ended = false;
		AnimationBase_CurrentFrame = (SDL_GetTicks64() / SequentialAnimation_CurrentSequence.Sequence_Speed) % SequentialAnimation_CurrentSequence.Sequence_FrameCount;
	}

	if (!AnimationBase_Repeat and AnimationBase_CurrentFrame == (SequentialAnimation_CurrentSequence.Sequence_FrameCount - 1))
	{
		AnimationBase_Ended = false;
		AnimationBase_CurrentFrame = SequentialAnimation_CurrentSequence.Sequence_FrameCount - 1;
	}
}

void SequentialAnimation::Parse(std::string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);
	if (xml.Error())
	{
		std::cout << "Failed to load animation file: " << source << std::endl;
	}

	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("sequence"))
		{
			Sequence seq;
			std::string seqID = e->Attribute("id");
			e->Attribute("speed", &seq.Sequence_Speed);
			e->Attribute("width", &seq.Sequence_W);
			e->Attribute("height", &seq.Sequence_H);
			e->Attribute("frameCount", &seq.Sequence_FrameCount);
			for (TiXmlElement* frame = e->FirstChildElement(); frame != nullptr; frame = frame->NextSiblingElement())
			{
				seq.Sequence_TextureIDs.push_back(frame->Attribute("textureID"));
			}
			SequentialAnimation_SequenceMap[seqID] = seq;
		}
	}
}

void SequentialAnimation::setCurrentSequence(std::string seqID)
{
	if (SequentialAnimation_SequenceMap.count(seqID) > 0)
	{
		SequentialAnimation_CurrentSequence = SequentialAnimation_SequenceMap[seqID];
	}

	else
	{
		std::cout << "The given sequence animation is not matching: " << seqID << std::endl;
	}
}

void SequentialAnimation::DrawFrame(double x, double y, SDL_RendererFlip flip, double XScale, double YScale)
{
	TextureManager::GetInstance()->Draw(SequentialAnimation_CurrentSequence.Sequence_TextureIDs[AnimationBase_CurrentFrame], x, y, SequentialAnimation_CurrentSequence.Sequence_W, SequentialAnimation_CurrentSequence.Sequence_H, XScale, YScale, flip);
}
