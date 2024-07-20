#include"title.hpp"
#include"GameLib2D.hpp"
#include"gameplay.hpp"
#include<iostream>

Title::Title(const char * title_pic, GameLib2D::Framework2D * const fra_data):GameStatus(fra_data), title_image(title_pic)
{
}
Base * Title::update(Base * const)
{
    GameLib2D::InputKey input_key = frame_instance->read_once_input();
    frame_instance->clear({0, 0, 0});
    frame_instance->draw_image(title_image, title_image.width() / 2, title_image.height() / 2);
    if (input_key == GameLib2D::SPACE)
    {
        GamePlay * game_play = new GamePlay("pictures/alien.bmp", "pictures/ship.bmp", frame_instance);
        return game_play;
    }
    if (input_key == GameLib2D::ESCAPE)
    {
        frame_instance->destory();
    }
    return this;
}

Title::~Title()
{
}
