#pragma once

class AnimationBase {
protected:
	bool AnimationBase_Repeat;
	bool AnimationBase_Ended;
	int AnimationBase_CurrentFrame;

public:
	inline AnimationBase(bool repeat = true) : AnimationBase_Repeat(repeat) { AnimationBase_Ended = false; }

	virtual void Update(double dt) = 0;
	inline bool getEnded() { return AnimationBase_Ended; }

};