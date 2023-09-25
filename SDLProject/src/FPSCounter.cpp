#include "FPSCounter.hpp"

FPSCounter* FPSCounter::FPS_Instance = nullptr;

void FPSCounter::Update()
{
							 // ez igy undorito std::to_string(Timer::GetInstance()->getFPS()).c_str()
	surfaceMessage = TTF_RenderText_Solid(font, std::to_string(Timer::GetInstance()->getFPS()).c_str(), color);
	Message = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surfaceMessage);
	//ttf_rendertext
}

void FPSCounter::Draw() {
	SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Message, NULL, &Message_rect);
	Clean();
	surfaceMessage = nullptr;
	Message = nullptr;
}

void FPSCounter::Clean() {
	if (surfaceMessage) { SDL_FreeSurface(surfaceMessage); }
	if (Message) { SDL_DestroyTexture(Message); }
	//std::cout << "\nText is deleted\n";
}