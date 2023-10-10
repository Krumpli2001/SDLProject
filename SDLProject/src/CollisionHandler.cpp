#include "CollisionHandler.hpp"
#include "Engine.hpp"
//#include "Player.hpp"

CollisionHandler* CollisionHandler::CollisionHandler_Instance = nullptr;

CollisionHandler::CollisionHandler()
{
    CollisionHandler_CollisionLayer = (TileLayer*)Engine::GetInstance()->getLevelMap()->getMapLayers().back();
    CollisionHandler_CollitionTileMap = CollisionHandler_CollisionLayer->getTileMap();
};

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool x_overlaps = (a.x < b.x + b.w) and (a.x + a.w > b.x);
    bool y_overlaps = (a.y < b.y + b.h) and (a.y + a.h > b.y);
    return (x_overlaps and y_overlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a)
{
    int tileSize = CollisionHandler_CollisionLayer->getTileSize();
    int rowCount = CollisionHandler_CollisionLayer->getRowCount();
    int colCount = CollisionHandler_CollisionLayer->getColCount();

    //ezek itt coordinaatak
    int left_tile = a.x / tileSize; //karakter legbaloldalibb pixele
    int right_tile = (a.x + a.w) / tileSize; //karakter legjobboldalibb pixele

    int top_tile = a.y / tileSize;//karakter legfelso pixele
    int bottom_tile = (a.y + a.h) / tileSize; //karakter legalso pixele

    //map szelei
    if (left_tile < 0) { left_tile = 0; }
    if (right_tile > colCount) { right_tile = colCount; }

    if (top_tile < 0) { top_tile = 0; }
    if (bottom_tile > rowCount) { bottom_tile = rowCount; }

    if ((a.x < 0) || ((a.x + a.w) >= (colCount * tileSize)) || (a.y < 0) || ((a.y + a.h) >= (rowCount * tileSize))) { return true; }

    auto O = Engine::GetInstance()->getGameObjects();
    

    for (int i = left_tile; i <= right_tile; i++)
    {
        for (int j = top_tile; j <= bottom_tile; j++)
        {
            if (CollisionHandler_CollitionTileMap[j][i] > 0)
            {
                if (CollisionHandler_CollitionTileMap[bottom_tile][left_tile] == 12 and CollisionHandler_CollitionTileMap[bottom_tile][right_tile] == 12 ) { //a viz id-ja
                    for(int i = 0; i<O.size(); i++){ O[i]->setGravity(0.3); }
                    return false;
                }
                else {
                    for (int i = 0; i < O.size(); i++) {
                        if (CollisionHandler_CollitionTileMap[bottom_tile - 1][right_tile] == 12) { O[i]->setGravity(0.3); }
                        else { O[i]->setGravity(1); }
                    }
                    return true;
                }
            }
        }
    }

    return false;
}