#include <iostream>

#include <SDL_image.h>

#include "Engine.hpp"
#include "MapParser.hpp"
#include "ObjectFactory.hpp"
#include "Input.hpp"
#include "Menu.hpp"
#include "Camera.hpp"
#include "TextureManager.hpp"
#include "UI.hpp"
#include "mappgen.hpp"
#include "Options.hpp"

Engine* Engine::Engine_Instance = nullptr;

enum irany {BAL, JOBB};

bool Engine::Init()
{
	//SDL kep inicializalasa
	if ((SDL_Init(SDL_INIT_VIDEO) != 0) and IMG_Init(IMG_INIT_JPG or IMG_INIT_PNG) != 0)
	{
		std::cout << "Failed to inicialise!\n" << SDL_GetError() << std::endl;
		return false;
	}

	TTF_Init();
	Mix_Init(0);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);

	Engine_Music = Mix_LoadMUS("assets/ff_zene.wav");
	if (!Engine_Music) {
		std::cerr << SDL_GetError() << std::endl;
	}

	//ablak letrehozasa
	Engine_Window = SDL_CreateWindow("Jatek", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CREATION_WIDTH, CREATION_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (Engine_Window == nullptr)
	{
		std::cout << "Failed to CreateWindow!\n" << SDL_GetError() << std::endl;
		return false;
	}

	//renderer letrehozasa
	Engine_Renderer = SDL_CreateRenderer(Engine_Window, -1, SDL_RENDERER_ACCELERATED);
	if (Engine_Renderer == nullptr)
	{
		std::cout << "Failed to CreateRenderer!\n" << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetRenderDrawBlendMode(Engine_Renderer, SDL_BLENDMODE_BLEND);

	TextureManager::GetInstance()->Init();

	Menu::GetInstance()->MenuInit();

	ItemData::GetInstance()->ParseData("assets/itemdata.xml");

	//lehet hogy ezt lehetne unique_ptr-el - illetve nem itt kene lennie
	Engine_PropsMap.emplace("PLAYER", new Properties("player_idle", 100, 0, 0, 0.0, 0.0));
	Engine_PropsMap.emplace("ZOMBIE", new Properties("zombie_idle", 100, 240, 240, 0.0, 0.0));
	Engine_PropsMap.emplace("SKELETON", new Properties("skeleton_idle", 100, 240, 240, 0.0, 0.0));
	Engine_PropsMap.emplace("ARROW", new Properties("arrow", 1, 20, 100, 0, 0));

	//Enigine_GameObjects.push_back(ObjectFactory::GetInstance()->CreateObject("PLAYER", Engine_PropsMap.find("PLAYER")->second));	//player a nulladik elem
																																	//Enigine_GameObjects.push_back(mob);
	//Camera::GetInstance()->setTarget(Enigine_GameObjects[0]->getOrigin());

	UI::GetInstance()->UIInit();

	//spawnSpecial("SKELETON", 1000, 0);
	/*spawnSpecial("ZOMBIE", 1000, 0)*/;

	Options::GetInstance()->readSettings();
	if (*Options::GetInstance()->getSavedScale() != -1) {
		scale = *Options::GetInstance()->getSavedScale();
	}
	if (*Options::GetInstance()->getSavedVolume() != -1) {
		volume = *Options::GetInstance()->getSavedVolume();
	}

	Engine_IsRunning = true;
	return Engine_IsRunning;

}

bool Engine::Clean()
{


	for (unsigned int i = 0; i != Enigine_GameObjects.size(); i++)
	{
		Enigine_GameObjects[i]->Clean();
	}

	Engine_PropsMap.clear();

	TextureManager::GetInstance()->Clean();
	TextureManager::GetInstance()->Clearfont();
	//UI::GetInstance()->Clean();
	Menu::GetInstance()->Clean();
	ItemData::GetInstance()->ClearData();

	//settings kiirasa fajlba
	{
		Options::GetInstance()->setSavedScale(scale);
		Options::GetInstance()->setSavedVolume(volume);
		Options::GetInstance()->saveSettings();
	}

	SDL_DestroyRenderer(Engine_Renderer);
	SDL_DestroyWindow(Engine_Window);
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
	return false;
}

void Engine::Quit()
{
	Engine_IsRunning = false;
}

void Engine::Update()
{
	Mix_VolumeMusic(volume);

	if (Engine_ResetFlag) {
		Enigine_GameObjects[0]->reset();
		//Engine_MenuShowing = false;
		Engine_ResetFlag = false;
	}

	if (!Engine_MenuShowing) {
		Uint64 dt = Timer::GetInstance()->getTimer_DeltaTime();
		Timer::GetInstance()->setmenu(false);

		//ez itt csak a spawnolás
		if (Engine_SpawnTimer == SPAWN) {
			int bal_jobb = RNG::GetInstance()->genRandomInt(1);
			//mi a rak lett ez az auto XD
			auto iter = Engine_PropsMap.begin();
			int randomMob;
			do {
				iter = Engine_PropsMap.begin();
				randomMob = RNG::GetInstance()->genRandomInt(Engine_PropsMap.size()-1);
				std::advance(iter, randomMob);
			} while (iter->first == "PLAYER" || iter->first == "ARROW");

			//maga a spawnolas

			int x = 0;
			int y = 0;

				if (bal_jobb == BAL) {
					x = Enigine_GameObjects[0]->getPosition()->getX() - (50 * TileSize);
					if (x > 0 && spawnolhat(x, &y, iter->second->Properties_Width, iter->second->Properties_Height)) {
						//spawnSpecial(iter->first, x, legmamasabbBlock(x) - iter->second->Properties_Height, iter->second->Properies_hp, 10);
					}
				}
				if (bal_jobb == JOBB) {
					x = Enigine_GameObjects[0]->getPosition()->getX() + (50 * TileSize);
					if (x < Map_W && spawnolhat(x, &y, iter->second->Properties_Width, iter->second->Properties_Height)) {
						//spawnSpecial(iter->first, x, legmamasabbBlock(x) - iter->second->Properties_Height, iter->second->Properies_hp, 10);
					}
				}

			Engine_SpawnTimer -= dt;
		}
		else {
			Engine_SpawnTimer -= dt;
		}
		if (Engine_SpawnTimer < 0) {
			Engine_SpawnTimer = SPAWN;
		}

		for (unsigned int i = 0; i < Enigine_GameObjects.size(); i++)
		{
			//player meghalt
			if (Enigine_GameObjects[0]->getHP() <= 0) { Engine_MenuShowing = true; Menu::GetInstance()->setGameOver(true);  Menu::GetInstance()->setMain(false); break; }
			//barmi mas meghalt
			if (Enigine_GameObjects[i]->getHP() <= 0 and i != 0) {
				Enigine_GameObjects.erase(Enigine_GameObjects.begin() + i);
			}
			else {
				//player collisionja mas enemyvel
				if (i != 0) {
					unsigned int mob = i;

					if (CollisionHandler::GetInstance()->CheckCollision(*Enigine_GameObjects[0]->getCollider()->getBox(),
						*Enigine_GameObjects[mob]->getCollider()->getBox())) {
						//utes (player)
						if ((Enigine_GameObjects[0]->getAttacking())/* and (Enigine_GameObjects[0]->getAttacktime() == PLAYER_ATTACK_TIME - dt)*/) {
							Enigine_GameObjects[mob]->setHP(Enigine_GameObjects[mob]->getHP() - Enigine_GameObjects[0]->getAttackPower());
						}
					}
					Enigine_GameObjects[mob]->attacking(dt);

				}
				Enigine_GameObjects[i]->Update(dt);
			}
		}

		Engine_LevelMap->Update(static_cast<int>(Enigine_GameObjects[0]->getPosition()->getX()) / CollisionHandler::GetInstance()->getCollisionLayer()->getTileSize(), static_cast<int>(Enigine_GameObjects[0]->getPosition()->getY()) / CollisionHandler::GetInstance()->getCollisionLayer()->getTileSize());
		Camera::GetInstance()->Update();
		UI::GetInstance()->Update();


		if (Mix_PlayingMusic())
		{
			Mix_ResumeMusic();
		}
		if (!Mix_PlayingMusic()) {
			Mix_PlayMusic(Engine_Music, -1);
		}

		if (Input::GetInstance()->getElse() == SDL_SCANCODE_ESCAPE) {
			setMenuShowing(!getMenuShowing());
			SDL_Delay(200);
		}
	}
	
	if (Engine_MenuShowing) {
		Mix_PauseMusic();
		Menu::GetInstance()->Update();
		Timer::GetInstance()->setmenu(true);
	}

	Input::GetInstance()->interpret(Input::GetInstance()->getElse());
	scale = scale < 0.2 ? 0.2 : scale;
	scale = scale > 1 ? 1 : scale;
	volume = volume < 0 ? 0 : volume;
	volume = volume > SDL_MIX_MAXVOLUME ? MIX_MAX_VOLUME : volume;


}

void Engine::Render()
{

	if (!Engine_MenuShowing or mapIsLoaded) {
		SDL_SetRenderDrawColor(Engine_Renderer, 255, 0, 247, 255);
		SDL_RenderClear(Engine_Renderer);
		
		drawBG("bg", 0);

		Engine_LevelMap->Render(static_cast<int>(Enigine_GameObjects[0]->getPosition()->getX()) / CollisionHandler::GetInstance()->getCollisionLayer()->getTileSize(), static_cast<int>(Enigine_GameObjects[0]->getPosition()->getY()) / CollisionHandler::GetInstance()->getCollisionLayer()->getTileSize());

		UI::GetInstance()->Draw();

		//azert megy hatrafele hogy a player legyen legfelul
		for (int i = Enigine_GameObjects.size() - 1; i >= 0; i--) {
			Enigine_GameObjects[i]->Draw();
		}

		mapIsLoaded = true;
	}
	//?????????????????????????????????????????????????????????????????????
	SDL_RenderSetScale(Engine::GetInstance()->getRenderer(), scale, scale);
	if (getMenuShowing()) { Menu::GetInstance()->Draw(); }
	SDL_RenderPresent(Engine_Renderer);

}

void Engine::drawBG(std::string id, int y)
{
	auto scroll = 0.6;
	auto t = TextureManager::GetInstance()->getTextureMap();
	auto dim = t->find(id)->second.second;


	int x = 0;
	int meg = static_cast<int>(ceil(static_cast<double>(Map_W) / static_cast<double>(dim.w) * scroll)) + 1;
	int alkalom = 0;

	while (alkalom<meg) {
		TextureManager::GetInstance()->DrawBackgroundPicture(id, x, y, dim.w, dim.h, scroll);
		x += dim.w;
		alkalom++;
	}
}

void Engine::Events()
{
	Input::GetInstance()->Listen();
}

int Engine::legmamasabbBlock(int x)
{
	//ha tobb x kockat is meg akarunk nezni akkor nested loop kell imo
	x /= TileSize;

	//int max = 0;
	int i;

	for (i = 1; i < Engine_CollisionLayerVector->size(); i++) {
		if ((*Engine_CollisionLayerVector)[i][x] == 0) { continue; }
		else {
			return (i - 1) * TileSize;
		}
	}

	return (i - 1) * TileSize;
}

bool Engine::spawnolhat(int x, int* y, int w, int h) {
	*y = legmamasabbBlock(x);
	if (x + w < Map_W) {
		int egyszer = legmamasabbBlock(x + w);
		if (*y > egyszer) {
			*y = egyszer;
			x += w;
		}
	}
	x /= TileSize;

	int magassagblock = (*y - h) / TileSize + 1;
	magassagblock = magassagblock < 0 ? 0 : magassagblock;

	if ((*Engine_CollisionLayerVector)[magassagblock][x] == 0) { return true; }
	return false;
}

//ez inkabb tesztkent szolgal, mert igy mindig a bal felso sarokba spawnol
void Engine::spawn(std::string name) {
	Enigine_GameObjects.push_back(ObjectFactory::GetInstance()->CreateObject(name, Engine_PropsMap.find(name)->second));
}

void Engine::spawnSpecial(std::string name, double x, double y, int hp, int power)
{
	spawn(name);
	Enigine_GameObjects[Enigine_GameObjects.size() - 1]->setHP(hp);
	Enigine_GameObjects[Enigine_GameObjects.size() - 1]->setPosition(x, y);
	Enigine_GameObjects[Enigine_GameObjects.size() - 1]->setAttackPower(power);
}

void Engine::map_save() {
	if (Engine_LevelMap->getMapLayers()) {

		int width = Map_W/TileSize;
		int height = Map_H/TileSize;

		mappgen::szoveg(loaded_map_name, width, height, Engine_FloraLayerVector, Engine_BackgroundLayerVector, Engine_CollisionLayerVector);
	}
}
