#include "FPSCounter.hpp"

FPSCounter* FPSCounter::FPS_Instance = nullptr;

void FPSCounter::Update()
{
	scale = Engine::GetInstance()->getScale();
}

void FPSCounter::Draw() {
	TextureManager::GetInstance()->TCharsOut(std::to_string(Timer::GetInstance()->getFPS()), 0, 100, static_cast<int>(100.0 / scale));
}

//void FPSCounter::Clean() {
//}