#include"game.hpp"
#include"title.hpp"

Game* Game::game = NULL;
Game::Game(GameLib2D::Framework2D* const fra):frame_instance(fra)
{
    game_status = new Title("pictures/title.png", fra);
}

void Game::update()
{
    frame_instance->record_time();
    Base * now = game_status;
    game_status = dynamic_cast<GameStatus*>(game_status->update(NULL));
    /// if game status changed, delete the previous game status 
    if (game_status != now)
    {
        delete now;
    }
}

Game * Game::instance(GameLib2D::Framework2D * fra)
{
    if (game)
    {
        return game;
    }
    else
    {
        game = new Game(fra);
        return game;
    }
}

Game::~Game()
{
    delete game_status;
}