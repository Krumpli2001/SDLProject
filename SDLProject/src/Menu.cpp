#include "Menu.hpp"
//#include <string>

Menu* Menu::Menu_Instance = nullptr;

void Menu::MenuInit() {
	//const char* sz = "Continue";
	rublikak.push_back(rublika("Continue", 0, 0, 1000, 300, Menu::font, Menu::color));
	rublikak.push_back(rublika("Quit", 0, 300, 500, 300, Menu::font, Menu::color));
}

void Menu::Update()
{
	int cx, cy;
	Uint32 b = SDL_GetMouseState(&cx, &cy);

	if (b == 1 and cx >= 0 and cy >= 0 and cx <= 1000 and cy <= 300) {
		//SDL_Delay(150);
		Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing());
	}

	if (b == 1 and cx >= 0 and cy >= 300 and cx <= 500 and cy <= 600) {
		//SDL_Delay(150);
		Engine::GetInstance()->Quit();
	}

	//SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
	//SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), Menu::GetInstance()->getBG());
	

	/*for (int i = 0; i < rublikak.size(); i++) {
		rublikak[i].surfaceMessage = TTF_RenderText_Solid(font, "\nContinue\nQuit\n", color);
		rublikak[i].Message = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), rublikak[i].surfaceMessage);
	}*/
}

void Menu::Draw()
{
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::GetInstance()->GetRenderer());
	//SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &BG);
	for (int i = 0; i < rublikak.size(); i++) {
		SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), rublikak[i].Message, NULL, &rublikak[i].doboz);
	}
	//SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Message, NULL, &Message_rect);

}

void Menu::Clean()
{
	for (int i = 0; i < rublikak.size(); i++)
	{
		SDL_FreeSurface(rublikak[i].surfaceMessage);
		SDL_DestroyTexture(rublikak[i].Message);
	}
	rublikak.clear();

	/*SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);*/
	std::cout << "\nText is deleted\n";
}
