#include "UI.hpp"

void UI::Update()
{
	scale = Engine::GetInstance()->getScale();
	if (FpsShowing) {
		FPSCounter::GetInstance()->Update();
	}

	php = (*Engine::GetInstance()->getGameObjects())[0]->getHP();
	mphp = (*Engine::GetInstance()->getGameObjects())[0]->getMaxHP();
	std::string str = std::to_string(php) + " / " + std::to_string(mphp);
	surfaceMessage = TTF_RenderText_Solid(font, str.c_str(), color);
	Message = SDL_CreateTextureFromSurface(Engine::GetInstance()->getRenderer(), surfaceMessage);
	Message_rect = { static_cast<int>((*Engine::GetInstance()->getWindow_W() - 150) * 1/scale), 0, static_cast<int>(100 * (1 / scale)), static_cast<int>(20 * (1 / scale)) };
}

void UI::Draw()
{
	if (FpsShowing) {
		FPSCounter::GetInstance()->Draw();
	}
	
	if (php > 0) {
		TextureManager::GetInstance()->Draw("heart", (*Engine::GetInstance()->getWindow_W() - 200 + 40.0 * (1.0 - (php / 100.0))) * (1 / scale), 40, 40.0 * (php / 100.0) * (1 / scale), 40 * (1 / scale), 40.0 * (1.0 - (php / 100.0)), 0, true, SDL_FLIP_NONE, 1);
		//std::cout << 40.0 * (100.0 / php) << "\t"<< php << "\n";
	}

	SDL_RenderCopy(Engine::GetInstance()->getRenderer(), Message, NULL, &Message_rect);
	Clean();
	surfaceMessage = nullptr;
	Message = nullptr;
}

void UI::Clean()
{
	FPSCounter::GetInstance()->Clean();
	if (surfaceMessage) { SDL_FreeSurface(surfaceMessage); }
	if (Message) { SDL_DestroyTexture(Message); }
}
