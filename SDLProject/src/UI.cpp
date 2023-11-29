#include "UI.hpp"

void UI::Update()
{
	scale = Engine::GetInstance()->getScale();
	if (FpsShowing) {
		FPSCounter::GetInstance()->Update();

	}
}

void UI::Draw()
{
	if (FpsShowing) {
		FPSCounter::GetInstance()->Draw();
	}
	double php = Engine::GetInstance()->getGameObjects()[0]->getHP();
	if (php > 0) {
		TextureManager::GetInstance()->Draw("heart", (*Engine::GetInstance()->getWindow_W() - 200 + 40.0 * (1.0 - (php / 100))) * (1 / scale), 0, 40.0 * (php / 100) * (1 / scale), 40 * (1 / scale), 40.0 * (1.0 - (php / 100)), 0, true, SDL_FLIP_NONE, 1);
		//std::cout << 40.0 * (100.0 / php) << "\t"<< php << "\n";
	}
}

void UI::Clean()
{
	FPSCounter::GetInstance()->Clean();
}
