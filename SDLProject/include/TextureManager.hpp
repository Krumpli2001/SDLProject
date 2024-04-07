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
	
	//inicializ�l�s
	bool Init();

	/// <summary>
	/// sz�veg ki�r�sa text�rak�nt a k�perny�re
	/// </summary>
	/// <param name="str">maga a kiirand� sz�g</param>
	/// <param name="x">X koordin�ta</param>
	/// <param name="y">Y koordin�ta</param>
	/// <param name="size">bet�m�ret</param>
	/// <param name="width">opcion�lis: ebbe a v�ltoz�ba ki�rja, hogy mi lett a sz�veg sz�less�ge a k�perny�n</param>
	/// <param name="szin">opcion�lis: a sz�veg sz�ne</param>
	void TCharsOut(const std::string& str, int x, int y, int size, int* width = nullptr, const std::string& szin = "");

	/// <summary>
	/// text�r�k bet�lt�se a k�pf�jlokb�l
	/// </summary>
	/// <param name="id">a text�ra neve amivel elt�rol�sra ker�l</param>
	/// <param name="filename">a beolvasand� f�jl neve</param>
	/// <returns>a m�velet sikeress�g�t adja vissza</returns>
	bool Load(std::string id, std::string filename);

	/// <summary>
	/// a text�r�k beolvas�sa
	/// </summary>
	/// <param name="source">az xml f�jl amit beolvas, ebben van el t�rolva a text�r�k nevei �s a k�pf�jlok nevei</param>
	/// <returns>a m�velet sikeress�g�t adja vissza</returns>
	bool ParseTextures(std::string source);

	/// <summary>
	/// a text�ra kirajzol�sa
	/// </summary>
	/// <param name="id">a kirajzoland� text�ra neve</param>
	/// <param name="x">a c�l x koordin�t�ja, a k�p bal fels� sarka</param>
	/// <param name="y">a c�l x koordin�t�ja, a k�p bal fels� sarka</param>
	/// <param name="w">a k�p kirajzolni k�v�nt sz�less�ge</param>
	/// <param name="h">a k�p kirajzolni k�v�nt magass�ga</param>
	/// <param name="srcx">a forr�sk�pb�l kirajzoland� x koordin�ta (alapesetben 0)</param>
	/// <param name="srcy">a forr�sk�pb�l kirajzoland� x koordin�ta (alapesetben 0)</param>
	void Draw(const std::string& id, int x, int y, int w, int h, int srcx = 0, int srcy = 0);

	/// <summary>
	/// egy blokk kirajzol�s��ert felel�s f�ggv�ny
	/// </summary>
	/// <param name="tilesetID">a tile ID-ja</param>
	/// <param name="tilesize">a tile m�rete</param>
	/// <param name="x">a c�l X koordin�ta (bal fels� sarok)</param>
	/// <param name="y">a c�l Y koordin�ta (bal fels� sarok)</param>
	/// <param name="row">a texture map sora (l�nyeg�ben scrX)</param>
	/// <param name="frame">a texture map oszlopa (l�nyeg�ben scrY)</param>
	/// <param name="flip">text�ra flippel�se</param>
	void DrawTile(const std::string& tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	/// <summary>
	/// a gameObj-�rt felel�s f�ggv�ny
	/// </summary>
	/// <param name="id">a text�ra neve neve</param>
	/// <param name="x">a c�l X koordin�ta (bal fels� sarok)</param>
	/// <param name="y">a c�l Y koordin�ta (bal fels� sarok)</param>
	/// <param name="w">a text�ra sz�less�ge</param>
	/// <param name="h">a text�ra magass�ga</param>
	/// <param name="row">a text�ra sora (l�nyeg�ben scrX)</param>
	/// <param name="frame">a text�ra oszlopa/frame-je (l�nyeg�ben scrY)</param>
	/// <param name="startFrame">a kezd� frame meghat�roz�sa (pl �t�sn�l, hogy mindig a megfelel� k�pr�l induljon)</param>
	/// <param name="scale">zoom skal�r</param>
	/// <param name="angle">forgat�s sz�ge</param>
	/// <param name="flip">flip</param>
	/// <param name="flipX">flipX az elt�r� anim�ci� m�retek miatt</param>
	/// <param name="flipY">flipY az elt�r� anim�ci� m�retek miatt</param>
	void DrawFrame(const std::string& id, double x, double y, int w, int h, int row, int frame, bool startFrame, double scale, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE, int flipX = 0, int flipY = 0);
	
	/// <summary>
	/// Az item-ek kirajzol�s��rt felel�s f�ggv�ny
	/// </summary>
	/// <param name="id">a text�ra neve</param>
	/// <param name="x">a c�l X koordin�ta (bal fels� sarok)</param>
	/// <param name="y">a c�l Y koordin�ta (bal fels� sarok)</param>
	/// <param name="w">a text�ra sz�less�ge</param>
	/// <param name="h">a text�ra magass�ga</param>
	/// <param name="srcx">forr�s X koordin�t�ja</param>
	/// <param name="srcy">forr�s Y koordin�t�ja</param>
	/// <param name="srcw">forr�s sz�less�ge</param>
	/// <param name="srch">forr�s magass�ga</param>
	void DrawItem(const std::string& id, int x, int y, int w, int h, int srcx = 0, int srcy = 0, int srcw = 0, int srch = 0);
	
	/// <summary>
	/// background k�p kirajzol�sa (a h�tt�r)
	/// </summary>
	/// <param name="id">a text�ra neve</param>
	/// <param name="x">a c�l X koordin�ta (bal fels� sarok)</param>
	/// <param name="y">a c�l Y koordin�ta (bal fels� sarok)</param>
	/// <param name="srcw">a text�ra sz�less�ge</param>
	/// <param name="srch">a text�ra magass�ga</param>
	/// <param name="scrollRatio">meghat�rozza, hogy milyen gyorsan mozogjon a h�tt�er a kamer�val (pl. 0.5 akkor a h�tt�r fele olyan gyorsan mozog)</param>
	void DrawBackgroundPicture(const std::string& id, int x, int y, int srcw, int srch, double scrollRatio);

	/// <summary>
	/// t�r�l/felszabad�t
	/// </summary>
	/// <param name="id">t�r�lni k�v�nt text�ra</param>
	void Drop(const std::string& id);

	/// <summary>
	/// minden t�rl�se/felszabad�t�sa
	/// </summary>
	void Clean();

	/// <summary>
	/// sz�veg felszabad�t�sa
	/// </summary>
	void Clearfont();


	/// <summary>
	/// sz�n map felt�lt�se f�jlb�l
	/// </summary>
	/// <param name="source">a sz�n adatokat tartalmaz� f�jl neve</param>
	void fillColorMap(std::string source);

	/// <summary>
	/// 
	/// </summary>
	/// <returns>a texturemap pointert</returns>
	inline std::map<std::string, std::pair<SDL_Texture*, dimenziok>>* getTextureMap() { return &TextureManager_TextureMap; }
	

	/// <summary>
	/// 
	/// </summary>
	/// <returns>a sz�n adaatokat tartalmaz� mapot</returns>
	inline std::unordered_map<std::string, SDL_Color>* getColors() { return &colors; }

	/// <summary>
	/// be�ll�tja a sz�veg (�s minden m�s) sz�n�t
	/// </summary>
	/// <param name="texture">a sz�nezni k�v�nt text�ra</param>
	/// <param name="szin">a k�v�nt sz�n</param>
	void setTextColor(SDL_Texture* texture, const std::string& szin);
};