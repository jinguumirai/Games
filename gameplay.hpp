#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_
#include"GameLib2D.hpp"
#include"gamestatus.hpp"

class PlayStatus;
class Play;
class Pause;
class GamePlay: public GameStatus
{
    private:
    Play * const play;
    Pause * const pause;
    PlayStatus * play_status;

    public:
    GamePlay(const char * alienware_path, const char* boat_path, GameLib2D::Framework2D * const fra);
    virtual Base * update(Base* const) override;
    virtual ~GamePlay();
};
#endif