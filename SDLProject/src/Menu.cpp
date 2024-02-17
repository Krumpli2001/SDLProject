#include <fstream>
#include <string>
#include <cstring>

#include "Menu.hpp"
#include "Input.hpp"
#include "Timer.hpp"
#include "MapParser.hpp"
#include "TextureManager.hpp"
#include "UI.hpp"
#include "Tiles.hpp"
#include "Itemdata.hpp"

Menu* Menu::Menu_Instance = nullptr;

void Menu::MenuInit() {

	rublikak.push_back(rublika("Continue", 0, 0, 500, 150));
	rublikak.push_back(rublika("Options", 0, 150, 500, 150));
	rublikak.push_back(rublika("Save", 0, 300, 250, 150));
	rublikak.push_back(rublika("Title screen", 0, 450, 600, 150));
	rublikak.push_back(rublika("Quit", 0, 600, 250, 150));

	rublikak.push_back(rublika("Retry", 0, 0, 300, 150));

	rublikak.push_back(rublika("Load", 0, 0, 250, 150));
	rublikak.push_back(rublika("Generate", 0, 150, 500, 150));

	rublikak.push_back(rublika("Back", 0, 0, 250, 150));

	rublikak.push_back(rublika("Volume: ", 0, 0, 0, 150));

}

void Menu::Update()
{
	int prevx = cx; int prevy = cy;
	Uint32 e = SDL_GetMouseState(&cx, &cy);
	int cc = 0;
	if (e == 1) {
		if (Timer::GetInstance()->pressable(200) and e == 1) {
			cc = 1;
		}
		else {
			cc = 0;
		}
	}

	if (cx != prevx or cy != prevy) {
		rublikak[highLighted].isHighlighted = false;
		eger = true;
	}

	options.clear();
	int code = Input::GetInstance()->getElse();


	if (submenu == sub::Main) {
		prevSubmenu = submenu;
		//continue
		{
			if (melyik("Continue", &index)) {
				rublikak[index].setRectLocation(0, options.size() * 150);
				RUpdate("gold", index);
				if (cc == 1 or enter) {
					enter = false;
					Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing());
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, options.size() * 150);
				doelse("white", index);
			}
			options.push_back(index);
		}

		//options
		{
			if (melyik("Options", &index)) {
				rublikak[index].setRectLocation(0, options.size() * 150);
				RUpdate("gold", index);
				if (cc == 1 or enter) {
					submenu = sub::Settings;
					enter = false;
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, options.size() * 150);
				doelse("white", index);
			}
			options.push_back(index);
		}

		//save
		{
			if (melyik("Save", &index)) {
				rublikak[index].setRectLocation(0, options.size() * 150);
				RUpdate("gold", index);
				if (cc == 1 or enter) {
					enter = false;
					Engine::GetInstance()->map_save();
					(*Engine::GetInstance()->getGameObjects())[0]->saveInventory();
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, options.size() * 150);
				doelse("white", index);
			}
			options.push_back(index);
		}

		//title screen
		{
			if (melyik("Title screen", &index)) {
				rublikak[index].setRectLocation(0, options.size() * 150);
				RUpdate("red", index);
				if (cc == 1 or enter) {
					enter = false;
					submenu = sub::Title;
					MapParser::GetInstance()->Clean();
					TextureManager::GetInstance()->Clean();
					Engine::GetInstance()->setmapIsLoaded(false);
					TileData::GetInstance()->ClearData();
					ItemData::GetInstance()->ClearData();
					Reset();
					Engine::GetInstance()->setMenuShowing(true);
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, options.size() * 150);
				doelse("white", index);
			}
			options.push_back(index);
		}

		//quit
		{
			if (melyik("Quit", &index)) {
				rublikak[index].setRectLocation(0, options.size() * 150);
				RUpdate("red", index);
				if (cc == 1 or enter) {
					Engine::GetInstance()->Quit();
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, options.size() * 150);
				doelse("white", index);
			}
			options.push_back(index);
		}

		if (code == SDL_SCANCODE_ESCAPE) {
			Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing());
			SDL_Delay(200);
		}
	}

	else if (submenu == sub::GameOver) {
		
		//reset
		{
			if (melyik("Retry", &index)) {
				rublikak[index].setRectLocation(0, options.size() * 150);
				RUpdate("gold", index);
				if (cc == 1 or enter) {
					enter = false; Reset();
					submenu = sub::Main;
					Engine::GetInstance()->setMenuShowing(false);
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, options.size() * 150);
				doelse("white", index);
			}
			options.push_back(index);
		}

		//quit
		{
			if (melyik("Quit", &index)) {
				rublikak[index].setRectLocation(0, options.size() * 150);
				RUpdate("red", index);
				if (cc == 1 or enter) {
					Engine::GetInstance()->Quit();
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, options.size() * 150);
				doelse("white", index);
			}
			options.push_back(index);
		}

	}

	else if (submenu == sub::Title) {
		prevSubmenu = submenu;
		//load
		{
			if (melyik("Load", &index)) {
				rublikak[index].setRectLocation(0, options.size() * 150);
				RUpdate("green", index);
				if (cc == 1 or enter) {
					TextureManager::GetInstance()->ParseTextures("assets/textures.xml");
					enter = false;
					submenu = sub::Load;
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, options.size() * 150);
				doelse("white", index);
			}
			options.push_back(index);
		}

		//mapgen
		{
			if (melyik("Generate", &index)) {
				rublikak[index].setRectLocation(0, options.size() * 150);
				RUpdate("green", index);
				if (cc == 1 or enter) {
					enter = false;
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, options.size() * 150);
				doelse("white", index);
			}
			options.push_back(index);
		}

		//options
		{
			if (melyik("Options", &index)) {
				rublikak[index].setRectLocation(0, options.size() * 150);
				RUpdate("red", index);
				if (cc == 1 or enter) {
					submenu = sub::Settings;
					enter = false;
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, options.size() * 150);
				doelse("white", index);
			}
			options.push_back(index);
		}

		//quit
		{
			if (melyik("Quit", &index)) {
				rublikak[index].setRectLocation(0, options.size() * 150);
				RUpdate("red", index);
				if (cc == 1 or enter) {
					Engine::GetInstance()->Quit();
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, options.size() * 150);
				doelse("white", index);
			}
			options.push_back(index);
		}
	}

	else if (submenu == sub::Load) {
		//ez itt a mentes nevek feltoltese
		{
			if (saves.empty()) {
				int i = 0;
				for (const auto& entry : std::filesystem::directory_iterator("saves"))
				{
					std::string temp = entry.path().generic_string();
					temp = temp.substr(6);
					std::string ext = temp.substr(temp.length() - 3, temp.length());
					if (ext == "tmx") {
						temp.erase(temp.length() - 4, temp.length());

						int len = temp.length();
						char* c = new char[temp.length() + 1];
						strcpy_s(c, temp.length() + 1, temp.c_str());

						saves.push_back(c);
						rublikak.push_back(rublika(saves[i], 0, (saves.size() - 1) * 150, temp.length() * 60, 150));
						i++;
					}
				}
			}
		}

		//"inicializalas"
		{
			for (int i = 0; i < saves.size(); i++) {
				if (melyik(saves[i], &index)) {
					RUpdate("green", index);
					if (cc == 1 or enter) {
						enter = false;
						if (MapParser::GetInstance()->Load(saves[i])) {
							Engine::GetInstance()->setLevelMap(MapParser::GetInstance()->getMap("MAP"));
							TileData::GetInstance()->parseTileData("assets/maps/blockdata.xml");
							ItemData::GetInstance()->ParseItemData("assets/itemdata.xml");
							UI::GetInstance()->setCollisionLayer(Engine::GetInstance()->getCollisionLayer());
							CollisionHandler::GetInstance()->reset();
							Engine::GetInstance()->setCollisionLayerVector(CollisionHandler::GetInstance()->getCollisionTileMap());
							Engine::GetInstance()->setTileSize(CollisionHandler::GetInstance()->getCollisionLayer()->getTileSize());
							Engine::GetInstance()->setMapName(saves[i]);
							(*Engine::GetInstance()->getGameObjects())[0]->readInventory();
							loaded_map_name = saves[i];
						}
						submenu = sub::Main;
						Engine::GetInstance()->setMenuShowing(false);

						for (int j = 0; j < saves.size(); j++) {
							delete saves[j];
						}
						saves.clear();
						cc = 0;
						break;
					}
				}
				else {
					doelse("white", index);
				}
				options.push_back(index);
			}
		}

		//vissza
		{
			if (melyik("Back", &index)) {
				rublikak[index].setRectLocation(0, saves.size() * 150);
				RUpdate("green", index);
				if (cc == 1 or enter) {
					enter = false;
					submenu = prevSubmenu;
					MapParser::GetInstance()->Clean();
					TextureManager::GetInstance()->Clean();
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, saves.size() * 150);
				doelse("white", index);
			}
			options.push_back(index);
		}
	}

	else if (submenu == sub::Settings) {
		//hang
		{
			if(melyik("Volume: ", &index)){
				rublikak[index].setRectLocation(0, options.size() * 150);
				RUpdate("red", index);
			}
			else {
				rublikak[index].setRectLocation(0, saves.size() * 150);
				doelse("white", index);
			}
			options.push_back(index);
		}

		//vissza
		{
			if (melyik("Back", &index)) {
				rublikak[index].setRectLocation(0, options.size() * 150);
				RUpdate("red", index);
				if (cc == 1 or enter) {
					enter = false;
					submenu = prevSubmenu;
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, options.size() * 150);
				doelse("white", index);
			}
			options.push_back(index);
		}
	}

	switch (code)
	{
	case SDL_SCANCODE_DOWN:
		setHighlighted(-1);
		SDL_Delay(100);
		break;
	case SDL_SCANCODE_UP:
		setHighlighted(1);
		SDL_Delay(100);
		break;
	case SDL_SCANCODE_RETURN:
		setEnter(true);
		SDL_Delay(100);
		break;
	}

}

void Menu::Draw()
{
	if (submenu!=sub::Title) {
		SDL_SetRenderDrawColor(Engine::GetInstance()->getRenderer(), 0, 0, 0, 100);
		SDL_RenderFillRect(Engine::GetInstance()->getRenderer(), 0);
	}
	else {
		SDL_SetRenderDrawColor(Engine::GetInstance()->getRenderer(), 0, 0, 0, 255);
		SDL_RenderFillRect(Engine::GetInstance()->getRenderer(), 0);
	}

	for (int i = 0; i < options.size(); i++) {
		auto scale = Engine::GetInstance()->getScale();
		TextureManager::GetInstance()->TCharsOut(rublikak[options[i]].szoveg, rublikak[options[i]].x, rublikak[options[i]].y/scale, rublikak[options[i]].h/scale, &rublikak[options[i]].w, rublikak[options[i]].color);
	}
}

//ez is mar teljesen feles
void Menu::Clean()
{
	rublikak.clear();
}

//billentyuzethez
void Menu::setHighlighted(int i) {

	int index=0;
	for(int j = 0; j<options.size();j++){if(options[j]==highLighted){ index = j; } }
	int prevHol = index;

	eger = false;
	rublikak[options[index]].isHighlighted = true;
	
		if (i == 1) {
			prevHol = index;
			index -= 1;
			if (index <= -1) {
				index = options.size() - 1;
			}
		}
		if (i == -1) {
			prevHol = index;
			index += 1;
			if (index >= options.size()) {
				index = 0;
			}
		}

		rublikak[options[index]].isHighlighted = true;
		rublikak[options[prevHol]].isHighlighted = false;
		highLighted = options[index];
}

void Menu::Reset()
{
	Engine::GetInstance()->setResetFlag(true);
	std::ignore = melyik("Quit", &index);
	rublikak[index].setRectLocation(0, options.size() * 150);
}

