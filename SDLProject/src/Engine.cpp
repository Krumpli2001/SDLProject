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

Engine* Engine::Engine_Instance = nullptr;
//Player* player = nullptr;

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

	Properties* Pprops = new Properties("player_idle", 100, 240, 240, 0.0, 0.0);
	GameObject* player = ObjectFactory::GetInstance()->CreateObject("PLAYER", Pprops);

	Properties* Zprops = new Properties("zombie_idle", 100, 240, 240, 0.0, 0.0);
	GameObject* zombie = ObjectFactory::GetInstance()->CreateObject("ZOMBIE", Zprops);


	Enigine_GameObjects.push_back(player); //player a nulladik elem
	//Enigine_GameObjects.push_back(mob);
	Enigine_GameObjects.push_back(zombie);

	Camera::GetInstance()->setTarget(player->getOrigin());

	Menu::GetInstance()->MenuInit();

	return Engine_IsRunning = true;
}

bool Engine::Clean()
{
	for (unsigned int i = 0; i != Enigine_GameObjects.size(); i++)
	{
		Enigine_GameObjects[i]->Clean();
	}

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
	if (!Engine_MenuShowing) {
		Uint64 dt = Timer::GetInstance()->getTimer_DeltaTime();

		for (unsigned int i = 0; i < Enigine_GameObjects.size(); i++)
		{
			if (Enigine_GameObjects[i]->getHP() <= 0 and i != 0) {
				Enigine_GameObjects.erase(Enigine_GameObjects.begin() + i);
			}
			else {
				//bool collision = false;
				//unsigned int mob;
				if (i != 0) {
					unsigned int mob = i;
					bool collision = CollisionHandler::GetInstance()->CheckCollision(Enigine_GameObjects[0]->getCollider()->getBox(), Enigine_GameObjects[mob]->getCollider()->getBox());
					std::cout << collision<<"\n";
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
	}
	
	if (Engine::Engine_MenuShowing) {
		Mix_PauseMusic();
		Menu::GetInstance()->Update();
	}

	//Input::GetInstance()->interpret(Input::GetInstance()->getElse());

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