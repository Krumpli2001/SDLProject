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
	//fillColorMap("assets/colors.txt");

	//rublikak.reserve(20);

	rublikak.push_back(rublika("Continue", 0, 0, 500, 150));
	rublikak.push_back(rublika("Options", 0, 150, 500, 150));
	rublikak.push_back(rublika("Save", 0, 300, 250, 150));
	rublikak.push_back(rublika("Title screen", 0, 450, 600, 150));
	rublikak.push_back(rublika("Quit", 0, 600, 250, 150));

	rublikak.push_back(rublika("Retry", 0, 0, 300, 150));

	rublikak.push_back(rublika("Load", 0, 0, 250, 150));
	rublikak.push_back(rublika("Generate", 0, 150, 500, 150));

	rublikak.push_back(rublika("Back", 0, 0, 250, 150));


	/*for (int i = 0; i < rublikak.size(); i++) {
		rublikak[i].letrehoz();
	}*/
	//menuScale = Engine::GetInstance()->getScale();
}

void Menu::Update()
{
	int prevx = cx; int prevy = cy;
	Uint32 e = SDL_GetMouseState(&cx, &cy);
	int cc = 0;
	if (e == 1) {
		if (Timer::GetInstance()->pressable(200) and e == 1) {
			cc = 1;
			//SDL_BUTTON(1);
		}
		else {
			cc = 0;
		}
	}

	//SDL_RenderSetScale(Engine::GetInstance()->getRenderer(), 1.0f, 1.0f);


	if (cx != prevx or cy != prevy) {
		rublikak[highLighted].isHighlighted = false;
		eger = true;
	}

	options.clear();
	int code = Input::GetInstance()->getElse();


	if (Main) {
		
		//continue
		{
			if (melyik("Continue", &index)) {
				RUpdate("gold", index);
				//TextureManager::GetInstance()->TCharsOut(rublikak[index].szoveg, rublikak[index].x, rublikak[index].y, rublikak[index].h, &rublikak[index].w, "gold");
				//highLighted = index;
				if (cc == 1 or enter) {
					enter = false;
					Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing());
					cc = 0;
				}
			}
			else {
				doelse("white", index);
			}
			options.push_back(index);
		}

		//options
		{
			if (melyik("Options", &index)) {
				rublikak[index].setRectLocation(0, 150);
				RUpdate("gold", index);
				if (cc == 1 or enter) {
					enter = false;
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, 150);
				doelse("white", index);
			}
			options.push_back(index);
		}

		//save
		{
			if (melyik("Save", &index)) {
				RUpdate("gold", index);
				if (cc == 1 or enter) {
					enter = false;
					Engine::GetInstance()->map_save();
					(*Engine::GetInstance()->getGameObjects())[0]->saveInventory();
					cc = 0;
				}
			}
			else {
				doelse("white", index);
			}
			options.push_back(index);
		}

		//title screen
		{
			if (melyik("Title screen", &index)) {
				rublikak[index].setRectLocation(0, 450);
				RUpdate("red", index);
				if (cc == 1 or enter) {
					enter = false;
					Main = false;
					Title = true;
					MapParser::GetInstance()->Clean();
					TextureManager::GetInstance()->Clean();
					Engine::GetInstance()->setmapIsLoaded(false);
					TileData::GetInstance()->ClearData();
					ItemData::GetInstance()->ClearData();
					//SDL_RenderClear(Engine::GetInstance()->getRenderer());
					Reset();
					Main = false; //ez igy egy buta megoldas
					Engine::GetInstance()->setMenuShowing(true);
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, 450);
				doelse("white", index);
			}
			options.push_back(index);
		}

		//quit
		{
			if (melyik("Quit", &index)) {
				rublikak[index].setRectLocation(0, 600);
				RUpdate("red", index);
				if (cc == 1 or enter) {
					Engine::GetInstance()->Quit();
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, 600);
				doelse("white", index);
			}
			options.push_back(index);
		}

		if (code == SDL_SCANCODE_ESCAPE) {
			Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing());
			SDL_Delay(200);
		}
	}

	else if (GameOver) {
		
		//reset
		{
			if (melyik("Retry", &index)) {
				RUpdate("gold", index);
				if (cc == 1 or enter) {
					enter = false; Reset();
					Main = true;
					Engine::GetInstance()->setMenuShowing(false);
					cc = 0;
				}
			}
			else {
				doelse("white", index);
			}
			options.push_back(index);
		}

		//quit
		{
			if (melyik("Quit", &index)) {
				rublikak[index].setRectLocation(0, 150);
				RUpdate("red", index);
				if (cc == 1 or enter) {
					Engine::GetInstance()->Quit();
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, 150);
				doelse("white", index);
			}
			options.push_back(index);
		}

	}

	else if (Title) {

		//load
		{
			if (melyik("Load", &index)) {
				RUpdate("green", index);
				if (cc == 1 or enter) {
					TextureManager::GetInstance()->ParseTextures("assets/textures.xml");
					enter = false;
					Title = false;
					Load = true;
					cc = 0;
				}
			}
			else {
				doelse("white", index);
			}
			options.push_back(index);
		}

		//mapgen
		{
			if (melyik("Generate", &index)) {
				RUpdate("green", index);
				if (cc == 1 or enter) {
					enter = false;
					cc = 0;
				}
			}
			else {
				doelse("white", index);
			}
			options.push_back(index);
		}

		//options
		{
			if (melyik("Options", &index)) {
				rublikak[index].setRectLocation(0, 300);
				RUpdate("red", index);
				if (cc == 1 or enter) {
					enter = false;
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, 300);
				doelse("white", index);
			}
			options.push_back(index);
		}

		//quit
		{
			if (melyik("Quit", &index)) {
				rublikak[index].setRectLocation(0, 450);
				RUpdate("red", index);
				if (cc == 1 or enter) {
					Engine::GetInstance()->Quit();
					cc = 0;
				}
			}
			else {
				rublikak[index].setRectLocation(0, 450);
				doelse("white", index);
			}
			options.push_back(index);
		}
	}

	else if (Load) {
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
							/*auto data = TileData::GetInstance()->getTileIData();
							for (auto it = data->begin(); it != data->end(); it++) {
								std::cout << it->second->TileID << " " << it->second->TileName << " " << it->second->LayerID << " " << it->second->isTransparent << std::endl;
							}*/
							Engine::GetInstance()->setMapName(saves[i]);
							(*Engine::GetInstance()->getGameObjects())[0]->readInventory();
							loaded_map_name = saves[i];
						}
						Load = false;
						Main = true;
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
					Load = false;
					Title = true;
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
	//SDL_RenderClear(Engine::GetInstance()->getRenderer());
	if (!Title) {
		//SDL_RenderClear(Engine::GetInstance()->getRenderer());
		SDL_SetRenderDrawColor(Engine::GetInstance()->getRenderer(), 0, 0, 0, 100);
		SDL_RenderFillRect(Engine::GetInstance()->getRenderer(), 0);
	}
	else {
		SDL_SetRenderDrawColor(Engine::GetInstance()->getRenderer(), 0, 0, 0, 255);
		SDL_RenderFillRect(Engine::GetInstance()->getRenderer(), 0);
	}

	for (int i = 0; i < options.size(); i++) {
		/*SDL_RenderCopy(Engine::GetInstance()->getRenderer(), rublikak[options[i]].Message, NULL, &rublikak[options[i]].doboz);
		SDL_FreeSurface(rublikak[options[i]].surfaceMessage); rublikak[options[i]].surfaceMessage = nullptr;
		SDL_DestroyTexture(rublikak[options[i]].Message); rublikak[options[i]].Message = nullptr;*/
		auto scale = Engine::GetInstance()->getScale();
		TextureManager::GetInstance()->TCharsOut(rublikak[options[i]].szoveg, rublikak[options[i]].x, rublikak[options[i]].y/scale, rublikak[options[i]].h/scale, &rublikak[options[i]].w, rublikak[options[i]].color);
	}
	std::cout << std::format("{}\t{}\n", rublikak[options[0]].h, rublikak[options[0]].szoveg);
}

void Menu::Clean()
{
	/*if (!Engine::GetInstance()->getMenuShowing()) {
		for (int i = 0; i < rublikak.size(); i++)
		{
			SDL_FreeSurface(rublikak[i].surfaceMessage);
			SDL_DestroyTexture(rublikak[i].Message);
		}
	}*/
	
	rublikak.clear();

	//colors.clear();

	std::cout << "\nText is deleted\n";
}

//billentyuzethez
void Menu::setHighlighted(int i) {
	//if (highLighted > options.size() - 1) { highLighted = options.size() - 1; }
	//if (highLighted < 0) { highLighted = 0; }
	int index=0;
	for(int j = 0; j<options.size();j++){if(options[j]==highLighted){ index = j; } }
	int prevHol = index;

	//int prevHol = 0;
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
	GameOver = false;
	//Main = true;
	std::ignore = melyik("Quit", &index);
	rublikak[index].setRectLocation(0, 450);
}

