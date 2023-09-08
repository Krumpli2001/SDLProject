#include "Menu.hpp"

Menu* Menu::Menu_Instance = nullptr;

void Menu::Update()
{
	//SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
	//SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), Menu::GetInstance()->getBG());
	surfaceMessage = TTF_RenderText_Solid(font, "\nContinue\nQuit\n", color);
	Message = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surfaceMessage);
}

void Menu::Draw()
{
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::GetInstance()->GetRenderer());
	//SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &BG);
	SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Message, NULL, &Message_rect);

}

void Menu::Clean()
{
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
	std::cout << "\nText is deleted\n";
}
