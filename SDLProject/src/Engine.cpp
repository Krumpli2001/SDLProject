#include <iostream>

#include <SDL_image.h>

#include "Engine.hpp"
#include "MapParser.hpp"
#include "ObjectFactory.hpp"
#include "Input.hpp"
#include "FPSCounter.hpp"

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
		std::cout << "Failed to inicialise!\n" << SDL_GetError();
		return false;
	}
	TTF_Init();

	//ablak letrehozasa
	Engine_Window = SDL_CreateWindow("Jatek", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CREATION_WIDTH, CREATION_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (Engine_Window == nullptr)
	{
		std::cout << "Failed to CreateWindow!\n" << SDL_GetError();
		return false;
	}

	//renderer letrehozasa
	Engine_Renderer = SDL_CreateRenderer(Engine_Window, -1, SDL_RENDERER_ACCELERATED or SDL_RENDERER_PRESENTVSYNC);
	if (Engine_Renderer == nullptr)
	{
		std::cout << "Failed to CreateRenderer!\n" << SDL_GetError();
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

	////pl background
	//TextureManager::GetInstance()->Load("bg", "assets/Forest_background_1.png");

	Properties* props = new Properties("player_idle", 240, 240, 0.0, 0.0);
	GameObject* player = ObjectFactory::GetInstance()->CreateObject("PLAYER", props);

	//Player* player = new Player(new Properties("player_idle", 240, 240, 0.0, 0.0));

	//Enemy* mob = new Enemy(new Properties("boos_idle", 360, 360, 500.0, 0.0));

	Enigine_GameObjects.push_back(player);
	//Enigine_GameObjects.push_back(mob);

	Camera::GetInstance()->setTarget(player->getOrigin());

	return Engine_IsRunning = true;
}

bool Engine::Clean()
{
	for (unsigned int i = 0; i != Enigine_GameObjects.size(); i++)
	{
		Enigine_GameObjects[i]->Clean();
	}

	TextureManager::GetInstance()->Clean();
	SDL_DestroyRenderer(Engine_Renderer);
	SDL_DestroyWindow(Engine_Window);
	FPSCounter::GetInstance()->clean();
	IMG_Quit();
	SDL_Quit();
	return false;
}

void Engine::Quit()
{
	Engine_IsRunning = false;
}

void Engine::Update()
{
	double dt = Timer::GetInstance()->getTimer_DeltaTime();

	for (unsigned int i = 0; i != Enigine_GameObjects.size(); i++)
	{
		Enigine_GameObjects[i]->Update(dt);
	}

	Engine_LevelMap->Update();

	Camera::GetInstance()->Update(dt);
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(Engine_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(Engine_Renderer);

	TextureManager::GetInstance()->Draw("bg", 0, 0, 7200, 2400, 1.0, 1.0, SDL_FLIP_NONE, 0.5);

	Engine_LevelMap->Render();

	for (unsigned int i = 0; i != Enigine_GameObjects.size(); i++)
	{
		Enigine_GameObjects[i]->Draw();
	}

	FPSCounter::GetInstance()->kiir();
	SDL_RenderPresent(Engine_Renderer);
}

void Engine::Events()
{
	Input::GetInstance()->Listen();
}