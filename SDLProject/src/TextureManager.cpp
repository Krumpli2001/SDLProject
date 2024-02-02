#include "SDL_ttf.h"

#include "TextureManager.hpp"
#include "Engine.hpp"
#include "Camera.hpp"
#include "tinyxml.h"

TextureManager* TextureManager::TextureManager_Instance = nullptr;



bool TextureManager::Init()
{
	//tudom hogy sok az ismetles, nem akartam kulon fuggvenyt irni csak erre
	TTF_Font* font = TTF_OpenFont("assets/cambria.ttf", 12);
	for (char i = '0'; i <= '9'; i++) {
		SDL_Color color = { 255, 255, 255 };
		std::string str{ i };
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, str.c_str(), color);
		SDL_Texture* Message = SDL_CreateTextureFromSurface(Engine::GetInstance()->getRenderer(), surfaceMessage);

		chars_map[i] = Message;
		SDL_FreeSurface(surfaceMessage);
	}
	std::cout << "numbers made\n";

	for (char i = 'a'; i <= 'z'; i++) {
		SDL_Color color = { 255, 255, 255 };
		std::string str{ i };
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, str.c_str(), color);
		SDL_Texture* Message = SDL_CreateTextureFromSurface(Engine::GetInstance()->getRenderer(), surfaceMessage);

		chars_map[i] = Message;
		SDL_FreeSurface(surfaceMessage);
	}
	std::cout << "chars made\n";

	for (char i = 'A'; i <= 'Z'; i++) {
		SDL_Color color = { 255, 255, 255 };
		std::string str{ i };
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, str.c_str(), color);
		SDL_Texture* Message = SDL_CreateTextureFromSurface(Engine::GetInstance()->getRenderer(), surfaceMessage);

		chars_map[i] = Message;
		SDL_FreeSurface(surfaceMessage);
	}
	std::cout << "CHARS MADE\n";

	TTF_CloseFont(font);

	return true;
}

bool TextureManager::Load(std::string id, std::string filename)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface == nullptr)
	{
		std::cout << "Failed to IMG_Load! \n" << filename << SDL_GetError();
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->getRenderer(), surface);
	if (texture == nullptr)
	{
		std::cout << "Failed to SDL_CreateTextureFromSurface! \n" << filename << SDL_GetError();
		return false;
	}

	dimenziok d = { surface->w/frames, surface->h };

	auto data = std::make_pair(texture, d);

	TextureManager_TextureMap[id] = data;
	SDL_FreeSurface(surface);
	return true;
}

bool TextureManager::ParseTextures(std::string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);
	if (xml.Error())
	{
		std::cout << "Failde to load: " << source << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("texture"))
		{
			std::string id = e->Attribute("id");
			std::string src = e->Attribute("source");
			if (e->Attribute("frames")) {
				frames = std::atoi(e->Attribute("frames"));
			}
			Load(id, src);
		}
	}
	std::cout << "Textures loaded!\n";
	
	return true;
}

//stayonscreen = maradjon a kepernyon ugyan abban a pozicioban
void TextureManager::Draw(std::string id, int x, int y, int w, int h, int srcx, int srcy, bool stayonscreen, SDL_RendererFlip flip, double ScrollRatio)
{
	SDL_Rect srcRect = { srcx, srcy, w, h };
	SDL_Rect dstRect;
	if (stayonscreen) {
		dstRect = { x, y, w, h };
	}
	else {
		Vector2D cam = Camera::GetInstance()->getPosition() * ScrollRatio;
		dstRect = { static_cast<int>(x - cam.getX()), static_cast<int>(y - cam.getY()), w, h };
	}
	

	//SDL_Rect dstRect = { x, y, w, h };
	SDL_RenderCopyEx(Engine::GetInstance()->getRenderer(), TextureManager_TextureMap[id].first, &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
	//+1, -1 azert kell mert az sdl scaling valamit elcsesz a szamolasokba (vagy en cseszek el valamit)
	//a bal oldali tilet egy pixellel kesoob kezdjuk es jobbrol elobb hagyjuk abba
	SDL_Rect srcRect = { frame * tilesize+1, row * tilesize, tilesize-1, tilesize };

	Vector2D cam = Camera::GetInstance()->getPosition();

	SDL_Rect dstRect = { x - cam.getX(), y - cam.getY(), tilesize, tilesize};

	//SDL_Rect dstRect = { x, y, tilesize, tilesize };
	SDL_RenderCopy(Engine::GetInstance()->getRenderer(), TextureManager_TextureMap[tilesetID].first, &srcRect, &dstRect /*0, nullptr, flip*/);
}

void TextureManager::DrawFrame(std::string id, double x, double y, int w, int h, int row, int frame, bool startFrame, double scale, double angle, SDL_RendererFlip flip)
{
	//ez is a scale/clip miatt van, marmint a -1ek
	SDL_Rect srcRect = { w * frame, h * row, w-1, h-1 };

	Vector2D cam = Camera::GetInstance()->getPosition();

	SDL_Rect dstRect = { x - cam.getX(), y - cam.getY(), w * scale, h * scale };

	//SDL_Rect dstRect = { x, y, w, h };
	SDL_RenderCopyEx(Engine::GetInstance()->getRenderer(), TextureManager_TextureMap[id].first, &srcRect, &dstRect, angle, nullptr, flip);
}

void TextureManager::DrawItem(std::string id, int x, int y, int w, int h, int srcx, int srcy, int srcw, int srch)
{
	SDL_Rect srcRect = { srcx, srcy, srcw, srch };
	SDL_Rect dstRect = { x, y, w, h };

	//SDL_Rect dstRect = { x, y, w, h };
	SDL_RenderCopyEx(Engine::GetInstance()->getRenderer(), TextureManager_TextureMap[id].first, &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
}

void TextureManager::Drop(std::string id)
{
	SDL_DestroyTexture(TextureManager_TextureMap[id].first);
	TextureManager_TextureMap.erase(id);
}

void TextureManager::Clean()
{
	//std::map<std::string, std::pair<SDL_Texture*, dimenziok>>::iterator it;
	for (auto it = TextureManager_TextureMap.begin(); it != TextureManager_TextureMap.end(); it++)
	{
		SDL_DestroyTexture(it->second.first);
	}
	TextureManager_TextureMap.clear();

	std::cout << "Textures deleted!\n";

}

void TextureManager::Clearfont()
{
	std::cout << "Numbers deleted!\n";

	for (auto it = chars_map.begin(); it != chars_map.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}
	chars_map.clear();

	std::cout << "Chars deleted!\n";
}
