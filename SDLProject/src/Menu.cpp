#include <cstring>
#include <fstream>
#include <string>

#include "Camera.hpp"
#include "Input.hpp"
#include "Itemdata.hpp"
#include "MapParser.hpp"
#include "mappgen.hpp"
#include "Menu.hpp"
#include "TextureManager.hpp"
#include "Timer.hpp"
#include "UI.hpp"

Menu* Menu::Menu_Instance = nullptr;

void Menu::MenuInit() {

	constexpr auto r_height = 150;

	rublikak.push_back(rublika("Continue", 0, 0, 500, r_height));
	rublikak.push_back(rublika("Options", 0, 150, 500, r_height));
	rublikak.push_back(rublika("Save", 0, 300, 250, r_height));
	rublikak.push_back(rublika("Title screen", 0, 450, 600, r_height));
	rublikak.push_back(rublika("Quit", 0, 600, 250, r_height));

	rublikak.push_back(rublika("Retry", 0, 0, 300, r_height));

	rublikak.push_back(rublika("Load", 0, 0, 250, r_height));
	rublikak.push_back(rublika("Generate", 0, 150, 500, r_height));

	rublikak.push_back(rublika("Back", 0, 0, 250, r_height));

	rublikak.push_back(rublika("Volume: ", 0, 0, 0, r_height));

}

void Menu::Update()
{
	constexpr auto r_height = 150;
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
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				RUpdate("gold", index);
				if (cc == 1 or enter) {
					enter = false;
					auto engineInstance = Engine::GetInstance();
					engineInstance->setMenuShowing(!engineInstance->getMenuShowing());
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				doelse("white", index);
			}
			options.push_back(index);
		}

		//options
		{
			if (melyik("Options", &index)) {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				RUpdate("gold", index);
				if (cc == 1 or enter) {
					submenu = sub::Settings;
					enter = false;
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				doelse("white", index);
			}
			options.push_back(index);
		}

		//save
		{
			if (melyik("Save", &index)) {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				RUpdate("gold", index);
				if (cc == 1 or enter) {
					enter = false;
					auto engineInstance = Engine::GetInstance();
					engineInstance->map_save();
					(*engineInstance->getGameObjects()).front()->saveInventory();
					engineInstance->setMenuShowing(false);
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				doelse("white", index);
			}
			options.push_back(index);
		}

		//title screen
		{
			if (melyik("Title screen", &index)) {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				RUpdate("red", index);
				if (cc == 1 or enter) {
					enter = false;
					submenu = sub::Title;
					auto engineInstance = Engine::GetInstance();
					MapParser::GetInstance()->Clean();
					engineInstance->getLevelMap()->Clean();
					TextureManager::GetInstance()->Clean();
					engineInstance->setmapIsLoaded(false);

					auto g = engineInstance->getGameObjects();

					for (auto obj : *g) {
						delete obj;
					}
					g->clear();
				

					engineInstance->setMenuShowing(true);
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				doelse("white", index);
			}
			options.push_back(index);
		}

		//quit
		{
			if (melyik("Quit", &index)) {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				RUpdate("red", index);
				if (cc == 1 or enter) {
					Engine::GetInstance()->Quit();
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				doelse("white", index);
			}
			options.push_back(index);
		}

		if (code == SDL_SCANCODE_ESCAPE) {
			auto engineInstance = Engine::GetInstance();
			engineInstance->setMenuShowing(!engineInstance->getMenuShowing());
			SDL_Delay(200);
		}
	}

	else if (submenu == sub::GameOver) {
		
		//reset
		{
			if (melyik("Retry", &index)) {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				RUpdate("gold", index);
				if (cc == 1 or enter) {
					enter = false; Reset();
					submenu = sub::Main;
					Engine::GetInstance()->setMenuShowing(false);
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				doelse("white", index);
			}
			options.push_back(index);
		}

		//quit
		{
			if (melyik("Quit", &index)) {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				RUpdate("red", index);
				if (cc == 1 or enter) {
					Engine::GetInstance()->Quit();
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
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
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				RUpdate("green", index);
				if (cc == 1 or enter) {
					TextureManager::GetInstance()->ParseTextures("assets/textures.xml");
					enter = false;
					submenu = sub::Load;
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				doelse("white", index);
			}
			options.push_back(index);
		}

		//mapgen
		{
			if (melyik("Generate", &index)) {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				RUpdate("green", index);
				if (cc == 1 or enter) {
					enter = false;
					cc = 0;
					if (mappgen::gen("gen", 300, 100)) {
						TextureManager::GetInstance()->ParseTextures("assets/textures.xml");
						submenu = sub::Load;
					}
					
				}
			}
			else {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				doelse("white", index);
			}
			options.push_back(index);
		}

		//options
		{
			if (melyik("Options", &index)) {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				RUpdate("red", index);
				if (cc == 1 or enter) {
					submenu = sub::Settings;
					enter = false;
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				doelse("white", index);
			}
			options.push_back(index);
		}

		//quit
		{
			if (melyik("Quit", &index)) {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				RUpdate("red", index);
				if (cc == 1 or enter) {
					Engine::GetInstance()->Quit();
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
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

						int len = static_cast<int>(temp.length());
						char* c = new char[temp.length() + 1];
						strcpy_s(c, temp.length() + 1, temp.c_str());

						saves.push_back(c);
						rublikak.push_back(rublika(saves[i], 0, static_cast<int>((saves.size() - 1) * r_height), static_cast<int>(temp.length() * 60), r_height));
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
						auto engineInstance = Engine::GetInstance();

						if (MapParser::GetInstance()->Load(saves[i])) {

							engineInstance->setLevelMap(MapParser::GetInstance()->getMap("MAP"));
							auto g = engineInstance->getLevelMap()->getMapLayers();
							engineInstance->setMap_W((*g)[0]->getColCount()* (*g)[0]->getTileSize());
							engineInstance->setMap_H((*g)[0]->getRowCount()* (*g)[0]->getTileSize());
							UI::GetInstance()->setCollisionLayer(engineInstance->getCollisionLayer());
							CollisionHandler::GetInstance()->reset();
							
							engineInstance->setCollisionLayerVector((*engineInstance->getLevelMap()->getMapLayers())[engineInstance->getCollisionLayer()]->getTileMap());
							engineInstance->setBackgroundLayerVector((*engineInstance->getLevelMap()->getMapLayers())[engineInstance->getBackgroundLayer()]->getTileMap());
							engineInstance->setFloraLayerVector((*engineInstance->getLevelMap()->getMapLayers())[engineInstance->getFloraLayer()]->getTileMap());
							
							engineInstance->setTileSize(CollisionHandler::GetInstance()->getCollisionLayer()->getTileSize());
							engineInstance->setMapName(saves[i]);
							engineInstance->spawnSpecial("PLAYER", 0, 0);
							engineInstance->spawnSpecial("SKELETON", 1000, 0);
							Camera::GetInstance()->setTarget((*engineInstance->getGameObjects()).front()->getOrigin());
							(*engineInstance->getGameObjects()).front()->readInventory();
							loaded_map_name = saves[i];
						}
						submenu = sub::Main;
						engineInstance->setMenuShowing(false);

						/*auto it = rublikak.begin();
						for (int i = 0; i < rublikak.size(); i++) {
							for (int j = 0; j < saves.size(); j++) {
								if (rublikak[i].szoveg == saves[j])
									rublikak.erase(it);
							}
							it++;
						}*/

						for (int j = 0; j < saves.size(); j++) {
							delete saves[j];
						}
						saves.clear();
						cc = 0;
						Camera::GetInstance()->Update();
						UI::GetInstance()->Update();
						engineInstance->Update();
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
				rublikak[index].setRectLocation(0, static_cast<int>(saves.size() * r_height));
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
				rublikak[index].setRectLocation(0, static_cast<int>(saves.size() * r_height));
				doelse("white", index);
			}
			options.push_back(index);
		}
	}

	else if (submenu == sub::Settings) {
		//hang
		{
			if(melyik("Volume: ", &index)){
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				RUpdate("red", index);
			}
			else {
				rublikak[index].setRectLocation(0, static_cast<int>(saves.size() * r_height));
				doelse("white", index);
			}
			options.push_back(index);
		}

		//vissza
		{
			if (melyik("Back", &index)) {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
				RUpdate("red", index);
				if (cc == 1 or enter) {
					enter = false;
					submenu = prevSubmenu;
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
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
	auto engineInstane = Engine::GetInstance();

	if (submenu!=sub::Title) {
		SDL_SetRenderDrawColor(engineInstane->getRenderer(), 0, 0, 0, 100);
		SDL_RenderFillRect(engineInstane->getRenderer(), 0);
	}
	else {
		SDL_SetRenderDrawColor(engineInstane->getRenderer(), 0, 0, 0, 255);
		SDL_RenderFillRect(engineInstane->getRenderer(), 0);
	}

	auto scale = engineInstane->getScale();
	for (int i = 0; i < options.size(); i++) {
		TextureManager::GetInstance()->TCharsOut(rublikak[options[i]].szoveg, rublikak[options[i]].x, static_cast<int>(rublikak[options[i]].y / scale), static_cast<int>(rublikak[options[i]].h / scale), &rublikak[options[i]].w, rublikak[options[i]].color);
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
	for(int j = 0; j<options.size();j++){
		if(options[j]==highLighted){
			index = j;
		}
	}
	int prevHol = index;

	eger = false;
	rublikak[options[index]].isHighlighted = true;
	
		if (i == 1) {
			prevHol = index;
			index -= 1;
			if (index <= -1) {
				index = static_cast<int>(options.size() - 1);
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
	constexpr auto r_height = 150;
	Engine::GetInstance()->setResetFlag(true);
	std::ignore = melyik("Quit", &index);
	rublikak[index].setRectLocation(0, static_cast<int>(options.size() * r_height));
}

