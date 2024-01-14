#include "UI.hpp"

void UI::UIInit()
{
	
}

void UI::Update()
{
	//skala
	scale = Engine::GetInstance()->getScale();

	//fps frissules
	if (FpsShowing) {
		FPSCounter::GetInstance()->Update();
	}

	GameObject* player = (*Engine::GetInstance()->getGameObjects())[0];

	//hp szamolas + felette a szoveg letrehozasa
	php = player->getHP();
	mphp = player->getMaxHP();
	std::string str = std::to_string(php) + " / " + std::to_string(mphp);
	surfaceMessage = TTF_RenderText_Solid(font, str.c_str(), color);
	Message = SDL_CreateTextureFromSurface(Engine::GetInstance()->getRenderer(), surfaceMessage);
	Message_rect = { static_cast<int>((*Engine::GetInstance()->getWindow_W() - 150) * 1/scale), 0, static_cast<int>(100 * (1 / scale)), static_cast<int>(20 * (1 / scale)) };

	//block highlight
	//int cx, cy;
	SDL_GetMouseState(&cx, &cy);

	int M_WIDTH = Engine::GetInstance()->getMap_W();
	int M_HEIGHT = Engine::GetInstance()->getMap_H();
	int C_Width = *Engine::GetInstance()->getWindow_W();
	int C_Height = *Engine::GetInstance()->getWindow_H();

	kepernyoX = player->getOrigin()->getX() - C_Width / (2.0 * scale);
	kepernyoY = player->getOrigin()->getY() - C_Height / (2.0 * scale);

	kepernyoX = kepernyoX < 0 ? 0 : kepernyoX;
	kepernyoY = kepernyoY < 0 ? 0 : kepernyoY;
	kepernyoX = kepernyoX > M_WIDTH - C_Width * (1.0 / scale) ? M_WIDTH - C_Width * (1.0 / scale) : kepernyoX;
	kepernyoY = kepernyoY > M_HEIGHT - C_Height * (1.0 / scale) ? M_HEIGHT - C_Height * (1.0 / scale) : kepernyoY;

	//cx += kepernyoX;
	//cy += kepernyoY;
	kepernyoX += cx;
	kepernyoY += cy;
	//std::cout << kepernyoX << "\t" << kepernyoY << "\t";
	int size = Engine::GetInstance()->getTileSize();
	/*int blokkX = cx - cx % size;
	int blockY = cy - cy % size;*/

}

void UI::Draw()
{
	auto renderer = Engine::GetInstance()->getRenderer();
	//fps mutato
	if (FpsShowing) {
		FPSCounter::GetInstance()->Draw();
	}

	//ez itt a szivecskek
	{
		if (php > 0) {
			int szivekSzama = std::ceil(static_cast<double>(mphp) / 20.0 * (static_cast<double>(php) / static_cast<double>(mphp)));
			int kezdopixel /*for now*/ = 40;
			double heartmeret = 40.0;

			for (int i = szivekSzama; i > 0; i--) {
				double seged = php % 20 / 20.0 == 0 ? 1.0 : php % 20 / 20.0;
				int x = i == 1 ? (*Engine::GetInstance()->getWindow_W() - kezdopixel + heartmeret * (1.0 - (seged))) * (1.0 / scale) : ((*Engine::GetInstance()->getWindow_W() - kezdopixel) / scale);
				int w = i == 1 ? heartmeret * (seged) * (1.0 / scale) : heartmeret * (1.0 / scale);
				int srcx = i == 1 ? heartmeret * (1.0 - (seged)) : 0;

				TextureManager::GetInstance()->Draw("heart", x, 20 * (1.0 / scale), w, heartmeret * (1.0 / scale), srcx, 0, true, SDL_FLIP_NONE, 1);
				kezdopixel += 40;
			}
		}
		SDL_RenderCopy(renderer, Message, 0, &Message_rect);
	}

	//inventory
	{
		int x = 20;
		int y = 20;
		for (int sor = 0; sor < 4; sor++) {
			for (int oszlop = 0; oszlop < 10; oszlop++) {
				SDL_Rect inventoryKockaHely = { x,y, static_cast<int>(60 * (1 / scale)), static_cast<int>(60 * (1 / scale)) };
				SDL_SetRenderDrawColor(renderer, 10, 90, 230, 200);
				SDL_RenderFillRect(renderer, &inventoryKockaHely);
				x += static_cast<int>(20 * (1 / scale)) + static_cast<int>(60 * (1 / scale));
			}
			if (!showInventory) {
				break;
			}
			x = 20;
			y += static_cast<int>(20 * (1 / scale)) + static_cast<int>(60 * (1 / scale));
		}
	}

	//block highlight
	{
		//ez nem jo, zoommal elcsuszik
		/*int tilesize = Engine::GetInstance()->getTileSize();
		int x = cx - cx % static_cast<int>(tilesize*scale);
		int y = cy - cy % static_cast<int>(tilesize * scale);
		x *= (1.0 / scale);
		y *= (1.0 / scale);
		std::cout << x << "\t" << y << "\n";
		SDL_Rect highlightHely = { x, y, tilesize, tilesize };
		SDL_SetRenderDrawColor(renderer, 245, 225, 35, 150);
		SDL_RenderFillRect(renderer, &highlightHely);*/

		/*int tilesize = Engine::GetInstance()->getTileSize();
		highlightUI.w = tilesize;
		highlightUI.h = tilesize;
		SDL_SetRenderDrawColor(renderer, 245, 225, 35, 150);
		SDL_RenderFillRect(renderer, &highlightUI);*/
	}


	TextureReset();
}

void UI::TextureReset()
{
	if (FpsShowing) {
		FPSCounter::GetInstance()->Clean();
	}
	if (surfaceMessage) { SDL_FreeSurface(surfaceMessage); }
	if (Message) { SDL_DestroyTexture(Message); }
	surfaceMessage = nullptr;
	Message = nullptr;

	/*if (inventoryKocka) { SDL_FreeSurface(inventoryKocka); }
	if (inventoryKockaTextura) { SDL_DestroyTexture(inventoryKockaTextura); }
	inventoryKocka = nullptr;
	inventoryKockaTextura = nullptr;*/
}

void UI::Clean()
{
	if (FpsShowing) {
		FPSCounter::GetInstance()->Clean();
	}
	if (surfaceMessage) { SDL_FreeSurface(surfaceMessage); }
	if (Message) { SDL_DestroyTexture(Message); }
	surfaceMessage = nullptr;
	Message = nullptr;

	/*if (inventoryKocka) { SDL_FreeSurface(inventoryKocka); }
	if (inventoryKockaTextura) { SDL_DestroyTexture(inventoryKockaTextura); }
	inventoryKocka = nullptr;
	inventoryKockaTextura = nullptr;*/
}
