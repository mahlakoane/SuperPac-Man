#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <vector>
#include <tuple>
#include "MazeEntity.h"
#include "GeneralGameEntity.h"

using x_and_y = std::tuple<float, float>;


class Food : public MazeEntity,public GeneralGameEntity <std::vector<x_and_y>>
{
public:
    Food();
    virtual void ReadEntityFromFile() override;
    virtual std::vector<x_and_y> ObjectContainer() const override;
    ~Food();

private:
    std::vector<x_and_y>Foods;
};

#endif // FOOD_H
