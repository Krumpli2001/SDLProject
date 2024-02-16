#include "Tiles.hpp"
#include "tinyxml.h"

//majd meg kell kerdezni
std::string TileData::getTileNameFromID(int key)
{
    return IData.find(key)->second->TileName;
}

int TileData::getTileIDFromName(std::string key) {
    return SData.find(key)->second->TileID;
}

Tile* TileData::getTileDataFromID(int key) {
    return IData.find(key)->second;
}
Tile* TileData::getTileDataFromName(std::string key) {
    return SData.find(key)->second;
}

bool TileData::parseTileData(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error()) {
        std::cout << "Failde to load: " << source << std::endl;
        return false;
    }
    TiXmlElement* root = xml.RootElement();
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("block")) {
            //a gettext nullptr-t terit vissza ures stringre aka akkor crashel - gondolom a stdstring constructora behal tole
            // 
            //tehat ki kell tolteni a fajlt

            //tile nev
            TiXmlElement* data = e->FirstChildElement();
            std::string TileName = data->GetText();

            //id
            data = data->NextSiblingElement();
            auto temp = data->GetText();
            int TileID = temp ? std::stoi(temp) : -1;

            //layerid
            data = data->NextSiblingElement();
            std::string LayerID = data->GetText();

            //"atlatszo"
            data = data->NextSiblingElement();
            temp = data->GetText();
            bool isTransparent = temp ? std::stoi(temp) : -1;

            data = data->NextSiblingElement();
            temp = data->GetText();
            int mineTime = temp ? std::stoi(temp) : -1;

            Tile* tile = new Tile(TileID, TileName, LayerID, isTransparent, mineTime);
            IData[TileID] = tile;
            SData[TileName] = tile;
        }
    }
}

void TileData::ClearData()
{
    for (auto it = IData.begin(); it != IData.end(); it++) {
        delete it->second;
    }
    IData.clear();
}