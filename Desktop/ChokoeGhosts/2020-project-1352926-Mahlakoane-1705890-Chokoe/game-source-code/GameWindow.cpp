#include "GameWindow.h"

using namespace std;
GameWindow::GameWindow(sf::RenderWindow& window):window_{window}
{

}

void GameWindow::drawMazeWalls(std::vector<mazeWall>& currMaze)
{
    for(auto wall : currMaze) ///deal with maze walls
    {
        if(wall.Orientation=='v')
        {
            sf::RectangleShape rect(sf::Vector2f(10.f,wall.length));
            rect.setPosition(sf::Vector2f(wall.x_coord,wall.y_coord));
            window_.draw(rect);

        }
        else if(wall.Orientation=='h')
        {
            sf::RectangleShape rect(sf::Vector2f(wall.length,10.f));
            rect.setPosition(sf::Vector2f(wall.x_coord,wall.y_coord));
            window_.draw(rect);

        }

    }

}


void GameWindow::drawDoors(std::vector<MazeDoorComponents>& doorVec)
{
///deal with doors

    for(auto door : doorVec)
    {
        if(door.orientation=='v')
        {
            sf::RectangleShape currentDoor(sf::Vector2f(5.f,37.f));
            currentDoor.setPosition(sf::Vector2f(door.x_coord,door.y_coord));
            currentDoor.setFillColor(sf::Color(100, 250, 50));
            window_.draw(currentDoor);

        }
        else if(door.orientation=='h')
        {
            sf::RectangleShape currentDoor(sf::Vector2f(37.f,5.f));
            currentDoor.setPosition(sf::Vector2f(door.x_coord,door.y_coord));
            currentDoor.setFillColor(sf::Color(100, 250, 50));
            window_.draw(currentDoor);

        }

    }
}

void GameWindow::drawFoods(std::vector<x_and_y>& FoodVector)
{
    for(auto foodItem : FoodVector)
    {

        if(!texture.loadFromFile("Resources/food.png")) {}
        sf::RectangleShape FoodsRect(sf::Vector2f(25.f,27.f));
        FoodsRect.setTexture(&texture);
        FoodsRect.setPosition(sf::Vector2f(get<0>(foodItem),get<1>(foodItem)));
        window_.draw(FoodsRect);


    }

}

void GameWindow::drawKeys(std::vector<x_and_y>& KeysVec)
{

    for(auto nthKey : KeysVec)
    {
        if(!texture.loadFromFile("Resources/key.png"))
        {
            break;
        }
        sf::RectangleShape KeyRect(sf::Vector2f(21.f,27.f));
        KeyRect.setTexture(&texture);
        KeyRect.setPosition(sf::Vector2f(get<0>(nthKey),get<1>(nthKey)));
        window_.draw(KeyRect);
    }


}

void GameWindow::drawPellets(std::vector<PelletProperties>& PelletVec)
{

    for(auto nthPellet : PelletVec) ///deal with maze walls
    {
        switch(nthPellet.PelletType)
        {

        case 's':
        {
            if(!texture.loadFromFile("Resources/SuperPellet.png"))
            {
                break;
            }
            sf::RectangleShape SuperPellet(sf::Vector2f(28.f,29.f));
            SuperPellet.setTexture(&texture);
            SuperPellet.setPosition(sf::Vector2f(nthPellet.x_coord,nthPellet.y_coord));
            window_.draw(SuperPellet);
            break;
        }

        case 'n':
        {
            if(!texture.loadFromFile("Resources/normalPellet.png"))
            {
                break;
            }
            sf::RectangleShape NormalPellet(sf::Vector2f(24.f,21.f));
            NormalPellet.setTexture(&texture);
            NormalPellet.setPosition(sf::Vector2f(nthPellet.x_coord,nthPellet.y_coord));
            window_.draw(NormalPellet);
            break;
        }

        default:
        {

            break;
        }


        }
    }
}



GameWindow::~GameWindow()
{

}
