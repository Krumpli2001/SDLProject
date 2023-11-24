#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <map>

class TextureManager
{
private:
	static TextureManager* TextureManager_Instance;
	std::map<std::string, SDL_Texture*> TextureManager_TextureMap;

public:
	TextureManager() {};
	static inline TextureManager* GetInstance()
	{
		if (TextureManager_Instance == nullptr)
		{
			TextureManager_Instance = new TextureManager();
		}
		return TextureManager_Instance;
	}

	bool Load(std::string id, std::string filename);
	bool ParseTextures(std::string source);
	void Draw(std::string id, int x, int y, int w, int h, double Xscale, double Yscale, SDL_RendererFlip flip = SDL_FLIP_NONE, double ScrollRatio = 0.4);
	void DrawTile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawFrame(std::string id, double x, double y, int w, int h, int row, int frame, bool startFrame, double scale, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Drop(std::string id);
	void Clean();
};