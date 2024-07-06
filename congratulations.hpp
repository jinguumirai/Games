#ifndef CONGRATULATIONS_H_
#define CONGRATULATIONS_H_
#include"gamestatus.hpp"

class Congratulations:public GameStatus
{
    private:
    GameLib2D::ImageMat image_mat;
    public:
    virtual Base* update(Base*) override;
    Congratulations(const char * image_path, GameLib2D::Framework2D* const fra);
    virtual ~Congratulations();
};
#endif