#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameMaze.h"
#include "Player.h"


class GameWindow
{
    public:

        GameWindow(sf::RenderWindow& window);
        void drawMazeWalls(std::vector<mazeWall>&currMaze);
        void drawDoors(std::vector<MazeDoorComponents>& doorVec);
        void drawFoods(std::vector<x_and_y>& FoodVec);
        void drawKeys(std::vector<x_and_y>& KeysVec);
        void drawPellets(std::vector<PelletProperties>& PelletVec);

        ~GameWindow();


    private:
       sf::RenderWindow& window_;
       sf::Texture texture;
};

#endif // GAMEWINDOW_H
