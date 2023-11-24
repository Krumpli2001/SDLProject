#include "TextureManager.hpp"
#include "Engine.hpp"
#include "Camera.hpp"
#include "tinyxml.h"

TextureManager* TextureManager::TextureManager_Instance = nullptr;

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

	TextureManager_TextureMap[id] = texture;

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
			Load(id, src);
		}
	}
	std::cout << "Textures loaded!\n";
	return true;
}

void TextureManager::Draw(std::string id, int x, int y, int w, int h, double Xscale, double Yscale, SDL_RendererFlip flip, double ScrollRatio)
{
	SDL_Rect srcRect = { 0, 0, w, h };

	Vector2D cam = Camera::GetInstance()->getPosition() * ScrollRatio;

	SDL_Rect dstRect = { x - cam.getX(), y - cam.getY(), w * Xscale, h * Yscale };

	//SDL_Rect dstRect = { x, y, w, h };
	SDL_RenderCopyEx(Engine::GetInstance()->getRenderer(), TextureManager_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { frame * tilesize, row * tilesize, tilesize, tilesize };

	Vector2D cam = Camera::GetInstance()->getPosition();

	SDL_Rect dstRect = { x - cam.getX(), y - cam.getY(), tilesize, tilesize};

	//SDL_Rect dstRect = { x, y, tilesize, tilesize };
	SDL_RenderCopyEx(Engine::GetInstance()->getRenderer(), TextureManager_TextureMap[tilesetID], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, double x, double y, int w, int h, int row, int frame, bool startFrame, double scale, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { w * frame, h * row, w, h };

	Vector2D cam = Camera::GetInstance()->getPosition();

	SDL_Rect dstRect = { x - cam.getX(), y - cam.getY(), w * scale, h * scale };

	//SDL_Rect dstRect = { x, y, w, h };
	SDL_RenderCopyEx(Engine::GetInstance()->getRenderer(), TextureManager_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::Drop(std::string id)
{
	SDL_DestroyTexture(TextureManager_TextureMap[id]);
	TextureManager_TextureMap.erase(id);
}

void TextureManager::Clean()
{
	std::map<std::string, SDL_Texture*>::iterator it;
	for (it = TextureManager_TextureMap.begin(); it != TextureManager_TextureMap.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}
	TextureManager_TextureMap.clear();

	std::cout << "Textures deleted!";
}