#ifndef PAUSE_H_
#define PAUSE_H_
#include"playstatus.hpp"

class Play;
class Pause: public PlayStatus
{
    private:
    GameLib2D::ImageMat image;
    public:
    virtual Base * update(Base * const) override;
    Pause(const char* pause_path, GameLib2D::Framework2D * fra);
    virtual ~Pause();
};

#endif