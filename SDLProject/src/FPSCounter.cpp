#include "FPSCounter.hpp"

FPSCounter* FPSCounter::FPS_Instance = nullptr;

void FPSCounter::Update()
{
	scale = Engine::GetInstance()->getScale();
							 // ez igy undorito std::to_string(Timer::GetInstance()->getFPS()).c_str() - ki lett javitva :)
	/*surfaceMessage = TTF_RenderText_Solid(font, std::to_string(Timer::GetInstance()->getFPS()).c_str(), color);
	Message = SDL_CreateTextureFromSurface(Engine::GetInstance()->getRenderer(), surfaceMessage);
	azert van updatelve mindig az fps szamlalo hogy ha zoomolunk akkor annak a merete ne nagyon valtozzon
	Message_rect = { 0,0, static_cast<int>(100 * (1 / scale)), static_cast<int>(100 * (1 / scale)) };*/
}

void FPSCounter::Draw() {
	TextureManager::GetInstance()->TCharsOut(std::to_string(Timer::GetInstance()->getFPS()), 0, 0, 100 / scale);
	/*SDL_RenderCopy(Engine::GetInstance()->getRenderer(), Message, NULL, &Message_rect);
	Clean();
	surfaceMessage = nullptr;
	Message = nullptr;*/
}

void FPSCounter::Clean() {
	/*if (surfaceMessage) { SDL_FreeSurface(surfaceMessage); }
	if (Message) { SDL_DestroyTexture(Message); }*/
}