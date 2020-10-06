#ifndef MAZEDOORS_H
#define MAZEDOORS_H
#include <iostream>
#include <vector>
#include "MazeEntity.h"
#include "GeneralGameEntity.h"

//using x_and_y = std::tuple<float, float>;
struct MazeDoorComponents{
float x_coord;
float y_coord;
char orientation;
};

class Mazedoors : public MazeEntity , public GeneralGameEntity <std::vector<MazeDoorComponents>>
{
    public:
        Mazedoors();
        virtual void ReadEntityFromFile() override;
        virtual std::vector<MazeDoorComponents> ObjectContainer() const override;
        ~Mazedoors();

    private:
        MazeDoorComponents currentDoor;
        std::vector<MazeDoorComponents>mazedoors;
};



#endif // MAZEDOORS_H
