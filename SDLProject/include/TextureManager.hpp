#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <unordered_map>

struct dimenziok {
	int w, h;
};

class TextureManager
{
private:
	static TextureManager* TextureManager_Instance;
	std::map<std::string, std::pair<SDL_Texture*, dimenziok>> TextureManager_TextureMap;
	std::map<char, std::pair<SDL_Texture*, dimenziok>> chars_map;
	std::unordered_map<std::string, SDL_Color> colors;
	int frames{};
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

	bool Init();

	void TCharsOut(std::string str, int x, int y, int size, int* width = nullptr, std::string szin="");

	bool Load(std::string id, std::string filename);
	bool ParseTextures(std::string source);
	void Draw(std::string id, int x, int y, int w, int h, int srcx = 0, int srcy = 0, bool stayonscreen = false, SDL_RendererFlip flip = SDL_FLIP_NONE, double ScrollRatio = 0.4);
	void DrawTile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawFrame(std::string id, double x, double y, int w, int h, int row, int frame, bool startFrame, double scale, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawItem(std::string id, int x, int y, int w, int h, int srcx = 0, int srcy = 0, int srcw = 0, int srch = 0);
	void Drop(std::string id);
	void Clean();
	void Clearfont();

	void fillColorMap(std::string source);

	inline std::map<std::string, std::pair<SDL_Texture*, dimenziok>>* getTextureMap() { return &TextureManager_TextureMap; }

	inline std::unordered_map<std::string, SDL_Color>* getColors() { return &colors; }

	void setTextColor(SDL_Texture* texture, std::string szin);
};