#include "FPSCounter.hpp"

FPSCounter* FPSCounter::FPS_Instance = nullptr;

void FPSCounter::kiir() {
	surfaceMessage = TTF_RenderText_Solid(font, std::to_string(Timer::GetInstance()->getFPS()).c_str(), color);
	Message = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surfaceMessage);
	SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Message, NULL, &Message_rect);
}

void FPSCounter::clean() {
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
	std::cout << "\nText is deleted\n";
}