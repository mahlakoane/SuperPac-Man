#ifndef PLAYERCOLLISIONS_H
#define PLAYERCOLLISIONS_H
#include "GameMaze.h"
#include "Player.h"

using VectorOfMazeWallStructs=std::vector<mazeWall>;
using TuplePositionVecctor=std::vector<x_and_y>;
using VectorOfDoorStructs=std::vector<MazeDoorComponents>;
using VectorOfPelletStructs=std::vector<PelletProperties>;

class PlayerCollisions
{
    public:
        PlayerCollisions();
        void DoPlayerAndWallsCollide(Player& currentPlayer,VectorOfMazeWallStructs& WallVec); ///Player is not a fixed property, it changes
        void playerAndKeys(Player& currentPlayer,TuplePositionVecctor& KeyVec,VectorOfDoorStructs& DoorVec);
        void playerVsFood(Player& currentPlayer,TuplePositionVecctor& FoodBoxes);
        void playerAndDoors(Player& currentPlayer,VectorOfDoorStructs& DoorVec);
        void playerAndPellets(Player& currentPlayer,VectorOfPelletStructs& pelletVec);
        void GhostAndWalls(Ghost& GhostInstance,x_and_y& playerPos,VectorOfMazeWallStructs& WallVec);
        void GhostAndDoors(Ghost& currentGhost,x_and_y& playerPos,VectorOfDoorStructs& DoorVec);
        bool GhostAndPlayer(Ghost& currentGhost,Player& currentPlayer);
        bool Intersects(BoundingBox& Box1,BoundingBox& Box2);
        ~PlayerCollisions();

    private:
        void HandleWallCollison(BoundingBox& MazeBox,BoundingBox& ObjectBox,Player& PacMan);
        void HandleGhostAndWallCollison(BoundingBox& MazeBox,BoundingBox& ObjectBox,Ghost& GhostInstance);


};

#endif // PLAYERCOLLISIONS_H
