#include "Itemdata.hpp"
#include "Tiles.hpp"
#include "tinyxml.h"

bool ItemData::ParseItemData(std::string src)
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
                    auto ItemID = std::atoi(data->GetText());

                    data = data->NextSiblingElement();
                    std::string Name = data->GetText();

                    data = data->NextSiblingElement();
                    auto TileID = std::atoi(data->GetText());

                    data = data->NextSiblingElement();
                    std::string TextureID = data->GetText();

                    Block* item = new Block(ItemID, Name, TextureID, TileID);
                    IData[ItemID] = item;
                    SData[Name] = item;
                    TIDData[TileID] = item;
                }

            }
        }
    }
}

void ItemData::ClearData()
{
    for (auto it = IData.begin(); it != IData.end(); it++) {
        delete it->second;
    }
    IData.clear();
}
