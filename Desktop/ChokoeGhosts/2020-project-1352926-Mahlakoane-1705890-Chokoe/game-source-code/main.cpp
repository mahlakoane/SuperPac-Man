#include <iostream>
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Orientation.h"
#include "ScreenModes.h"
#include "GameWindow.h"
#include "GameMaze.h"
#include "Ghost.h"
#include "PlayerCollisions.h"

using namespace sf;
using width_and_height = std::tuple<float, float>;

width_and_height setUpPacmanSprite(Texture pacmanTexture)
{
    //get the size of pacman texture
    auto [x_pacManTextureSize,y_pacManTextureSize]= pacmanTexture.getSize();

    //get the width and height of each Pac-Man figure to have
    //size of one Pac-Man figure
    float PacMan_Width = x_pacManTextureSize /= Constants::PACMMAN_SPRITESHEET_COLS;
    float PacMan_Height = y_pacManTextureSize /= Constants::PACMAN_SPRITESHEET_ROWS;

    return {PacMan_Width, PacMan_Height};
}

//This function rotates the sprite with respect to its current orientation
void setOrientation(Sprite& pacman, Orientation& orientation)
{
    switch(orientation)
    {

    case Orientation::FACE_LEFT:
        pacman.setRotation(180);
        break;
    case Orientation::FACE_RIGHT:
        pacman.setRotation(0);
        break;
    case Orientation::FACE_UP:
        pacman.setRotation(270);
        break;
    case Orientation::FACE_DOWN:
        pacman.setRotation(90);
        break;
    default:
        break;
    }
}

void updatePacmanSprite (Orientation orientation, Player& player, Sprite& pacman)
{
    player.setEntityMoveDirection(orientation);
    setOrientation(pacman, orientation);
    player.moveEntity();
    player.isEntityInsideTheMaze();

    auto newPlayerPos = player.getEntityPosition();

    auto x_newPlayerPos = std::get<0>(newPlayerPos);
    auto y_newPlayerPos = std::get<1>(newPlayerPos);

    pacman.setPosition(x_newPlayerPos, y_newPlayerPos);

}

//This function moves the pacman around the screen
void pacmanMovement(Player& player, Sprite& pacman)
{
    if(Keyboard::isKeyPressed(Keyboard::Key::Up))
    {
        auto pacmanOrientation = Orientation::FACE_UP;
        updatePacmanSprite(pacmanOrientation, player, pacman);
    }
    else if(Keyboard::isKeyPressed(Keyboard::Key::Down))
    {
        auto pacmanOrientation = Orientation::FACE_DOWN;
        updatePacmanSprite(pacmanOrientation, player, pacman);
    }
    else if(Keyboard::isKeyPressed(Keyboard::Key::Right))
    {
        auto pacmanOrientation = Orientation::FACE_RIGHT;
        updatePacmanSprite(pacmanOrientation, player, pacman);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::Left))
    {
        auto pacmanOrientation = Orientation::FACE_LEFT;
        updatePacmanSprite(pacmanOrientation, player, pacman);
    }
}

void ghostMovement(Ghost& ghost, Sprite& blinky)
{
    auto initialDir = ghost.getEntityMoveDirection();
    ghost.setEntityMoveDirection(initialDir);
    ghost.moveEntity();

    auto [x_newGhostPos, y_newGhostPos] = ghost.getEntityPosition();
    blinky.setPosition(x_newGhostPos, y_newGhostPos);
}

int main()
{
    auto screenWidth = Constants::SCREEN_WIDTH;
    auto screenHeight = Constants::SCREEN_HEIGHT;

    auto screenMode = ScreenModes::SPLASH_SCREEN;

    float InkyX=Constants::INKY_START_XPOS;
    float InkyY=Constants::INKY_START_YPOS;
    float BlinkyX=Constants::BLINKY_START_XPOS;
    float BlinkyY=Constants::BLINKY_START_YPOS;
    float PinkyX=Constants::PINKY_START_XPOS;
    float PinkyY=Constants::PINKY_START_YPOS;
    float ClydeX=Constants::CLYDE_START_XPOS;
    float ClydeY= Constants::CLYDE_START_YPOS;

    //declaration of ghost objects
    auto Inky = Ghost{InkyX,InkyY};
    auto Pinky = Ghost{PinkyX,PinkyY };
    auto Blinky = Ghost{BlinkyX,BlinkyY };
    auto Clyde = Ghost{ClydeX,ClydeY};

    auto initial_direction=Orientation::FACE_UP;
    Inky.setEntityMoveDirection(initial_direction);
    Blinky.setEntityMoveDirection(initial_direction);
    Pinky.setEntityMoveDirection(initial_direction);
    Clyde.setEntityMoveDirection(initial_direction);

    RenderWindow window(VideoMode(screenWidth, screenHeight), "Super Pac-Man");
    auto player = Player{Orientation::FACE_RIGHT};
    window.setFramerateLimit(120);  /// Avoiding adaptive refresh rates.
    auto EntireMaze=GameMaze{};
    auto KeyObject=EntireMaze.MazeKeys();
    auto KeyVec=KeyObject.ObjectContainer();
    auto FoodObject=EntireMaze.MazeFoods();
    auto FoodVec=FoodObject.ObjectContainer();
    auto MazeWallsObject=EntireMaze.mazeWalls();
    auto mazeVec=MazeWallsObject.ObjectContainer();
    auto PelletObject=EntireMaze.MazePellets();
    auto PelletVec=PelletObject.ObjectContainer();
    auto DoorsObject=EntireMaze.mazeDoors();
    auto DoorVec=DoorsObject.ObjectContainer();
    auto CurrentGame = GameWindow{window};

    auto collisions = PlayerCollisions{};

    RectangleShape splashScreen(Vector2f(screenWidth, screenHeight));
    RectangleShape gameScreen(Vector2f(screenWidth, screenHeight));
    RectangleShape winnerScreen(Vector2f(screenWidth, screenHeight));
    RectangleShape loserScreen(Vector2f(screenWidth, screenHeight));

    //loading textures
    Texture splashScreenTexture;
    if(!splashScreenTexture.loadFromFile("Resources/SplashScreen.png")) {}
    splashScreen.setTexture(&splashScreenTexture);

    Texture winnerScreenTexture;
    if(!winnerScreenTexture.loadFromFile("Resources/WinnerScreen.png")) {}
    winnerScreen.setTexture(&winnerScreenTexture);

    Texture loserScreenTexture;
    if(!loserScreenTexture.loadFromFile("Resources/LoserScreen.png")) {}
    loserScreen.setTexture(&loserScreenTexture);

    Texture pacmanTexture;
    if(!pacmanTexture.loadFromFile("Resources/pacmansprites.png")) {}

    Texture blinkyTexture;
    if(!blinkyTexture.loadFromFile("Resources/blinky.png")) {}

    Texture pinkyTexture;
    if(!pinkyTexture.loadFromFile("Resources/pinky.png")) {}

    Texture inkyTexture;
    if(!inkyTexture.loadFromFile("Resources/inky.png")) {}

    Texture clydeTexture;
    if(!clydeTexture.loadFromFile("Resources/clyde.png")) {}

    auto [PacMan_Width, PacMan_Height] = setUpPacmanSprite(pacmanTexture);

    //get the uv co-ordinates of the texture
    //IntRect has x and y offset, also the pacman width and height (index start from 0)
    //we choose where we want to access our sprite sheet using uv co-ordinates
    IntRect rectPlayerSprite(PacMan_Width * 3, PacMan_Height * 0, PacMan_Width, PacMan_Height);
    Sprite pacman(pacmanTexture, rectPlayerSprite);

    //loading textures into sprite objects
    Sprite blinkySprite;
    blinkySprite.setTexture(blinkyTexture);

    Sprite pinkySprite;
    pinkySprite.setTexture(pinkyTexture);

    Sprite inkySprite;
    inkySprite.setTexture(inkyTexture);

    Sprite clydeSprite;
    clydeSprite.setTexture(clydeTexture);

    pacman.setOrigin(Constants::MOVING_OBJECT_X_ORIGIN, Constants::MOVING_OBJECT_Y_ORIGIN);
    pacman.setPosition(Constants::PLAYER_START_XPOS, Constants::PLAYER_START_YPOS);

    inkySprite.setOrigin(Constants::MOVING_OBJECT_X_ORIGIN, Constants::MOVING_OBJECT_Y_ORIGIN);
    inkySprite.setPosition(Constants::INKY_START_XPOS, Constants::INKY_START_YPOS);

    blinkySprite.setOrigin(Constants::MOVING_OBJECT_X_ORIGIN, Constants::MOVING_OBJECT_Y_ORIGIN);
    blinkySprite.setPosition(Constants::BLINKY_START_XPOS, Constants::BLINKY_START_YPOS);

    pinkySprite.setOrigin(Constants::MOVING_OBJECT_X_ORIGIN, Constants::MOVING_OBJECT_Y_ORIGIN);
    pinkySprite.setPosition(Constants::PINKY_START_XPOS, Constants::PINKY_START_YPOS);

    clydeSprite.setOrigin(Constants::MOVING_OBJECT_X_ORIGIN, Constants::MOVING_OBJECT_Y_ORIGIN);
    clydeSprite.setPosition(Constants::CLYDE_START_XPOS, Constants::CLYDE_START_YPOS);

    Clock clock; //for animation

    while(window.isOpen())
    {
        Event evnt;
        window.clear();

        while(window.pollEvent(evnt))
        {
            if(evnt.type == evnt.Closed)
                window.close();
            else if(evnt.type == Event::KeyPressed)
            {
                if(screenMode == ScreenModes::SPLASH_SCREEN && Keyboard::isKeyPressed(Keyboard::Enter))
                    screenMode = ScreenModes::PLAY_SCREEN;
            }
        }

        if (screenMode == ScreenModes::SPLASH_SCREEN)
        {
            window.clear(Color::Black);
            window.draw(splashScreen);
        }
        else if(screenMode==ScreenModes::GAMEOVER_WIN)
            {
               window.clear(Color::Black);
               window.draw(winnerScreen);
            }
        else if (screenMode==ScreenModes::GAMEOVER_LOSE)
            {
               window.clear(Color::Black);
               window.draw(loserScreen);

            }
        else if (screenMode == ScreenModes::PLAY_SCREEN)
        {
            window.clear(Color::Black);


            //animation
            if(clock.getElapsedTime().asSeconds() > Constants::REFRESH_FRAME_RATE)
            {
                if(rectPlayerSprite.left == (PacMan_Width * 4))
                    rectPlayerSprite.left = (PacMan_Width * 3);
                else
                    rectPlayerSprite.left += PacMan_Width;

                pacman.setTextureRect(rectPlayerSprite);
                clock.restart();
            }

            window.draw(pacman);
            window.draw(inkySprite);
            window.draw(pinkySprite);
            window.draw(blinkySprite);
            window.draw(clydeSprite);
            ghostMovement(Blinky, blinkySprite);
            ghostMovement(Inky,inkySprite);
            ghostMovement(Pinky,pinkySprite);
            ghostMovement(Clyde,clydeSprite);

            pacmanMovement(player, pacman);
            auto playerPosition=player.getEntityPosition();

            ///CollisionDetection
            collisions.GhostAndWalls(Blinky,playerPosition,mazeVec);
            collisions.GhostAndWalls(Inky,playerPosition,mazeVec);
            collisions.GhostAndWalls(Pinky,playerPosition,mazeVec);
            collisions.GhostAndWalls(Clyde,playerPosition,mazeVec);
            collisions.GhostAndDoors(Blinky,playerPosition,DoorVec);
            collisions.GhostAndDoors(Inky,playerPosition,DoorVec);
            collisions.GhostAndDoors(Pinky,playerPosition,DoorVec);
            collisions.GhostAndDoors(Clyde,playerPosition,DoorVec);
            collisions.DoPlayerAndWallsCollide(player,mazeVec);
            collisions.playerAndKeys(player,KeyVec,DoorVec);
            collisions.playerVsFood(player,FoodVec);
            collisions.playerAndPellets(player,PelletVec);
            collisions.playerAndDoors(player,DoorVec);


            ///draw Maze Objects
            CurrentGame.drawMazeWalls(mazeVec);
            CurrentGame.drawKeys(KeyVec);
            CurrentGame.drawFoods(FoodVec);
            CurrentGame.drawPellets(PelletVec);
            CurrentGame.drawDoors(DoorVec);

            if(collisions.GhostAndPlayer(Blinky,player) || collisions.GhostAndPlayer(Pinky,player) ||
               collisions.GhostAndPlayer(Inky,player) || collisions.GhostAndPlayer(Clyde,player))
            {
              screenMode=ScreenModes::GAMEOVER_LOSE;
             }

            if(FoodVec.size()==0){screenMode=ScreenModes::GAMEOVER_WIN;}

        }

        window.display(); //displaying the pacman to the screen

    }

    return 0;
}

