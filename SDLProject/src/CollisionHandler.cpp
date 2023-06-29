#include "CollisionHandler.hpp"
#include "Engine.hpp"

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

    int left_tile = a.x / tileSize;
    int right_tile = (a.x + a.w) / tileSize;

    int top_tile = a.y / tileSize;
    int bottom_tile = (a.y + a.h) / tileSize;

    if (left_tile < 0) { left_tile = 0; }
    if (right_tile > colCount) { right_tile = colCount; }

    if (top_tile < 0) { top_tile = 0; }
    if (bottom_tile > rowCount) { bottom_tile = rowCount; }

    for (int i = left_tile; i <= right_tile; i++)
    {
        for (int j = top_tile; j <= bottom_tile; j++)
        {
            if (CollisionHandler_CollitionTileMap[j][i] > 0)
            {
                return true;
            }
        }
    }

    return false;
}
