#include "CollisionHandler.hpp"
#include "Engine.hpp"

CollisionHandler* CollisionHandler::CollisionHandler_Instance = nullptr;

CollisionHandler::CollisionHandler()
{
    CollisionHandler_CollisionLayer = (TileLayer*)Engine::GetInstance()->getLevelMap()->getMapLayers()[Engine::GetInstance()->getCollisionLayer()];
    CollisionHandler_CollitionTileMap = CollisionHandler_CollisionLayer->getTileMap();
};

void CollisionHandler::reset() {
    CollisionHandler_CollisionLayer = (TileLayer*)Engine::GetInstance()->getLevelMap()->getMapLayers()[Engine::GetInstance()->getCollisionLayer()];
    CollisionHandler_CollitionTileMap = CollisionHandler_CollisionLayer->getTileMap();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool x_overlaps = (a.x < b.x + b.w) and (a.x + a.w > b.x);
    bool y_overlaps = (a.y < b.y + b.h) and (a.y + a.h > b.y);
    return (x_overlaps and y_overlaps);
}

bool CollisionHandler::MapCollision(GameObject* g)
{
    int tileSize = CollisionHandler_CollisionLayer->getTileSize();
    int rowCount = CollisionHandler_CollisionLayer->getRowCount();
    int colCount = CollisionHandler_CollisionLayer->getColCount();

    //ezek itt coordinaatak
    int left_tile = g->getCollider()->getBox().x / tileSize; //karakter legbaloldalibb pixele
    int right_tile = (g->getCollider()->getBox().x + g->getCollider()->getBox().w) / tileSize; //karakter legjobboldalibb pixele

    int top_tile = g->getCollider()->getBox().y / tileSize;//karakter legfelso pixele
    int bottom_tile = (g->getCollider()->getBox().y + g->getCollider()->getBox().h - 1) / tileSize; //karakter legalso pixele

    //map szelei
    if (left_tile < 0) { left_tile = 0; }
    if (right_tile > colCount) { right_tile = colCount; }

    if (top_tile < 0) { top_tile = 0; }
    if (bottom_tile > rowCount) { bottom_tile = rowCount; }

    if ((g->getCollider()->getBox().x < 0) || ((g->getCollider()->getBox().x + g->getCollider()->getBox().w) >= (colCount * tileSize)) || (g->getCollider()->getBox().y < 0) || ((g->getCollider()->getBox().y + g->getCollider()->getBox().h) >= (rowCount * tileSize))) { return true; }    

    for (int i = left_tile; i <= right_tile; i++)
    {
        for (int j = top_tile; j <= bottom_tile; j++)
        {
            if (CollisionHandler_CollitionTileMap[j][i] > 0)
            {
                if (CollisionHandler_CollitionTileMap[bottom_tile][left_tile] == 12 and CollisionHandler_CollitionTileMap[bottom_tile][right_tile] == 12 ) { //a viz id-ja
                    g->setGravity(0.3);
                    return false;
                }
                else {                    
                    return true;
                }
            }
            g->setGravity(1);
        }
    }
    return false;
}