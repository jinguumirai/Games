#ifndef GAMESTATUS_H_
#define GAMESTATUS_H_
#include "GameLib2D.hpp"
#include "base.hpp"
class GameStatus: public Base
{
    protected:
    GameLib2D::Framework2D * const frame_instance;
    
    public:
    GameStatus(GameLib2D::Framework2D * const);
    virtual Base * update(Base * const) override = 0;
    virtual ~GameStatus();
};
#endif