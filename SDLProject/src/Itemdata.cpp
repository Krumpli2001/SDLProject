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

                //ID
                auto temp = data->GetText();
                int ID = temp ? std::stoi(temp) : -1;

                //tile nev
                data = data->NextSiblingElement();
                std::string TileName = data->GetText();

                //std::string ItemType = data->GetText();

                //if (ItemType == "Block") {
                //    data = data->NextSiblingElement();
                //    auto ItemID = std::stoi(data->GetText());

                //    data = data->NextSiblingElement();
                //    std::string Name = data->GetText();

                //    data = data->NextSiblingElement();
                //    auto TileID = std::stoi(data->GetText());

                //    Block* item = new Block(ItemID, Name, TileID);
                //    int_ItemData[ItemID] = item;
                //    string_ItemData[Name] = item;
                //    //int_TileData[TileID] = item;
                //}

                Item* item = new Tool(ID, TileName);
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


                //"atlatszo"
                data = data->NextSiblingElement();
                temp = data->GetText();
                bool isTransparent = temp ? std::stoi(temp) : -1;

                data = data->NextSiblingElement();
                temp = data->GetText();
                int mineTime = temp ? std::stoi(temp) : -1;

                Tile* tile = new Tile(ID, TileName, isTransparent, mineTime);
                Item* item = new Block(ID, TileName);

                int_ItemData[ID] = item;
                string_ItemData[TileName] = item;

                int_TileData[ID] = tile;
                string_TileData[TileName] = tile;

                //int_TileData[ID] = tile;
                //string_TileData[TileName] = tile;
            }
        }
    }
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
