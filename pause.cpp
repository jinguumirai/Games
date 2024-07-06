#include"pause.hpp"
#include"title.hpp"

Pause::Pause(const char* path, GameLib2D::Framework2D * const fra):PlayStatus(fra), image(path)
{
    fra->draw_image(image, image.width() / 2, image.height() / 2);
}

Pause::~Pause()
{
}

Base * Pause::update(Base * const game)
{
    GameLib2D::InputKey input_key = frame_instance->read_once_input();
    frame_instance->clear({0, 0, 0});
    frame_instance->draw_image(image, image.width() / 2, image.height() / 2);
    if (input_key == GameLib2D::ESCAPE)
    {
        Title * title = new Title("pictures/title.png", frame_instance);
        return title;
    }
    else if (input_key == GameLib2D::SPACE)
    {
        return game;
    }
    else
    {
        return this;
    }
}