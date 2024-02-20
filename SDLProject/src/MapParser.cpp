#include "MapParser.hpp"
#include "Engine.hpp"

MapParser* MapParser::MapParser_Instance = nullptr;

bool MapParser::Parse(std::string id, std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error())
    {
        std::cerr << "Failed to load: " << source << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    int rowcount;
    int colcount;
    int tilesize;

    root->Attribute("width", &colcount);
    root->Attribute("height", &rowcount);
    root->Attribute("tilewidth", &tilesize);


    std::vector<Tileset> tilesets;

    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("tileset") )
        {
            tilesets.push_back(ParseTileset(e));
        }
    }

    int i = 0;
    GameMap* gamemap = new GameMap();
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("layer"))
        {
            TileLayer* tilelayer = ParseTileLayer(e, &tilesets, tilesize, rowcount, colcount);
            gamemap->GameMap_MapLayers.push_back(tilelayer);
        }

        if (e->Value() == std::string("layer")) {
            std::string str;
            str = e->Attribute("name");
            if (str == "foreground") {
                Engine::GetInstance()->setCollisionLayer(i);
            }
            if (str == "background") {
                Engine::GetInstance()->setBackgroundLayer(i);
            }
            if (str == "flora") {
                Engine::GetInstance()->setFloraLayer(i);
            }
            i++;
        }
    }

    MapParser_GameMap = gamemap;
    MapParsed = true;
    return true;

}

//tileset id - 0 = semmi, mindegyik layer-ben
    //ha egy adott layer-nek tile-janak az id-jet akarjuk ugy, amit a tiled is ir akkor ki kell vonni a "firstgid - 1"-et
    //illetve az utolso tile-id pedig a firstgid + tilecount - 1

    //doksibol:
    //https://doc.mapeditor.org/en/stable/reference/global-tile-ids/

    //Every tileset has its own, independent local tile IDs, typically(but not always)
    //starting at 0. To avoid conflicts within maps using multiple tilesets, GIDs are
    //assigned in sequence based on the size of each tileset.Each tileset is assigned a
    //firstgid within the map, this is the GID that the tile with local ID 0 in the tileset would have.
    //To figure out which tileset a tile belongs to, find the tileset that has the
    //largest firstgid that is smaller than or equal to the tile’s GID.
    //Once you have identified the tileset, subtract its firstgid from the tile’s
    //GID to get the local ID of the tile within the tileset.

    //Note: The firstgid of the first tileset is always 1. A GID of 0 in a layer means that cell is empty.

    //As an example, here’s an excerpt from a TMX file with three tilesets :

    //    <tileset firstgid = "1" source = "TilesetA.tsx" / >
    //    <tileset firstgid = "65" source = "TilesetB.tsx" / >
    //    <tileset firstgid = "115" source = "TilesetC.tsx" / >

    //In this map, tiles with GIDs 1 - 64 would be part of TilesetA,
    //tiles with GIDs 65 - 114 would be part of TilesetB, and tiles
    // with GIDs 115 and above would be part of tileset C.A tile with
    //GID 72 would be part of TilesetB since TilesetB has the largest
    //firstgid that’s less than or equal to 72, and its local ID would be 7 (72 - 65).

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
    Tileset tileset;

    tileset.Name = xmlTileset->Attribute("name");

    xmlTileset->Attribute("firstgid", &tileset.FirstID);

    xmlTileset->Attribute("tilecount", &tileset.TileCount);

    tileset.LastID = tileset.FirstID + tileset.TileCount - 1;

    xmlTileset->Attribute("columns", &tileset.ColCount);

    tileset.RowCount = tileset.TileCount / tileset.ColCount;

    xmlTileset->Attribute("tilewidth", &tileset.TileSize);

    TiXmlElement* image = xmlTileset->FirstChildElement();

    tileset.Source = image->Attribute("source");

    return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, std::vector<Tileset>* tilesets, int tilesize, int rowcount, int colcount)
{

    TiXmlElement* data = nullptr;
    for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("data")) {
            data = e;
            break;
        }
    }

    std::string matrix;// (data->GetText());
    if (data) {
        matrix = (data->GetText());
    }
    std::istringstream iss(matrix);
    std::string id;

    std::vector<std::vector<int>> tilemap(rowcount, std::vector<int>(colcount, 0));

    for (int row = 0; row < rowcount; row++)
    {
        for (int col = 0; col < colcount; col++)
        {
            std::getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            if (!iss.good())
            {
                break;
            }
        }
    }

    return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
}

bool MapParser::Load(std::string palyanev)
{
    if (!MapParsed) {
        return Parse("MAP", "saves/" + palyanev + ".tmx");
    }
    else {
        return false;
    }
}

void MapParser::Clean()
{

    MapParser_GameMap->Clean();
    MapParser_GameMap = nullptr;
    MapParsed = false;
}