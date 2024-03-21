#include <format>

#include "Camera.hpp"
#include "FPSCounter.hpp"
#include "Input.hpp"
#include "TextureManager.hpp"
#include "TileLayer.hpp"
#include "UI.hpp"


void UI::UIInit()
{
	
}

void UI::Update()
{
	auto engine = Engine::GetInstance();

	//skala
	scale = engine->getScale();

	//fps frissules
	if (FpsShowing) {
		FPSCounter::GetInstance()->Update();
	}

	GameObject* player = (*engine->getGameObjects())[0];
	
	//hp szamolas + felette a szoveg letrehozasa
	php = player->getHP();
	mphp = player->getMaxHP();
	str_hp = std::to_string(php) + " / " + std::to_string(mphp);

	//block highlight
	auto camera = Camera::GetInstance();
	SDL_GetMouseState(&cx, &cy);
	kameraX = camera->getCamera_ViewBox()->x;
	kameraY = camera->getCamera_ViewBox()->y;
	kepernyoX = static_cast<int>(kameraX + cx / scale);
	kepernyoY = static_cast<int>(kameraY + cy / scale);
	//int size = Engine::GetInstance()->getTileSize();

}

void UI::Draw()
{
	auto engine = Engine::GetInstance();
	auto renderer = engine->getRenderer();
	auto texturemanager = TextureManager::GetInstance();
	//fps mutato
	if (FpsShowing) {
		FPSCounter::GetInstance()->Draw();
	}

	//ez itt a szivecskek
	{
		if (php > 0) {
			int szivekSzama = static_cast<int>(std::ceil(static_cast<double>(mphp) / 20.0 * (static_cast<double>(php) / static_cast<double>(mphp))));
			int kezdopixel = 40;
			double heartmeret = texturemanager->getTextureMap()->find("heart")->second.second.w;

			for (int i = szivekSzama; i > 0; i--) {
				double seged = php % 20 / 20.0 == 0 ? 1.0 : php % 20 / 20.0;
				int x = i == 1 ? (*engine->getWindow_W() - kezdopixel + heartmeret * (1.0 - (seged))) * (1.0 / scale) : ((*engine->getWindow_W() - kezdopixel) / scale);
				int w = i == 1 ? heartmeret * (seged) * (1.0 / scale) : heartmeret * (1.0 / scale);
				int srcx = i == 1 ? heartmeret * (1.0 - (seged)) : 0;

				texturemanager->Draw("heart", x, 20 * (1.0 / scale), w, heartmeret * (1.0 / scale), srcx, 0);
				kezdopixel = static_cast<int>(kezdopixel + heartmeret);
			}
		}
		//hp szam
		texturemanager->TCharsOut(str_hp, static_cast<int>((*engine->getWindow_W() - 150) * 1 / scale), 0, 25.0 / scale);
	}

	//inventory
	{

		//vagy #DEFINE
		//vagy constexpr
		const int hatter_meret = 60;
		const int item_meret = 40;
		const int item_texture_meret = engine->getTileSize();
		int x = 20;
		int y = 20;
		int xi = x + (10.0/scale);
		int yi = y + (10.0/scale);

		int kepernyoX = 20;
		int kepernyoY = 20;

		klikkelhetoInventory = false;

		/*auto kiirando_sor = 1;
		if (showInventory) { kiirando_sor = 4; }*/

		int kiirando_sor = showInventory ? 4 : 1;

		auto inv = static_cast<std::array<std::pair<Item*, int>, 40>*>((*engine->getGameObjects())[0]->getInventory());		
		auto selected = (*engine->getGameObjects())[0]->getSelectedInventory();
		for (int sor = 0; sor < kiirando_sor; sor++) {
			for (int oszlop = 0; oszlop < 10; oszlop++) {

				//kek kockak
				SDL_Rect inventoryKockaHely = { x,y, static_cast<int>(hatter_meret * (1 / scale)), static_cast<int>(hatter_meret * (1 / scale)) };
				SDL_SetRenderDrawColor(renderer, 10, 90, 230, 100);
				if (sor*10 + selected == oszlop)
				{
					SDL_SetRenderDrawColor(renderer, 10, 90, 255, 255);
				}
				SDL_RenderFillRect(renderer, &inventoryKockaHely);

				//itemek
				if ((*inv)[sor * 10 + oszlop].first) {
					//textura kiirasa
					texturemanager->DrawItem("texture_map", xi, yi, static_cast<int>(item_meret / scale), item_meret / scale,
					((*inv)[sor * 10 + oszlop].first->getItemID() - 1) * item_texture_meret, 0, item_texture_meret, item_texture_meret);
				}
				if ((*inv)[sor * 10 + oszlop].second>0) {
					//szam kiirasa
					texturemanager->TCharsOut(std::to_string((*inv)[sor * 10 + oszlop].second), x, y, 35.0/scale);
				}

				if(Timer::GetInstance()->pressable(75)){

					if (transfer.first == nullptr and (*inv)[sor * 10 + oszlop].first and Input::GetInstance()->getClickDown() and
						static_cast<double>(cx) / scale > inventoryKockaHely.x and static_cast<double>(cx) / scale < inventoryKockaHely.x + inventoryKockaHely.w and
						static_cast<double>(cy) / scale > inventoryKockaHely.y and static_cast<double>(cy) / scale < inventoryKockaHely.y + inventoryKockaHely.h) {
						transfer.first = (*inv)[sor * 10 + oszlop].first;
						transfer.second = (*inv)[sor * 10 + oszlop].second;
						(*inv)[sor * 10 + oszlop].first = nullptr;
						(*inv)[sor * 10 + oszlop].second = 0;
					}

					else if ( transfer.first and (*inv)[sor * 10 + oszlop].first == nullptr and Input::GetInstance()->getClickDown() and
						static_cast<double>(cx) / scale > inventoryKockaHely.x and static_cast<double>(cx) / scale < inventoryKockaHely.x + inventoryKockaHely.w and
						static_cast<double>(cy) / scale > inventoryKockaHely.y and static_cast<double>(cy) / scale < inventoryKockaHely.y + inventoryKockaHely.h) {
						(*inv)[sor * 10 + oszlop].first = transfer.first;
						(*inv)[sor * 10 + oszlop].second = transfer.second;
						transfer.first = nullptr;
						transfer.second = 0;
					}


					if (transfer.first == (*inv)[sor * 10 + oszlop].first and Input::GetInstance()->getClickDown() and
						static_cast<double>(cx) / scale > inventoryKockaHely.x and static_cast<double>(cx) / scale < inventoryKockaHely.x + inventoryKockaHely.w and
						static_cast<double>(cy) / scale > inventoryKockaHely.y and static_cast<double>(cy) / scale < inventoryKockaHely.y + inventoryKockaHely.h)
					{
						(*inv)[sor * 10 + oszlop].second += transfer.second;
						transfer.first = nullptr;
						transfer.second = 0;
					}
				}

				if (transfer.first) {
					int cx, cy;
					SDL_GetMouseState(&cx, &cy);
					texturemanager->DrawItem("texture_map", cx/scale,cy/scale, item_meret * (1 / scale), item_meret * (1 / scale),
					(transfer.first->getItemID() - 1) * item_texture_meret, 0, item_texture_meret, item_texture_meret);
				}
				
				x += static_cast<int>(20 * (1 / scale)) + static_cast<int>(hatter_meret * (1 / scale));
				kepernyoX += 20 + hatter_meret;
				xi += static_cast<int>(item_meret * (1 / scale)) + static_cast<int>(item_meret * (1 / scale));
			}

			x = 20;
			xi = x + (10.0 / scale);
			kepernyoX = 20;
			y += static_cast<int>(20 * (1 / scale)) + static_cast<int>(hatter_meret * (1 / scale));
			kepernyoY += 20 + hatter_meret;
			yi += static_cast<int>(item_meret * (1 / scale)) + static_cast<int>(item_meret * (1 / scale));
		}
	}

	//block highlight
	{
		auto colllayer = engine->getCollisionLayerVector();
		int tilesize = engine->getTileSize();
		int x = kepernyoX - kameraX - (kepernyoX % tilesize);
		int y = kepernyoY - kameraY - (kepernyoY % tilesize);

		int xv = kepernyoX / tilesize;
		int yv = kepernyoY / tilesize;

		xv = xv < 0 ? 0 : xv;
		xv = xv > (*colllayer)[0].size() - 1 ? (*colllayer)[0].size() - 1 : xv;
		yv = yv < 0 ? 0 : yv;
		yv = yv > (*colllayer).size() - 1 ? (*colllayer).size() - 1 : yv;

		highlightUI = { x, y, tilesize, tilesize };
		SDL_SetRenderDrawColor(renderer, 245, 225, 35, 150);
		auto attetszo = CollisionHandler::GetInstance()->getAttetszo();
		bool at = false;
		for (int i = 0; i < attetszo->size() && !at; i++) {
			if ((*colllayer)[yv][xv] == (*attetszo)[i]) {
				at = true;
			}
		}
		if (!at) {
			SDL_RenderFillRect(renderer, &highlightUI);
		}
	}


	//TextureReset();
}

//void UI::TextureReset()
//{
//	/*if (FpsShowing) {
//		FPSCounter::GetInstance()->Clean();
//	}*/
//}

//void UI::Clean()
//{
//	/*if (FpsShowing) {
//		FPSCounter::GetInstance()->Clean();
//	}*/
//}
