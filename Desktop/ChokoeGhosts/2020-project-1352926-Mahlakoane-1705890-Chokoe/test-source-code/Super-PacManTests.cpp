#include "../game-source-code/Player.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

//Test cases for the player object
TEST_CASE("The initial orientation of the player is correct")
{
    auto player = Player{Orientation::FACE_RIGHT};
    auto playerOrientation = player.getOrientation();

    CHECK(playerOrientation == Orientation::FACE_RIGHT);
}

TEST_CASE("The initial position of the player is correct")
{
    auto player = Player{Orientation::FACE_RIGHT};
    auto [x_initialPos, y_initialPos] = player.getPlayerPosition();

    CHECK(x_initialPos == Constants::PLAYER_START_XPOS);
    CHECK(y_initialPos == Constants::PLAYER_START_YPOS);
}

TEST_CASE("Player does not go outside the maze edges")
{
    auto player = Player{Orientation::FACE_RIGHT};

    SUBCASE("Player does not go over the left edge")
    {
        auto leftEdge = Constants::LEFT_EDGE;

        for(unsigned int i = 0; i < 300; i++)
        {
            player.setMoveDirection(Orientation::FACE_LEFT);
            player.movePlayer();
            player.isInsideTheMaze();
        }

        auto [new_xPos, new_yPos] = player.getPlayerPosition();

        CHECK(new_xPos >= leftEdge);
    }
    SUBCASE("Player does not go over the right edge")
    {
      auto rightEdge = Constants::RIGHT_EDGE;

      for(unsigned int i = 0; i < 1000; i++)
      {
          player.setMoveDirection(Orientation::FACE_RIGHT);
          player.movePlayer();
          player.isInsideTheMaze();
      }

      auto [new_xPos, new_yPos] = player.getPlayerPosition();

      CHECK(new_xPos <= rightEdge);
    }
    SUBCASE("Player does not go over the top edge")
    {
        auto topEdge = Constants::TOP_EDGE;

        for(unsigned int i = 0; i < 100; i++)
        {
            player.setMoveDirection(Orientation::FACE_UP);
            player.movePlayer();
            player.isInsideTheMaze();
        }

        auto [new_xPos, new_yPos] = player.getPlayerPosition();

        CHECK(new_yPos >= topEdge);
    }
    SUBCASE("Player does not go over the bottom edge")
    {
        auto bottomEdge = Constants::BOTTOM_EDGE;

        for(unsigned int i = 0; i < 100; i++)
        {
            player.setMoveDirection(Orientation::FACE_DOWN);
            player.movePlayer();
            player.isInsideTheMaze();
        }

        auto [new_xPos, new_yPos] = player.getPlayerPosition();

        CHECK(new_yPos <= bottomEdge);
    }
}


