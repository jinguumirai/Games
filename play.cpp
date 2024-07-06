#include "play.hpp"
#include "congratulations.hpp"
#include "defeated.hpp"

Play::MoveObjects::MoveObjects(float x, float y, const std::array<unsigned char, 4>& color, int h, int w, float speed):
x(x), y(y), image_mat(h, w, color), h(h), w(w), speed(speed){}

Play::MoveObjects::MoveObjects(float x, float y, const char * object_image_path, float speed):
x(x), y(y), image_mat(object_image_path), speed(speed){
    h = image_mat.height();
    w = image_mat.width();
}

Play::MoveObjects::MoveObjects(const Play::MoveObjects& move_object): x(move_object.x), y(move_object.y),
speed(move_object.speed), w(move_object.w), h(move_object.h), image_mat(move_object.image_mat)
{
    ;
}
float Play::MoveObjects::up_edge() const
{
    return y + float(h) / 2;
}

float Play::MoveObjects::down_edge() const
{
    return y - float(h) / 2;
}

float Play::MoveObjects::left_edge() const
{
    return x - float(w) / 2;
}

float Play::MoveObjects::right_edge() const
{
    return x + float(w) / 2;
}

Play::Play(const char * alien_path, const char * boats_path, GameLib2D::Framework2D * const fra):
boats(fra->width() / 2, 100, boats_path, 150), PlayStatus(fra), is_clear(false), is_defeated(false)
{
    float i , j;
    for (i = 100; i < 800; i+=100)
    {
        for (j = 400; j < 700; j+=100)
        {
            aliens.push_back(MoveObjects(i, j, alien_path, 150));
        }
    }
}

Base * Play::update(Base * const pause)
{
    GameLib2D::InputKey input_key = frame_instance->read_input();
    GameLib2D::InputKey pressed_key = frame_instance->read_once_input();
    frame_instance->clear({230, 230, 230});
    crash_process();
    if (is_clear)
    {
        Base* congratulations = new Congratulations("pictures/congratulations.png", frame_instance);
        return congratulations;
    }
    else if (is_defeated)
    {
        Base* defeated = new Defeated("pictures/defeated.png", frame_instance);
        return defeated;
    }

    double delta_time = frame_instance->average_delta_time() / 1000;

    if (pressed_key == GameLib2D::P)
    {
        return pause;
    }

    if (pressed_key == GameLib2D::SPACE)
    {
        bullets.push_back(MoveObjects(boats.x, boats.up_edge() + 20, {60, 60, 60, 255}, 15, 3, 150));
    }

    /// move ship
    if (input_key == GameLib2D::UP)
    {
        boats.y += delta_time * boats.speed; 
    }
    if (input_key == GameLib2D::DOWN)
    {
        boats.y -= delta_time * boats.speed;
    }
    if (input_key == GameLib2D::LEFT)
    {
        boats.x -= delta_time * boats.speed;
    }
    if (input_key == GameLib2D::RIGHT)
    {
        boats.x += delta_time * boats.speed;
    }

    /// prevent ship from going out of screen
    if (boats.right_edge() >= 1200)
    {
        boats.x = 1198 - float(boats.w) / 2;
    }
    if (boats.up_edge() >= 800)
    {
        boats.y = 798 - float(boats.h) / 2 ;
    }
    if (boats.left_edge() < 0)
    {
        boats.x = float(boats.w) / 2;
    }
    if (boats.down_edge() < 0)
    {
        boats.y = float(boats.h) / 2;
    }

    /// move aliens. If aliens arrive at the border of screen, change the direction of horizontal
    /// speed of the aliens. 
    
    bool alien_change_direct = false;
    
    for (auto& alien:aliens)
    {
        float alien_dis = alien.speed * delta_time;
        alien.x += alien_dis;
        if (alien.left_edge() <= 0)
        {
            alien.x = 1 + (float)alien.w / 2;
            alien_change_direct = true;
        }
        else if (alien.right_edge() >= 1200)
        {
            alien.x = 1198 - (float)alien.w / 2;
            alien_change_direct = true;
        }
        alien.y -= 10 * delta_time;

        /// if alien arrive at the bottom of the screen, game over
        if (alien.down_edge() <= 0)
        {
            is_defeated = true;
        }
    }

    /// move bullets. If the bullet cross the border of the screen, it would vanish
    auto but = bullets.begin();
    while(but != bullets.end())
    {
        (*but).y += delta_time * (*but).speed;
        if ((*but).y >= 800)
        {
            but = bullets.erase(but);
        }
        else
        {
            but++;
        }
    }
    if (alien_change_direct)
    {
        for (auto& alien:aliens)
        {
            alien.speed = -alien.speed;
        }
    }
    
    this->draw();
    return this;
}

bool Play::is_crash(const MoveObjects& obj1, const MoveObjects& obj2)
{
    /// crash detection
    if (obj1.left_edge() < obj2.right_edge() && obj2.left_edge() < obj1.right_edge() && 
    obj1.down_edge() < obj2.up_edge() && obj2.down_edge() < obj1.up_edge())
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Play::crash_process()
{
    if (aliens.size() == 0)
    {
        is_clear = true;
        return;
    }
    auto alien_iter = aliens.begin();
    auto bullet_iter = bullets.begin();
    while (aliens.size() != 0 && alien_iter != aliens.end())
    {
        /// if aliens crash the boat, game over
        if (is_crash(*alien_iter, boats))
        {
            is_defeated = true;
            return;
        }
        bullet_iter = bullets.begin();
        while (alien_iter != aliens.end() && bullets.size() != 0 && bullet_iter != bullets.end())
        {
            /// if an alien crash a bullet, delete the bullet and alien, bullet_iter and 
            /// alien_iter point to the next bullet and alien
            if (is_crash(*alien_iter, *bullet_iter))
            {
                alien_iter = aliens.erase(alien_iter);
                if (alien_iter != aliens.end() && is_crash(*alien_iter, boats))
                {
                    is_defeated = true;
                    return;
                }
                bullet_iter = bullets.erase(bullet_iter);
                /// reset bullet_iter, then detect the crash between the alien that 
                /// the alien_iter point to and the bullets left
                bullet_iter = bullets.begin();
            }
            else
            {
                bullet_iter++;
            }
        }
        if (alien_iter != aliens.end())
        {
            alien_iter++;
        }
    }
}

void Play::draw()
{
    frame_instance->draw_image(boats.image_mat, boats.x, boats.y);
    for (auto&alien: aliens)
    {
        frame_instance->draw_image(alien.image_mat, alien.x, alien.y);
    }
    for (auto&bullet: bullets)
    {
        frame_instance->draw_image(bullet.image_mat, bullet.x, bullet.y);
    }
}

Play::~Play()
{
}
