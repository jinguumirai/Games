#include"GameLib2D.hpp"
#include"game.hpp"


void GameLib2D::Framework2D::update()
{
    Game* games = Game::instance(this);
    games->update();
}


