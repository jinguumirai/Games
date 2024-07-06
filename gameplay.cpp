#include"gameplay.hpp"
#include"play.hpp"
#include"pause.hpp"

GamePlay::GamePlay(const char * alien_image_path, const char * boats_image_path, GameLib2D::Framework2D * const fra):
GameStatus(fra), play(new Play(alien_image_path, boats_image_path, fra)), pause(new Pause("pictures/pause.png", fra))
{
    play_status = play;
}

Base * GamePlay::update(Base * const base)
{
    PlayStatus * now = play_status;
    PlayStatus * another = pause;
    if (play_status == pause)
    {
        another = play;
    }
    Base * next;
    next = play_status->update(another);
    PlayStatus * next_status = dynamic_cast<PlayStatus*>(next);
    if (next_status)
    {
        if (next_status != now)
        {
            play_status = next_status;
        }
        return this;
    }
    else
    {
        /// if next status is not gameplay, return the next status
        return next;
    }
}

GamePlay::~GamePlay()
{
    delete play;
    delete pause;
}