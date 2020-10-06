#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include "MazeEntity.h"
#include "GeneralGameEntity.h"

struct mazeWall{
        float x_coord;
        float y_coord;
        float length;
        char Orientation;
        };


class Maze : public MazeEntity , public GeneralGameEntity <std::vector<mazeWall>>
{
    public:
        Maze();
        virtual void ReadEntityFromFile() override;
        virtual std::vector<mazeWall> ObjectContainer() const override;
        ~Maze();


    private:
        mazeWall currentWall;
        std::vector<mazeWall>LogicMaze;



};

#endif // MAZE_H
