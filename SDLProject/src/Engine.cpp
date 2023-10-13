#include <iostream>

#include <SDL_image.h>

#include "Engine.hpp"
#include "MapParser.hpp"
#include "ObjectFactory.hpp"
#include "Input.hpp"
#include "FPSCounter.hpp"
#include "Menu.hpp"
#include "Timer.hpp"
#include "Camera.hpp"
#include "TextureManager.hpp"
#include "Rng.hpp"

Engine* Engine::Engine_Instance = nullptr;
RNG* RNG::RNG_Instance = nullptr;

//Player* player = nullptr;

//ez azert van itt hogy az update-be majd lehessen random spawn - de ra kell kerdeznem
//Properties* Player_props = new Properties("player_idle", 100, 240, 240, 0.0, 0.0);
//Properties* Zombie_props = new Properties("zombie_idle", 100, 240, 240, 0.0, 0.0);
//Properties* Skeleton_props = new Properties("skeleton_idle", 100, 240, 240, 100.0, 0.0);

//GameObject* zombie = ObjectFactory::GetInstance()->CreateObject("ZOMBIE", Zombie_props);
//GameObject* skeleton = ObjectFactory::GetInstance()->CreateObject("SKELETON", Skeleton_props);


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

	Music = Mix_LoadMUS("assets/ff_zene.wav");
	if (!Music) {
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
	Engine_Renderer = SDL_CreateRenderer(Engine_Window, -1, SDL_RENDERER_ACCELERATED or SDL_RENDERER_PRESENTVSYNC);
	if (Engine_Renderer == nullptr)
	{
		std::cout << "Failed to CreateRenderer!\n" << SDL_GetError() << std::endl;
		return false;
	}

	//map betoltese
	if (!MapParser::GetInstance()->Load())
	{
		std::cout << "failed to load map\n";
	}

	//itt a map
	Engine_LevelMap = MapParser::GetInstance()->getMap("MAP");

	TextureManager::GetInstance()->ParseTextures("assets/textures.xml");

	//lehet hogy ezt lehetne unique_ptr-el
	Engine_PropsMap.emplace("PLAYER", new Properties("player_idle", 100, 240, 240, 0.0, 0.0));
	Engine_PropsMap.emplace("ZOMBIE", new Properties("zombie_idle", 100, 240, 240, 0.0, 0.0));
	Engine_PropsMap.emplace("SKELETON", new Properties("skeleton_idle", 100, 240, 240, 0.0, 0.0));

	/*Engine_GOMap.emplace("player", ObjectFactory::GetInstance()->CreateObject("PLAYER", Engine_PropsMap.find("player")->second));
	Engine_GOMap.emplace("zombie", ObjectFactory::GetInstance()->CreateObject("ZOMBIE", Engine_PropsMap.find("zombie")->second));
	Engine_GOMap.emplace("skeleton", ObjectFactory::GetInstance()->CreateObject("SKELETON", Engine_PropsMap.find("skeleton")->second));*/


	/*GameObject* player = ObjectFactory::GetInstance()->CreateObject("PLAYER", Player_props);
	GameObject* zombie = ObjectFactory::GetInstance()->CreateObject("ZOMBIE", Zombie_props);
	GameObject* skeleton = ObjectFactory::GetInstance()->CreateObject("SKELETON", Skeleton_props);*/


	Enigine_GameObjects.push_back(ObjectFactory::GetInstance()->CreateObject("PLAYER", Engine_PropsMap.find("PLAYER")->second));	//player a nulladik elem
																																	//Enigine_GameObjects.push_back(mob);
	/*Enigine_GameObjects.push_back(ObjectFactory::GetInstance()->CreateObject("ZOMBIE", Engine_PropsMap.find("ZOMBIE")->second));
	Enigine_GameObjects.push_back(ObjectFactory::GetInstance()->CreateObject("ZOMBIE", Engine_PropsMap.find("ZOMBIE")->second));
	Enigine_GameObjects.push_back(ObjectFactory::GetInstance()->CreateObject("SKELETON", Engine_PropsMap.find("SKELETON")->second));*/

	spawn("ZOMBIE");
	spawn("ZOMBIE");
	spawnSpecial("SKELETON", 5, 1000, 200, 0);
	spawn("SKELETON");

	Camera::GetInstance()->setTarget(Enigine_GameObjects[0]->getOrigin());

	Menu::GetInstance()->MenuInit();

	return Engine_IsRunning = true;
}

bool Engine::Clean()
{
	for (unsigned int i = 0; i != Enigine_GameObjects.size(); i++)
	{
		Enigine_GameObjects[i]->Clean();
	}

	Engine_PropsMap.clear();

	TextureManager::GetInstance()->Clean();
	FPSCounter::GetInstance()->Clean();
	Menu::GetInstance()->Clean();
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
	if (Engine_ResetFlag) {
		Enigine_GameObjects[0]->reset();
		Engine_MenuShowing = false;
		Engine_ResetFlag = false;
	}
	if (!Engine_MenuShowing) {
		Uint64 dt = Timer::GetInstance()->getTimer_DeltaTime();

		if (Engine_SpawnTimer == SPAWN) {
			spawn("ZOMBIE");
			Engine_SpawnTimer -= dt;
			//zombik++;
		}
		else {
			Engine_SpawnTimer -= dt;
		}
		if (Engine_SpawnTimer > SPAWN or Engine_SpawnTimer == 0) {
			Engine_SpawnTimer = SPAWN;
		}
		//std::cout << zombik << "\n";

		for (unsigned int i = 0; i < Enigine_GameObjects.size(); i++)
		{
			//player meghalt
			if (Enigine_GameObjects[0]->getHP() < 0) { Engine_MenuShowing = true; Menu::GetInstance()->setGameOver(true);  Menu::GetInstance()->setMain(false); break; }
			//barmi mas meghalt
			if (Enigine_GameObjects[i]->getHP() <= 0 and i != 0) {
				Enigine_GameObjects.erase(Enigine_GameObjects.begin() + i);
			}
			else {
				//player collisionja mas enemyvel
				if (i != 0) {
					unsigned int mob = i;

					if (CollisionHandler::GetInstance()->CheckCollision(Enigine_GameObjects[0]->getCollider()->getBox(), Enigine_GameObjects[mob]->getCollider()->getBox())) {
						//utes
						if ((Enigine_GameObjects[0]->isAttacking()) and (Enigine_GameObjects[0]->getAttacktime() == PLAYER_ATTACK_TIME - dt)) {
							Enigine_GameObjects[mob]->setHP(Enigine_GameObjects[mob]->getHP() - Enigine_GameObjects[0]->getAttackPower());
						}
					}
				}
				Enigine_GameObjects[i]->Update(dt);
			}
		}


		auto g = Engine_LevelMap->getMapLayers();
		g[0]->getColCount();

		Map_W = g[0]->getColCount() * g[0]->getTileSize();
		Map_H = g[0]->getRowCount() * g[0]->getTileSize();

		Engine_LevelMap->Update();
		Camera::GetInstance()->Update(dt);
		FPSCounter::GetInstance()->Update();

		if (Mix_PlayingMusic())
		{
			Mix_ResumeMusic();
		}
		if (!Mix_PlayingMusic()) {
			Mix_PlayMusic(Music, -1);
		}

		if (Input::GetInstance()->getElse() == SDL_SCANCODE_ESCAPE) {
			setMenuShowing(!getMenuShowing());
			SDL_Delay(200);
		}

		//std::cout<<RNG::GetInstance()->genRandomInt(100)<<"\n";

		std::cout<<Enigine_GameObjects[0]->getPosition()->getX()<<" "<< Enigine_GameObjects[0]->getPosition()->getY() << "\t" << legmamasabbBlock(Enigine_GameObjects[0]->getPosition()->getX())<<"\n";
		//legmamasabbBlock(Enigine_GameObjects[0]->getPosition()->getX());

	}
	
	if (Engine::Engine_MenuShowing) {
		Mix_PauseMusic();
		Menu::GetInstance()->Update();
	}

	Input::GetInstance()->interpret(Input::GetInstance()->getElse());

}

void Engine::Render()
{
	if (!Engine_MenuShowing) {
		TextureManager::GetInstance()->Draw("bg", 0, 0, 7200, 2400, 1.0, 1.0, SDL_FLIP_NONE, 0.5);

		Engine_LevelMap->Render();

		for (unsigned int i = 0; i != Enigine_GameObjects.size(); i++)
		{
			Enigine_GameObjects[i]->Draw();
		}

		FPSCounter::GetInstance()->Draw();
	}
	if (getMenuShowing()) { Menu::GetInstance()->Draw(); }
	SDL_RenderPresent(Engine_Renderer);
}

void Engine::Events()
{
	Input::GetInstance()->Listen();
}

int Engine::legmamasabbBlock(int x)
{
	auto map = CollisionHandler::GetInstance()->getCollisionTileMap();
	int col = CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getColCount();
	//int row = CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getRowCount();
	int size = CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize();

	x /= size;
	std::cout << x << "\n";

	for (int i = 0; i < map->size(); i++) {
		if ((*map)[i][x] == 0) { continue; }
		else {
			return i * size;
		}
	}

	return 1;
}

//ez inkabb tesztkent szolgal, mert igy mindig a bal felso sarokba spawnol
void Engine::spawn(std::string name) {
	Enigine_GameObjects.push_back(ObjectFactory::GetInstance()->CreateObject(name, Engine_PropsMap.find(name)->second));
}

void Engine::spawnSpecial(std::string name, int hp, double x, double y, int power)
{
	spawn(name);
	Enigine_GameObjects[Enigine_GameObjects.size() - 1]->setHP(hp);
	Enigine_GameObjects[Enigine_GameObjects.size() - 1]->setPosition(x, y);
	Enigine_GameObjects[Enigine_GameObjects.size() - 1]->setAttackPower(power);
}