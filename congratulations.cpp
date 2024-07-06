#include"congratulations.hpp"
#include"title.hpp"

Congratulations::Congratulations(const char* image_path, GameLib2D::Framework2D* fra):image_mat(image_path), GameStatus(fra)
{
}

Congratulations::~Congratulations()
{
}

Base* Congratulations::update(Base* another)
{
    GameLib2D::InputKey input_key = frame_instance->read_once_input();
    frame_instance->clear({0, 0, 0});
    frame_instance->draw_image(image_mat, image_mat.width() / 2, image_mat.height() / 2);
    if (input_key == GameLib2D::SPACE)
    {
        GameStatus* title = new Title("pictures/title.png", frame_instance);
        return title;
    }
    return this;
}