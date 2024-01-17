#include "Tiles.hpp"
#include "tinyxml.h"

//binary search
int TileData::getTileIdFromName(std::string key)
{
    auto talalat = Data.find(key);
    return talalat->second->TileID;
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
            TiXmlElement* data = e->FirstChildElement();
            std::string TileName = data->GetText();

            data = data->NextSiblingElement();
            auto temp = data->GetText();
            int TileID = temp ? std::atoi(temp) : -1;

            data = data->NextSiblingElement();
            temp = data->GetText();
            int LayerID = temp ? std::atoi(temp) : -1;

            data = data->NextSiblingElement();
            temp = data->GetText();
            bool isTransparent = temp ? std::atoi(temp) : -1;

            Tile* tile = new Tile(TileID, LayerID, isTransparent);
            Data[TileName] = tile;
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