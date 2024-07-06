#ifndef DEFEATED_H_
#define DEFEATED_H_
#include"gamestatus.hpp"

class Defeated: public GameStatus
{
    private:
    const GameLib2D::ImageMat image_mat;
    public:
    Defeated(const char * image_path, GameLib2D::Framework2D* const fra);
    virtual Base* update(Base*);
    virtual ~Defeated();
};

#endif