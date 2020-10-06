#ifndef KEYS_H
#define KEYS_H
#include <iostream>
#include <vector>
#include <tuple>
#include "MazeEntity.h"
#include "GeneralGameEntity.h"

using x_and_y = std::tuple<float, float>;


class Keys : public MazeEntity, public GeneralGameEntity<std::vector<x_and_y>>
{
    public:
        Keys();
        virtual void ReadEntityFromFile() override;
        virtual std::vector<x_and_y> ObjectContainer() const override;
        ~Keys();

    private:
        std::vector<x_and_y>KeyVec;
};

#endif // KEYS_H
