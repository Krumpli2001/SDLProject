#include "Itemdata.hpp"
#include "tinyxml.h"

bool ItemData::ParseData(std::string src)
{
	TiXmlDocument xml;
	xml.LoadFile(src);
	if (xml.Error()) {
		std::cout << "Failde to load: " << src << std::endl;
		return false;
	}
	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("item")) {
			TiXmlElement* data = e->FirstChildElement();

			//ID
			int ID = std::stoi(data->GetText());

			//tile nev
			data = data->NextSiblingElement();
			std::string TileName = data->GetText();

			//AttackPower
			data = data->NextSiblingElement();
			int AttackPower = std::stoi(data->GetText());

			//Heal
			data = data->NextSiblingElement();
			int Heal = std::stoi(data->GetText());

			data = data->NextSiblingElement();
			auto MS = std::stoi(data->GetText());


			Item* item = new Tool(ID, TileName, AttackPower, Heal, MS);
			int_ItemData[ID] = item;
			string_ItemData[TileName] = item;

		}

		if (e->Value() == std::string("block")) {
			//a gettext nullptr-t terit vissza ures stringre aka akkor crashel - gondolom a stdstring constructora behal tole
			// 
			//tehat ki kell tolteni a fajlt - vagy majd kesobb lehet adok neki vmi defaultot

			TiXmlElement* data = e->FirstChildElement();

			//id
			auto temp = data->GetText();
			int ID = temp ? std::stoi(temp) : -1;

			//tile nev
			data = data->NextSiblingElement();
			std::string TileName = data->GetText();

			//layer
			data = data->NextSiblingElement();
			std::string Layer = data->GetText();

			//"atlatszo"
			data = data->NextSiblingElement();
			temp = data->GetText();
			bool isTransparent = temp ? std::stoi(temp) : -1;

			data = data->NextSiblingElement();
			temp = data->GetText();
			int mineTime = temp ? std::stoi(temp) : -1;

			data = data->NextSiblingElement();
			temp = data->GetText();
			int MS = temp ? std::stoi(temp) : -1;

			Tile* tile = new Tile(ID, TileName, Layer, isTransparent, mineTime, MS);
			Item* item = new Block(ID, TileName, MS);

			int_ItemData[ID] = item;
			string_ItemData[TileName] = item;

			int_TileData[ID] = tile;
			string_TileData[TileName] = tile;

		}
	}
	return true;
}

std::string ItemData::getTileNameFromID(int key)
{
	return int_TileData.find(key)->second->TileName;
}

int ItemData::getTileIDFromName(std::string key) {
	return string_TileData.find(key)->second->TileID;
}

Tile* ItemData::getTileDataFromID(int key) {
	return int_TileData.find(key)->second;
}

Tile* ItemData::getTileDataFromName(std::string key) {
	return string_TileData.find(key)->second;
}

void ItemData::ClearData()
{
	for (auto it = int_ItemData.begin(); it != int_ItemData.end(); it++) {
		delete it->second;
	}
	for (auto it = int_TileData.begin(); it != int_TileData.end(); it++) {
		delete it->second;
	}
	//int_ItemData.clear();
}
