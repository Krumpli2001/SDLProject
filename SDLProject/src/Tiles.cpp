#include "Tiles.hpp"
#include "tinyxml.h"

//majd meg kell kerdezni
std::string TileData::getTileNameFromID(int key)
{
    //Data.find(std::pair(0, "semmi"));
    for (auto i = Data.begin(); i != Data.end(); i++) {
        if (i->first.first == key) { return i->first.second; }
    }
}

int TileData::getTileIDFromName(std::string key) {
    for (auto i = Data.begin(); i != Data.end(); i++) {
        if (i->first.second == key) { return i->first.first; }
    }
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
            int TileID = temp ? std::atoi(temp) : -1;

            //layerid
            data = data->NextSiblingElement();
            std::string LayerID = data->GetText();

            //"atlatszo"
            data = data->NextSiblingElement();
            temp = data->GetText();
            bool isTransparent = temp ? std::atoi(temp) : -1;

            Tile* tile = new Tile(LayerID, isTransparent);
            auto key = std::make_pair(TileID, TileName);
            Data[key] = tile;
        }
    }
}

void TileData::ClearData()
{
    for (auto it = Data.begin(); it != Data.end(); it++) {
        delete it->second;
    }
    Data.clear();
}