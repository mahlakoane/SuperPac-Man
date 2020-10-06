#ifndef MOVABLEENTITY_H
#define MOVABLEENTITY_H

#include <tuple>

using x_and_y = std::tuple<float, float>;
using gridXPos_and_gridYPos = std::tuple<int, int>;

template <typename ReturnType>
class MovableEntity
{
    public:
        MovableEntity() {}
        virtual x_and_y getEntityPosition() const=0;
        virtual x_and_y getSizeOfEntity() const=0;
        virtual void setEntityMoveDirection(ReturnType& orientation)=0;
        virtual ReturnType getEntityMoveDirection() const=0;
        virtual void isEntityInsideTheMaze()=0;
        virtual void setEntityPosition(float x, float y)=0;
        virtual void moveEntity()=0;


        ~MovableEntity() {}

    private:
};

#endif // MOVABLEENTITY_H
