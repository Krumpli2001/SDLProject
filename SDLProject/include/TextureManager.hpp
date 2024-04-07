#pragma once

#include <iostream>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
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
	static inline TextureManager* GetInstance(bool del = false)
	{
		if (del) {
			if (TextureManager_Instance) {
				delete TextureManager_Instance;
			}
			TextureManager_Instance = nullptr;
			return nullptr;
		}
		if (TextureManager_Instance == nullptr)
		{
			TextureManager_Instance = new TextureManager();
		}
		return TextureManager_Instance;
	}
	
	//inicializálás
	bool Init();

	/// <summary>
	/// szöveg kiírása textúraként a képernyõre
	/// </summary>
	/// <param name="str">maga a kiirandó szög</param>
	/// <param name="x">X koordináta</param>
	/// <param name="y">Y koordináta</param>
	/// <param name="size">betüméret</param>
	/// <param name="width">opcionális: ebbe a változóba kiírja, hogy mi lett a szöveg szélessége a képernyõn</param>
	/// <param name="szin">opcionális: a szöveg színe</param>
	void TCharsOut(const std::string& str, int x, int y, int size, int* width = nullptr, const std::string& szin = "");

	/// <summary>
	/// textúrák betöltése a képfájlokból
	/// </summary>
	/// <param name="id">a textúra neve amivel eltárolásra kerül</param>
	/// <param name="filename">a beolvasandó fájl neve</param>
	/// <returns>a mûvelet sikerességét adja vissza</returns>
	bool Load(std::string id, std::string filename);

	/// <summary>
	/// a textúrák beolvasása
	/// </summary>
	/// <param name="source">az xml fájl amit beolvas, ebben van el tárolva a textúrák nevei és a képfájlok nevei</param>
	/// <returns>a mûvelet sikerességét adja vissza</returns>
	bool ParseTextures(std::string source);

	/// <summary>
	/// a textúra kirajzolása
	/// </summary>
	/// <param name="id">a kirajzolandó textúra neve</param>
	/// <param name="x">a cél x koordinátája, a kép bal felsõ sarka</param>
	/// <param name="y">a cél x koordinátája, a kép bal felsõ sarka</param>
	/// <param name="w">a kép kirajzolni kívánt szélessége</param>
	/// <param name="h">a kép kirajzolni kívánt magassága</param>
	/// <param name="srcx">a forrásképbõl kirajzolandó x koordináta (alapesetben 0)</param>
	/// <param name="srcy">a forrásképbõl kirajzolandó x koordináta (alapesetben 0)</param>
	void Draw(const std::string& id, int x, int y, int w, int h, int srcx = 0, int srcy = 0);

	/// <summary>
	/// egy blokk kirajzolásáéert felelõs függvény
	/// </summary>
	/// <param name="tilesetID">a tile ID-ja</param>
	/// <param name="tilesize">a tile mérete</param>
	/// <param name="x">a cél X koordináta (bal felsõ sarok)</param>
	/// <param name="y">a cél Y koordináta (bal felsõ sarok)</param>
	/// <param name="row">a texture map sora (lényegében scrX)</param>
	/// <param name="frame">a texture map oszlopa (lényegében scrY)</param>
	/// <param name="flip">textúra flippelése</param>
	void DrawTile(const std::string& tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	/// <summary>
	/// a gameObj-ért felelõs függvény
	/// </summary>
	/// <param name="id">a textúra neve neve</param>
	/// <param name="x">a cél X koordináta (bal felsõ sarok)</param>
	/// <param name="y">a cél Y koordináta (bal felsõ sarok)</param>
	/// <param name="w">a textúra szélessége</param>
	/// <param name="h">a textúra magassága</param>
	/// <param name="row">a textúra sora (lényegében scrX)</param>
	/// <param name="frame">a textúra oszlopa/frame-je (lényegében scrY)</param>
	/// <param name="startFrame">a kezdõ frame meghatározása (pl ütésnél, hogy mindig a megfelelõ képrõl induljon)</param>
	/// <param name="scale">zoom skalár</param>
	/// <param name="angle">forgatás szöge</param>
	/// <param name="flip">flip</param>
	/// <param name="flipX">flipX az eltérõ animáció méretek miatt</param>
	/// <param name="flipY">flipY az eltérõ animáció méretek miatt</param>
	void DrawFrame(const std::string& id, double x, double y, int w, int h, int row, int frame, bool startFrame, double scale, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE, int flipX = 0, int flipY = 0);
	
	/// <summary>
	/// Az item-ek kirajzolásáért felelõs függvény
	/// </summary>
	/// <param name="id">a textúra neve</param>
	/// <param name="x">a cél X koordináta (bal felsõ sarok)</param>
	/// <param name="y">a cél Y koordináta (bal felsõ sarok)</param>
	/// <param name="w">a textúra szélessége</param>
	/// <param name="h">a textúra magassága</param>
	/// <param name="srcx">forrás X koordinátája</param>
	/// <param name="srcy">forrás Y koordinátája</param>
	/// <param name="srcw">forrás szélessége</param>
	/// <param name="srch">forrás magassága</param>
	void DrawItem(const std::string& id, int x, int y, int w, int h, int srcx = 0, int srcy = 0, int srcw = 0, int srch = 0);
	
	/// <summary>
	/// background kép kirajzolása (a háttér)
	/// </summary>
	/// <param name="id">a textúra neve</param>
	/// <param name="x">a cél X koordináta (bal felsõ sarok)</param>
	/// <param name="y">a cél Y koordináta (bal felsõ sarok)</param>
	/// <param name="srcw">a textúra szélessége</param>
	/// <param name="srch">a textúra magassága</param>
	/// <param name="scrollRatio">meghatározza, hogy milyen gyorsan mozogjon a háttéer a kamerával (pl. 0.5 akkor a háttér fele olyan gyorsan mozog)</param>
	void DrawBackgroundPicture(const std::string& id, int x, int y, int srcw, int srch, double scrollRatio);

	/// <summary>
	/// töröl/felszabadít
	/// </summary>
	/// <param name="id">törölni kívánt textúra</param>
	void Drop(const std::string& id);

	/// <summary>
	/// minden törlése/felszabadítása
	/// </summary>
	void Clean();

	/// <summary>
	/// szöveg felszabadítása
	/// </summary>
	void Clearfont();


	/// <summary>
	/// szín map feltöltése fájlból
	/// </summary>
	/// <param name="source">a szín adatokat tartalmazó fájl neve</param>
	void fillColorMap(std::string source);

	/// <summary>
	/// 
	/// </summary>
	/// <returns>a texturemap pointert</returns>
	inline std::map<std::string, std::pair<SDL_Texture*, dimenziok>>* getTextureMap() { return &TextureManager_TextureMap; }
	

	/// <summary>
	/// 
	/// </summary>
	/// <returns>a szín adaatokat tartalmazó mapot</returns>
	inline std::unordered_map<std::string, SDL_Color>* getColors() { return &colors; }

	/// <summary>
	/// beállítja a szöveg (és minden más) színét
	/// </summary>
	/// <param name="texture">a színezni kívánt textúra</param>
	/// <param name="szin">a kívánt szín</param>
	void setTextColor(SDL_Texture* texture, const std::string& szin);
};