#ifndef GHOST_H
#define GHOST_H
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <cmath>
#include <set>
#include <tuple>
#include <cfloat>
#include <vector>
#include "Orientation.h"
#include "MovableEntity.h"
#include "GeneralGameEntity.h"
#include "Player.h"


using x_and_y = std::tuple<float, float>;






class Ghost : public MovableEntity <Orientation>,public GeneralGameEntity <BoundingBox>
{
public:
    Ghost(float& xStartPos, float& yStartPos);
    virtual x_and_y getEntityPosition() const override;
    virtual x_and_y getSizeOfEntity() const override;
    void setEntityMoveDirection(Orientation& orientation);
    virtual Orientation getEntityMoveDirection() const override;
    virtual void moveEntity() override;
    virtual void isEntityInsideTheMaze() override;
    virtual void setEntityPosition(float x, float y) override;
    virtual BoundingBox ObjectContainer() const override;


private:
    Orientation ghostMoveDirection_;
    float ghostWidth_;
    float ghostHeight_;
    float x_ghostPos_;
    float y_ghostPos_;
    BoundingBox GhostBox;
    float movementStep_;


};

#endif // GHOST_H
