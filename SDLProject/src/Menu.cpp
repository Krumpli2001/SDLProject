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

Menu* Menu::Menu_Instance = nullptr;

void Menu::MenuInit() {
	fillColorMap("assets/colors.txt");

	//rublikak.reserve(20);

	rublikak.push_back(rublika("Continue", 0, 0, 500, 150, colors["white"]));
	rublikak.push_back(rublika("Options", 0, 150, 500, 150, colors["white"]));
	rublikak.push_back(rublika("Save", 0, 300, 250, 150, colors["white"]));
	rublikak.push_back(rublika("Title screen", 0, 450, 600, 150, colors["white"]));
	rublikak.push_back(rublika("Quit", 0, 600, 250, 150, colors["white"]));

	rublikak.push_back(rublika("Retry", 0, 0, 300, 150, colors["white"]));

	rublikak.push_back(rublika("Load", 0, 0, 250, 150, colors["white"]));
	rublikak.push_back(rublika("Generate", 0, 150, 500, 150, colors["white"]));

	rublikak.push_back(rublika("Back", 0, 0, 250, 150, colors["white"]));


	for (int i = 0; i < rublikak.size(); i++) {
		rublikak[i].letrehoz();
	}
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

	SDL_RenderSetScale(Engine::GetInstance()->getRenderer(), 1.0f, 1.0f);


	if (cx != prevx or cy != prevy) {
		rublikak[highLighted].isHighlighted = false;
		eger = true;
	}

	options.clear();
	int code = Input::GetInstance()->getElse();
	//enter = false;

	if (Main) {
		
		//continue
		{
			if (melyik("Continue", &index)) {
				RUpdate("gold", index);
				if (cc == 1 or enter) { enter = false; Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing()); }
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
					//SDL_RenderClear(Engine::GetInstance()->getRenderer());
					//Reset();

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
				if (cc == 1 or enter) {	/*Main = false; Title = true;*/ Engine::GetInstance()->Quit(); }
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
				if (cc == 1 or enter) { Engine::GetInstance()->Quit(); }
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
				if (cc == 1 or enter) { Engine::GetInstance()->Quit(); }
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
					temp.erase(temp.length() - 4, temp.length());

					int len = temp.length();
					char* c = new char[temp.length() + 1];
					strcpy_s(c, temp.length() + 1, temp.c_str());

					saves.push_back(c);
					rublikak.push_back(rublika(saves[i], 0, (saves.size() - 1) * 150, temp.length() * 60, 150, colors["white"]));
					i++;
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
							UI::GetInstance()->setCollisionLayer(Engine::GetInstance()->getCollisionLayer());
							CollisionHandler::GetInstance()->reset();
							Engine::GetInstance()->setCollisionLayerVector(CollisionHandler::GetInstance()->getCollisionTileMap());
							Engine::GetInstance()->setTileSize(CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize());
						}
						Load = false;
						Main = true;
						Engine::GetInstance()->setMenuShowing(false);

						for (int j = 0; j < saves.size(); j++) {
							delete saves[j];
						}
						saves.clear();

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
		SDL_RenderCopy(Engine::GetInstance()->getRenderer(), rublikak[options[i]].Message, NULL, &rublikak[options[i]].doboz);
		SDL_FreeSurface(rublikak[options[i]].surfaceMessage); rublikak[options[i]].surfaceMessage = nullptr;
		SDL_DestroyTexture(rublikak[options[i]].Message); rublikak[options[i]].Message = nullptr;
	}

}

void Menu::Clean()
{
	if (!Engine::GetInstance()->getMenuShowing()) {
		for (int i = 0; i < rublikak.size(); i++)
		{
			SDL_FreeSurface(rublikak[i].surfaceMessage);
			SDL_DestroyTexture(rublikak[i].Message);
		}
	}
	
	rublikak.clear();

	colors.clear();

	std::cout << "\nText is deleted\n";
}

void Menu::fillColorMap(std::string source)
{
	std::string egysor = "";
	std::string szin = "";
	std::string szam = "";
	unsigned char r = 0; unsigned char g = 0; unsigned char b = 0;
	std::ifstream f(source);
	//int i = 0;
	int betu = 0;

	if (f.is_open()) {
		while (std::getline(f, egysor)) {
			//int i = 0;
			int betu = 0;
			while (betu < egysor.length()) {
				while (egysor[betu] != '_' or egysor[betu+1] != ' ') {
					szin += std::tolower(egysor[betu]);
					betu++;
				}
				while (egysor[betu] != ' ' and egysor[betu+1] != '(') { betu++; }

				betu++;

				if (egysor[betu] == ' ' and egysor[betu+1] == '(') {
					int vesszok = 0;
					betu += 2;
					while (vesszok <= 2) {
						if (egysor[betu] != ',' and egysor[betu] != ')') {
							szam += egysor[betu];
							betu++;
						}
						else { 
							switch (vesszok){
							case 0:
								r = std::stoi(szam);
								break;
							case 1:
								g = std::stoi(szam);
								break;
							case 2:
								b = std::stoi(szam);
								break;
							}

							szam = "";
							vesszok++;
							betu++;
						}

					}
				}
				colors[szin] = SDL_Color{ r,g,b };
				betu = egysor.length();
			}
			egysor = "";
			//std::cout << szin<<"\n";
			szin = "";
		}
		f.close();
	}
	else {
		std::cerr << "\nnem lehetett megnyitni a szines fajlt\n";
	}
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
	Main = true;
	std::ignore = melyik("Quit", &index);
	rublikak[index].setRectLocation(0, 450);
}

void Menu::doelse(std::string str, int index) {
	rublikak[index].color = getColor(str);
	rublikak[index].letrehoz();
}
