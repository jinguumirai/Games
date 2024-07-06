#ifndef PLAYSTATUS_H_
#define PLAYSTATUS_H_
#include "GameLib2D.hpp"
#include "base.hpp"

/// @brief all play status classes would inherit PlayStatus
class PlayStatus: public Base
{
    protected:
    GameLib2D::Framework2D * const frame_instance;
    public:
    PlayStatus(GameLib2D::Framework2D * frame);
    virtual Base * update(Base * const) override = 0;
    virtual ~PlayStatus();
};
#endif