#ifndef TITLE_H_
#define TITLE_H_

#include"gamestatus.hpp"
#include"GameLib2D.hpp"

class Title:public GameStatus
{
    private:
    GameLib2D::ImageMat title_image;
    public:
    Title(const char * title_pic, GameLib2D::Framework2D * const fra_data);
    virtual Base* update(Base * const) override;
    virtual ~Title();
};
#endif