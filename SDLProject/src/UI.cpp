#include "UI.hpp"
#include "FPSCounter.hpp"
#include "TextureManager.hpp"
#include "Camera.hpp"
#include "Player.hpp"
#include "TileLayer.hpp"


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
	SDL_GetMouseState(&cx, &cy);
	kameraX = Camera::GetInstance()->getCamera_ViewBox()->x;
	kameraY = Camera::GetInstance()->getCamera_ViewBox()->y;
	kepernyoX = kameraX + cx*(1.0/scale);
	kepernyoY = kameraY + cy*(1.0/scale);
	//std::cout << kepernyoX << "\t" << kepernyoY << "\n";
	int size = Engine::GetInstance()->getTileSize();

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
		int xi = x + (10.0/scale);
		int yi = y + (10.0/scale);

		//bleh
		auto inv = static_cast<std::array<std::pair<Item*, int>, 40>*>((*Engine::GetInstance()->getGameObjects())[0]->getInventory());		

		for (int sor = 0; sor < 4; sor++) {
			for (int oszlop = 0; oszlop < 10; oszlop++) {
				SDL_Rect inventoryKockaHely = { x,y, static_cast<int>(60 * (1 / scale)), static_cast<int>(60 * (1 / scale)) };
				SDL_SetRenderDrawColor(renderer, 10, 90, 230, 200);
				SDL_RenderFillRect(renderer, &inventoryKockaHely);
				if ((*inv)[sor * 10 + oszlop].first) {
					TextureManager::GetInstance()->DrawItem("itemtexturemap", xi, yi, 40 * (1 / scale), 40 * (1 / scale), ((*inv)[sor * 10 + oszlop].first->getItemID() - 1) * 40, 0, 40, 40);
				}
				x += static_cast<int>(20 * (1 / scale)) + static_cast<int>(60 * (1 / scale));
				xi += static_cast<int>(40 * (1 / scale)) + static_cast<int>(40 * (1 / scale));
			}
			if (!showInventory) {
				break;
			}
			x = 20;
			y += static_cast<int>(20 * (1 / scale)) + static_cast<int>(60 * (1 / scale));
			yi += static_cast<int>(40 * (1 / scale)) + static_cast<int>(40 * (1 / scale));
		}
	}

	//block highlight
	{

		int tilesize = Engine::GetInstance()->getTileSize();
		int x = kepernyoX - kameraX - kepernyoX % tilesize;
		int y = kepernyoY - kameraY - kepernyoY % tilesize;

		/*std::cout << x << "\t" << y << "\n";
		std::cout << kepernyoX/tilesize << "\t" << kepernyoY/tilesize << "\n";*/

		highlightUI = { x, y, tilesize, tilesize };
		SDL_SetRenderDrawColor(renderer, 245, 225, 35, 150);
		SDL_RenderFillRect(renderer, &highlightUI);

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

}
