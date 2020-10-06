#include "Player.h"
#include <iostream>

Player::Player(Orientation playerOrientation)
{
    this->playerOrientation_ = playerOrientation;
    this->playerWidth_ = Constants::MOVING_OBJECT_WIDTH;
    this->playerHeight_ = Constants::MOVING_OBJECT_HEIGHT;

    this->movementStep_ = Constants::MOVEMENT_STEP;

    this->x_playerPosition_ = Constants::PLAYER_START_XPOS;
    this->y_playerPosition_ = Constants::PLAYER_START_YPOS;

    CurrentBox.BoxHeight=playerHeight_;
    CurrentBox.BoxLength=playerWidth_;
}

x_and_y Player::getEntityPosition() const
{
    return {x_playerPosition_, y_playerPosition_};
}

x_and_y Player::getSizeOfEntity() const
{
    return {playerWidth_, playerHeight_};
}

void Player::setEntityMoveDirection(Orientation& orientation)
{
    playerOrientation_ = orientation;
}

Orientation Player::getEntityMoveDirection() const
{
    return playerOrientation_;
}

//Function to get the mazeGrid, this is 25 x 24 matrix
vector<vector <int>> Player::getmazeGrid()
{
    this->mazeGrid_ = vector<vector <int>> {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,1},{1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1},
        {1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,1},{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,1},{1,0,1,0,0,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1},
        {1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1},{1,0,0,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,1},
        {1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1},{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1},
        {1,1,1,0,1,1,1,0,1,1,1,0,0,1,1,1,0,1,1,1,0,1,1,1},{1,0,0,0,0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,0,1,1,1,0,1},{1,0,1,1,1,0,1,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,0,1},
        {1,0,1,1,1,0,1,0,1,1,1,0,0,1,1,1,1,1,0,1,1,1,0,1},{1,0,1,1,1,0,1,0,1,0,0,0,0,0,0,1,1,1,0,1,1,1,0,1},
        {1,0,1,1,1,0,1,0,1,0,1,1,1,0,0,1,1,1,0,1,1,1,0,1},{1,0,0,0,0,0,1,0,1,0,1,1,1,0,0,1,1,1,0,0,0,0,0,1},
        {1,0,1,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,1,1,1,0,1},{1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1},
        {1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1},{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

    return mazeGrid_;
}


void Player::moveEntity()
{
    auto playerMoveDirection = getEntityMoveDirection();
    auto [xPlayerPosition, yPlayerPosition] = getEntityPosition();

        switch(playerMoveDirection)
        {
        case Orientation::FACE_LEFT:
            xPlayerPosition -= movementStep_;
            break;
        case Orientation::FACE_RIGHT:
            xPlayerPosition += movementStep_;
            break;
        case Orientation::FACE_UP:
            yPlayerPosition -= movementStep_;
            break;
        case Orientation::FACE_DOWN:
            yPlayerPosition += movementStep_;
            break;
        default:
            break;
        }

    setEntityPosition(xPlayerPosition, yPlayerPosition);
    //set Box coordinate values
    CurrentBox.xTopLeft = x_playerPosition_-Constants::MOVING_OBJECT_X_ORIGIN;
    CurrentBox.yTopLeft = y_playerPosition_-Constants::MOVING_OBJECT_Y_ORIGIN;
}

bool Player::isPacmanOnPath()
{
    auto [pacmanRow, pacmanCol] = getPacmanGridPos();
    auto mazeGrid = getmazeGrid();

    return false;
}

void Player::isEntityInsideTheMaze()
{
    auto [x_playerPos, y_playerPos] = getEntityPosition();

    auto leftEdge = Constants::LEFT_EDGE;
    auto rightEdge = Constants::RIGHT_EDGE;
    auto topEdge = Constants::TOP_EDGE;
    auto bottomEdge = Constants::BOTTOM_EDGE;

    if(y_playerPos > bottomEdge)
        setEntityPosition(x_playerPos, bottomEdge);
    else if(y_playerPos < topEdge)
        setEntityPosition(x_playerPos, topEdge);
    else if (x_playerPos < leftEdge)
        setEntityPosition(leftEdge, y_playerPos);
    else if(x_playerPos > rightEdge)
        setEntityPosition(rightEdge, y_playerPos);
}

////A function to convert pacman global co-ordinates to grid co-ordinates
gridXPos_and_gridYPos Player::getPacmanGridPos()
{
    auto [x_pacmanPos, y_pacmanPos] = getEntityPosition();

    int row_pacmanCell = (y_pacmanPos - Constants::MAZE_Y_OFFSET) / 23;
    int col_pacmanCell = (x_pacmanPos - Constants::MAZE_X_OFFSET) / 22;

    return {row_pacmanCell, col_pacmanCell};
}

void Player::setEntityPosition(float x, float y)
{
    x_playerPosition_ = x;
    y_playerPosition_ = y;
}
BoundingBox Player::ObjectContainer() const
{
  return CurrentBox;
}








