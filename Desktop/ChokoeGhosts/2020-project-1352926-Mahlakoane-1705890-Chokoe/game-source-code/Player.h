#ifndef PLAYER_H
#define PLAYER_H
#include "Orientation.h"
#include <tuple>
#include "MovableEntity.h"
#include "GeneralGameEntity.h"
#include "Ghost.h"
#include <vector>

using x_and_y = std::tuple<float, float>;
using gridXPos_and_gridYPos = std::tuple<int, int>;
using namespace std;

class Player : public MovableEntity <Orientation>, public GeneralGameEntity <BoundingBox>
{
    public:
        Player(Orientation playerOrientation);
        virtual x_and_y getEntityPosition() const override;
        virtual x_and_y getSizeOfEntity() const override;
        virtual void setEntityMoveDirection(Orientation& orientation) override;
        virtual Orientation getEntityMoveDirection() const override;
        virtual void moveEntity() override;
        virtual void isEntityInsideTheMaze() override;
        virtual void setEntityPosition(float x, float y) override;
        virtual BoundingBox ObjectContainer() const override;


        gridXPos_and_gridYPos getPacmanGridPos();
        vector<vector <int>> getmazeGrid();
        bool isPacmanOnPath();

    private:
        Orientation playerMoveDirection_;
        Orientation playerOrientation_;
        BoundingBox CurrentBox;
        float playerWidth_;
        float playerHeight_;
        float x_playerPosition_;
        float y_playerPosition_;
        float movementStep_;
        vector<vector <int>> mazeGrid_;
        //Ghost ghost_{Constants::BLINKY_START_XPOS, Constants::BLINKY_START_YPOS};
};

#endif // PLAYER_H
