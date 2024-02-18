#include "Itemdata.hpp"
//#include "Tiles.hpp"
#include "tinyxml.h"

bool ItemData::ParseData(std::string src)
{
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
                std::string ItemType = data->GetText();

                if (ItemType == "Block") {
                    data = data->NextSiblingElement();
                    auto ItemID = std::stoi(data->GetText());

                    data = data->NextSiblingElement();
                    std::string Name = data->GetText();

                    data = data->NextSiblingElement();
                    auto TileID = std::stoi(data->GetText());

                    Block* item = new Block(ItemID, Name, TileID);
                    IData[ItemID] = item;
                    SData[Name] = item;
                    TIDData[TileID] = item;
                }

            }

            if (e->Value() == std::string("block")) {
                //a gettext nullptr-t terit vissza ures stringre aka akkor crashel - gondolom a stdstring constructora behal tole
                // 
                //tehat ki kell tolteni a fajlt - vagy majd kesobb lehet adok neki vmi defaultot

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
                TData[TileID] = tile;
                TSData[TileName] = tile;
            }
        }
    }
}

std::string ItemData::getTileNameFromID(int key)
{
    return TData.find(key)->second->TileName;
}

int ItemData::getTileIDFromName(std::string key) {
    return TSData.find(key)->second->TileID;
}

Tile* ItemData::getTileDataFromID(int key) {
    return TData.find(key)->second;
}
Tile* ItemData::getTileDataFromName(std::string key) {
    return TSData.find(key)->second;
}

void ItemData::ClearData()
{
    for (auto it = IData.begin(); it != IData.end(); it++) {
        delete it->second;
    }
    for (auto it = TData.begin(); it != TData.end(); it++) {
        delete it->second;
    }
    //IData.clear();
}
