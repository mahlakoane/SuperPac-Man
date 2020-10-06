#include "Ghost.h"

Ghost::Ghost(float& xStartPos, float& yStartPos) ///but constants are being parsed here, in main
{
    this->x_ghostPos_ = xStartPos;
    this->y_ghostPos_ = yStartPos;

    this->movementStep_ = 0.1f;

    this->ghostWidth_ = Constants::MOVING_OBJECT_WIDTH;
    this->ghostHeight_ = Constants::MOVING_OBJECT_HEIGHT;

    GhostBox.BoxLength=ghostWidth_;
    GhostBox.BoxHeight=ghostHeight_;
}

x_and_y Ghost::getEntityPosition() const
{
    return {x_ghostPos_, y_ghostPos_};
}

x_and_y Ghost::getSizeOfEntity() const
{
    return {ghostWidth_, ghostHeight_};
}

void Ghost::setEntityPosition(float x, float y)
{
    x_ghostPos_ = x;
    y_ghostPos_ = y;

    GhostBox.xTopLeft=x-Constants::MOVING_OBJECT_X_ORIGIN;
    GhostBox.yTopLeft=y-Constants::MOVING_OBJECT_Y_ORIGIN;

}



void Ghost::setEntityMoveDirection(Orientation& ghostDirection)
{
    ghostMoveDirection_=ghostDirection;
}

void Ghost::moveEntity()
{
    //int ori = static_cast<int>(ghostMoveDirection_);
    //std::cout<<ori<<std::endl;

    auto [x_ghostPos, y_ghostPos] = getEntityPosition();


    if (ghostMoveDirection_ == Orientation::FACE_LEFT )
    {
        x_ghostPos -= movementStep_;

    }
    if (ghostMoveDirection_ == Orientation::FACE_RIGHT )
    {
        x_ghostPos += movementStep_;

    }

    if (ghostMoveDirection_ == Orientation::FACE_UP )
    {
        y_ghostPos -= movementStep_;

    }

    if (ghostMoveDirection_ == Orientation::FACE_DOWN )
    {
        y_ghostPos += movementStep_;

    }


    setEntityPosition(x_ghostPos, y_ghostPos);


}
void Ghost::isEntityInsideTheMaze()
{

}

BoundingBox Ghost::ObjectContainer() const
{
  return GhostBox;
}

Orientation Ghost::getEntityMoveDirection() const
{
    return ghostMoveDirection_;
}

