#include "PlayerCollisions.h"
//#include <iostream>
#include <cstdlib>

PlayerCollisions::PlayerCollisions()
{

}

void PlayerCollisions::DoPlayerAndWallsCollide(Player& currentPlayer,VectorOfMazeWallStructs& WallVec)
{
    float wall=10;
    BoundingBox MazeWallBox;
    auto CurrentBox = currentPlayer.ObjectContainer();
    bool resultHorizontal=false;
    bool resultVertical=false;
    BoundingBox WallCollidedWith;


    for(auto WallBox : WallVec)
    {

        MazeWallBox.xTopLeft=WallBox.x_coord;
        MazeWallBox.yTopLeft=WallBox.y_coord;

        if(WallBox.Orientation=='h')
        {
            MazeWallBox.BoxLength=WallBox.length;
            MazeWallBox.BoxHeight=wall;
            resultHorizontal=Intersects(CurrentBox,MazeWallBox);
            if(resultHorizontal)
            {
                WallCollidedWith=MazeWallBox;
                break;
            }

        }
        if(WallBox.Orientation=='v')
        {

            MazeWallBox.BoxLength=wall;
            MazeWallBox.BoxHeight=WallBox.length;
            resultVertical=Intersects(CurrentBox,MazeWallBox);
            if(resultVertical)
            {
                WallCollidedWith=MazeWallBox;
                break;
            }

        }


    }

    if(resultHorizontal)
    {
        HandleWallCollison(WallCollidedWith,CurrentBox,currentPlayer);
    }
    if(resultVertical)
    {
        HandleWallCollison(WallCollidedWith,CurrentBox,currentPlayer);
    }
}

void PlayerCollisions::playerAndKeys(Player& currentPlayer,TuplePositionVecctor& KeyVec,VectorOfDoorStructs& DoorVec)
{
    auto CurrentBox = currentPlayer.ObjectContainer();
    float height=27;
    float width=21;
    BoundingBox keyBox;
    int KeyCount=0;
    keyBox.BoxLength=width;
    keyBox.BoxHeight=height;
    bool Collided=false;


    for(auto key : KeyVec)
    {

        keyBox.xTopLeft=std::get<0>(key);
        keyBox.yTopLeft=std::get<1>(key);

        Collided=Intersects(CurrentBox,keyBox);
        if(Collided)
        {
            break;
        }
        KeyCount++;
    }
    if(Collided)
    {
        KeyVec.erase(begin(KeyVec)+KeyCount);

        srand(time(NULL));
        //The last door in doorVec is The door to the box where the ghosts are enclosed at the start.
        int RandomNum1=rand()%(DoorVec.size()-2);
        int RandomNum2=rand()%(DoorVec.size()-2);
        DoorVec.erase(begin(DoorVec)+RandomNum1);
        DoorVec.erase(begin(DoorVec)+RandomNum2);

    }

}


void PlayerCollisions::playerAndDoors(Player& currentPlayer,VectorOfDoorStructs& DoorVec)
{
    auto CurrentBox = currentPlayer.ObjectContainer();
    float height=5;
    float width=37;
    BoundingBox doorBox;
    bool DoorCollisionHorizontal=false;
    bool DoorCollisionVertical=false;
    int DoorCount=0;

    for(auto door : DoorVec)
    {
        doorBox.xTopLeft=door.x_coord;
        doorBox.yTopLeft=door.y_coord;

        if(door.orientation=='h')
        {
            doorBox.BoxLength=width;
            doorBox.BoxHeight=height;

            DoorCollisionHorizontal=Intersects(CurrentBox,doorBox);
            if(DoorCollisionHorizontal)
            {
                break;
            }

        }
        if(door.orientation=='v')
        {

            doorBox.BoxLength=height;
            doorBox.BoxHeight=width;
            DoorCollisionVertical=Intersects(CurrentBox,doorBox);

            if(DoorCollisionVertical)
            {
                break;
            }
        }
        DoorCount++;
    }
    if(DoorCollisionHorizontal)
    {
        HandleWallCollison(doorBox,CurrentBox,currentPlayer);
    }
    if(DoorCollisionVertical)
    {
        HandleWallCollison(doorBox,CurrentBox,currentPlayer);
    }

}

void PlayerCollisions::playerVsFood(Player& currentPlayer,TuplePositionVecctor& FoodBoxes)
{
    auto CurrentBox = currentPlayer.ObjectContainer();
    float height=27;
    float width=25;

    BoundingBox FoodBox;
    FoodBox.BoxLength=width;
    FoodBox.BoxHeight=height;
    int elementCounter=0;
    bool result=false;


    for(auto food : FoodBoxes)
    {
        FoodBox.xTopLeft=std::get<0>(food);
        FoodBox.yTopLeft=std::get<1>(food);
        result=Intersects(CurrentBox,FoodBox);
        if(result)
        {
            break;
        }
        elementCounter++;
    }

    if(result)
    {
        FoodBoxes.erase(begin(FoodBoxes)+elementCounter);
    }

}

void PlayerCollisions::playerAndPellets(Player& currentPlayer,VectorOfPelletStructs& pelletVec)
{
    auto CurrentBox = currentPlayer.ObjectContainer();
    float  superPelletLength=28;
    float superPelletHeight=29;
    float  normalPelletLength=24;
    float normalPelletHeight=21;
    BoundingBox pelletBox;
    bool NormalPelletCollision=false;
    bool SuperPelletCollision=false;
    int PelletCount=0;

    for(auto pellet : pelletVec)
    {


        if(pellet.PelletType=='n')
        {
            pelletBox.xTopLeft=pellet.x_coord;
            pelletBox.yTopLeft=pellet.y_coord;
            pelletBox.BoxLength=normalPelletLength;
            pelletBox.BoxHeight=normalPelletHeight;

            NormalPelletCollision=Intersects(CurrentBox,pelletBox);

            if(NormalPelletCollision)
            {
                break;
            }

        }
        if(pellet.PelletType=='s')
        {

            pelletBox.xTopLeft=pellet.x_coord;
            pelletBox.yTopLeft=pellet.y_coord;
            pelletBox.BoxLength=superPelletLength;
            pelletBox.BoxHeight=superPelletHeight;
            SuperPelletCollision=Intersects(CurrentBox,pelletBox);

            if(SuperPelletCollision)
            {
                break;
            }
        }
        PelletCount++;
    }
    if(NormalPelletCollision)
    {
        pelletVec.erase(begin(pelletVec)+PelletCount);
    }
    if(SuperPelletCollision)
    {
        pelletVec.erase(begin(pelletVec)+PelletCount);
    }

}
void PlayerCollisions::GhostAndWalls(Ghost& GhostInstance,x_and_y& playerPos,VectorOfMazeWallStructs& WallVec)
{
    float wall=10;
    BoundingBox MazeWallBox;
    auto CurrentBox = GhostInstance.ObjectContainer();
    bool resultHorizontal=false;
    bool resultVertical=false;
    BoundingBox WallCollidedWith;
    Orientation GhostDir;


    for(auto WallBox : WallVec)
    {

        MazeWallBox.xTopLeft=WallBox.x_coord;
        MazeWallBox.yTopLeft=WallBox.y_coord;

        if(WallBox.Orientation=='h')
        {
            MazeWallBox.BoxLength=WallBox.length;
            MazeWallBox.BoxHeight=wall;
            resultHorizontal=Intersects(CurrentBox,MazeWallBox);//collision with vertical wall?
            if(resultHorizontal)
            {
                WallCollidedWith=MazeWallBox;
                GhostDir=GhostInstance.getEntityMoveDirection();
                break;
            }

        }
        if(WallBox.Orientation=='v')
        {

            MazeWallBox.BoxLength=wall;
            MazeWallBox.BoxHeight=WallBox.length;
            resultVertical=Intersects(CurrentBox,MazeWallBox);
            if(resultVertical)
            {
                WallCollidedWith=MazeWallBox;
                GhostDir=GhostInstance.getEntityMoveDirection();
                break;
            }

        }


    }

    if(resultHorizontal)
    {
        HandleGhostAndWallCollison(WallCollidedWith,CurrentBox,GhostInstance);
        auto [xg,yg]=GhostInstance.getEntityPosition();
        auto [xp,yp]=playerPos;
        float y_diff=yp-yg;
        float x_diff=xp-xg;

        if(y_diff>0)
        {
            auto Direction=Orientation::FACE_DOWN;
            GhostInstance.setEntityMoveDirection(Direction);
        }
        else if(y_diff<0)
        {
            auto Direction=Orientation::FACE_UP;
            GhostInstance.setEntityMoveDirection(Direction);
        }
        if(x_diff>0)
        {
            auto Direction=Orientation::FACE_RIGHT;
            GhostInstance.setEntityMoveDirection(Direction);
        }
        else if(x_diff<0)
        {
            auto Direction=Orientation::FACE_LEFT;
            GhostInstance.setEntityMoveDirection(Direction);
        }
        else
        {
            Orientation Dir1=Orientation::FACE_UP;
            GhostInstance.setEntityMoveDirection(Dir1);
        }

    }
    if(resultVertical)
    {
        HandleGhostAndWallCollison(WallCollidedWith,CurrentBox,GhostInstance);
        auto [xg,yg]=GhostInstance.getEntityPosition();
        auto [xp,yp]=playerPos;
        float x_diff=xp-xg;
        float y_diff=yp-yg;
        if(x_diff>0)
        {
            auto Direction=Orientation::FACE_RIGHT;
            GhostInstance.setEntityMoveDirection(Direction);
        }
        else if(x_diff<0)
        {
            auto Direction=Orientation::FACE_LEFT;
            GhostInstance.setEntityMoveDirection(Direction);
        }
        if(y_diff>0) // vertical wall, we are concerned with vertical motion
        {
            auto Direction=Orientation::FACE_DOWN;
            GhostInstance.setEntityMoveDirection(Direction);
        }
        else
        {
            auto Direction=Orientation::FACE_UP;
            GhostInstance.setEntityMoveDirection(Direction);
        }
    }

}

void PlayerCollisions::GhostAndDoors(Ghost& currentGhost,x_and_y& playerPos,VectorOfDoorStructs& DoorVec)
{
    auto CurrentBox = currentGhost.ObjectContainer();
    float height=5;
    float width=37;
    BoundingBox doorBox;
    bool DoorCollisionHorizontal=false;
    bool DoorCollisionVertical=false;
    int DoorCount=0;
    Orientation GhostDir;

    for(auto door : DoorVec)
    {

        doorBox.xTopLeft=door.x_coord;
        doorBox.yTopLeft=door.y_coord;

        if(door.orientation=='h')
        {
            doorBox.BoxLength=width;
            doorBox.BoxHeight=height;

            DoorCollisionHorizontal=Intersects(CurrentBox,doorBox);
            if(DoorCollisionHorizontal)
            {
                GhostDir=currentGhost.getEntityMoveDirection();
                break;
            }

        }
        if(door.orientation=='v')
        {

            doorBox.BoxLength=height;
            doorBox.BoxHeight=width;
            DoorCollisionVertical=Intersects(CurrentBox,doorBox);

            if(DoorCollisionVertical)
            {
                GhostDir=currentGhost.getEntityMoveDirection();
                break;
            }
        }
        DoorCount++;
    }
    if(DoorCollisionHorizontal && DoorCount!= 32)  //32 is the position of the last door
    {
        HandleGhostAndWallCollison(doorBox,CurrentBox,currentGhost);
        auto [xg,yg]=currentGhost.getEntityPosition();
        auto [xp,yp]=playerPos;
        //auto Direction=setGhostDirection(GhostDir,GhostPos,playerPos);
        float x_diff=xp-xg;
        float y_diff=yp-yg;
        if(x_diff>0)
        {
            auto Direction=Orientation::FACE_RIGHT;
            currentGhost.setEntityMoveDirection(Direction);
        }
        else
        {
            auto Direction=Orientation::FACE_LEFT;
            currentGhost.setEntityMoveDirection(Direction);
        }
    }
    if(DoorCollisionVertical && DoorCount!= 32)
    {
        HandleGhostAndWallCollison(doorBox,CurrentBox,currentGhost);
        auto [xg,yg]=currentGhost.getEntityPosition();
        auto [xp,yp]=playerPos;
        //auto Direction=setGhostDirection(GhostDir,GhostPos,playerPos);
        float x_diff=xp-xg;
        float y_diff=yp-yg;
        if(y_diff>0)
        {
            auto Direction=Orientation::FACE_DOWN;
            currentGhost.setEntityMoveDirection(Direction);
        }
        else
        {
            auto Direction=Orientation::FACE_UP;
            currentGhost.setEntityMoveDirection(Direction);
        }
    }


}

bool PlayerCollisions::GhostAndPlayer(Ghost& currentGhost,Player& currentPlayer)
{
    auto GhostBox= currentGhost.ObjectContainer();
    auto PlayerBox= currentPlayer.ObjectContainer();
    bool GhostAndPlayerCollision=Intersects(PlayerBox,GhostBox);
    return GhostAndPlayerCollision;
}

//Check collision between any two bounding boxes
bool PlayerCollisions::Intersects(BoundingBox& Box1,BoundingBox& Box2) ///collision between bounding boxes, works fine
{
    if((Box1.xTopLeft<=(Box2.xTopLeft+Box2.BoxLength)) && ((Box1.xTopLeft+Box1.BoxLength)>=Box2.xTopLeft) &&
            (Box1.yTopLeft<=(Box2.yTopLeft+Box2.BoxHeight)) && ((Box1.yTopLeft+Box1.BoxHeight)>=Box2.yTopLeft))
    {
        return true;
    }
    return false;
}


void PlayerCollisions::HandleWallCollison(BoundingBox& MazeBox,BoundingBox& ObjectBox,Player& PacMan)
{
    auto [x,y]=PacMan.getEntityPosition();
    ///The Objects operated on in this function have already collided
    auto MazeLeftXBoundary=MazeBox.xTopLeft;
    auto MazeRightXBoundary=MazeLeftXBoundary+MazeBox.BoxLength;
    auto MazeTopYBoundary=MazeBox.yTopLeft;
    auto MazeBottomYBoundary=MazeTopYBoundary+MazeBox.BoxHeight;

    auto ObjectLeftXBoundary=ObjectBox.xTopLeft;
    auto ObjectRightXBoundary=ObjectLeftXBoundary+ObjectBox.BoxLength;
    auto ObjectTopYBoundary=ObjectBox.yTopLeft;
    auto ObjectBottomYBoundary=ObjectTopYBoundary+ObjectBox.BoxHeight;

    auto PlayerOrientation=PacMan.getEntityMoveDirection();

    auto RepositioningValue=15; ///The value used to undo the y or x value of the collision


    //Boundaries & orientation
    if(MazeRightXBoundary>=ObjectLeftXBoundary && PlayerOrientation==Orientation::FACE_LEFT)
    {
        //counter the motion of player/Movable Object to the Left
        PacMan.setEntityPosition(MazeRightXBoundary+RepositioningValue,y);
    }
    if(MazeLeftXBoundary<=ObjectRightXBoundary && PlayerOrientation==Orientation::FACE_RIGHT)
    {
        //Stop the player/movable Object from moving to the Right,past the boundary
        PacMan.setEntityPosition(MazeLeftXBoundary-RepositioningValue,y);
    }
    if(MazeTopYBoundary<=ObjectBottomYBoundary && PlayerOrientation==Orientation::FACE_DOWN)
    {
        //Top to Bottom
        PacMan.setEntityPosition(x,MazeTopYBoundary-RepositioningValue);
    }
    if(MazeBottomYBoundary>=ObjectTopYBoundary && PlayerOrientation==Orientation::FACE_UP)
    {
        //Bottom to Top
        PacMan.setEntityPosition(x,MazeBottomYBoundary+RepositioningValue);
    }

}

void PlayerCollisions::HandleGhostAndWallCollison(BoundingBox& MazeBox,BoundingBox& ObjectBox,Ghost& GhostInstance)
{
    auto [x,y]=GhostInstance.getEntityPosition();
    ///The Objects operated on in this function have already collided
    auto MazeLeftXBoundary=MazeBox.xTopLeft;
    auto MazeRightXBoundary=MazeLeftXBoundary+MazeBox.BoxLength;
    auto MazeTopYBoundary=MazeBox.yTopLeft;
    auto MazeBottomYBoundary=MazeTopYBoundary+MazeBox.BoxHeight;

    auto ObjectLeftXBoundary=ObjectBox.xTopLeft;
    auto ObjectRightXBoundary=ObjectLeftXBoundary+ObjectBox.BoxLength;
    auto ObjectTopYBoundary=ObjectBox.yTopLeft;
    auto ObjectBottomYBoundary=ObjectTopYBoundary+ObjectBox.BoxHeight;

    auto GhostOrientation=GhostInstance.getEntityMoveDirection();

    auto RepositioningValue=15; ///The value used to undo the y or x value of the collision


    //Boundaries & orientation
    if(MazeRightXBoundary>=ObjectLeftXBoundary && GhostOrientation==Orientation::FACE_LEFT)
    {
        //counter the motion of player/Movable Object to the Left
        GhostInstance.setEntityPosition(MazeRightXBoundary+RepositioningValue,y);
    }
    if(MazeLeftXBoundary<=ObjectRightXBoundary && GhostOrientation==Orientation::FACE_RIGHT)
    {
        //Stop the player/movable Object from moving to the Right,past the boundary
        GhostInstance.setEntityPosition(MazeLeftXBoundary-RepositioningValue,y);
    }
    if(MazeTopYBoundary<=ObjectBottomYBoundary && GhostOrientation==Orientation::FACE_DOWN)
    {
        //Top to Bottom
        GhostInstance.setEntityPosition(x,MazeTopYBoundary-RepositioningValue);
    }
    if(MazeBottomYBoundary>=ObjectTopYBoundary && GhostOrientation==Orientation::FACE_UP)
    {
        //Bottom to Top
        GhostInstance.setEntityPosition(x,MazeBottomYBoundary+RepositioningValue);
    }

}




PlayerCollisions::~PlayerCollisions()
{

}
