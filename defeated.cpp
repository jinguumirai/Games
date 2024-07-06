#include"defeated.hpp"
#include"title.hpp"

Defeated::Defeated(const char * image_path, GameLib2D::Framework2D* const fra):GameStatus(fra), image_mat(image_path)
{

}

Base* Defeated::update(Base* base)
{
    frame_instance->clear({0, 0, 0});
    frame_instance->draw_image(image_mat, image_mat.width() / 2, image_mat.height() / 2);
    GameLib2D::InputKey input_key = frame_instance->read_once_input();
    if (input_key == GameLib2D::SPACE)
    {
        return new Title("pictures/title.png", frame_instance);
    }
    return this;
}

Defeated::~Defeated()
{
}
