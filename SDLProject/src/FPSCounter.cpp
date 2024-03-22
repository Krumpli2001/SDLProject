#include "FPSCounter.hpp"

FPSCounter* FPSCounter::FPS_Instance = nullptr;

void FPSCounter::Update()
{
	scale = Engine::GetInstance()->getScale();
}

void FPSCounter::Draw() {
	constexpr auto x = 0;
	constexpr auto y = 100;
	constexpr auto w = 100.0;
	TextureManager::GetInstance()->TCharsOut(std::to_string(Timer::GetInstance()->getFPS()), x, y, static_cast<int>(w / scale));
}

//void FPSCounter::Clean() {
//}