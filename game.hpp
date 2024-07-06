#ifndef GAME_H_
#define GAME_H_
#include"GameLib2D.hpp"

class GameStatus;

class Game
{
private:
    GameStatus * game_status;
    Game(GameLib2D::Framework2D * const framework);
    static Game * game;
    GameLib2D::Framework2D * frame_instance;
public:
    /// @brief this function would create a instance of Game if instances do not exist. If 
    /// a instance exists, this function would return this instance
    /// @param framework pointer of the GameLib2D::Framework2D
    /// @return the pointer of the instance of Game
    static Game * instance(GameLib2D::Framework2D * const framework);
    void update();
    virtual ~Game();
};

#endif
