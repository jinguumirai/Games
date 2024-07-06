#ifndef PLAY_H_
#define PLAY_H_
#include"playstatus.hpp"
#include <vector>

class Play: public PlayStatus
{
    private:

    class MoveObjects
    {
        public:
        /// @param x the abscissa of the center of the object
        /// @param y the vertical ordinate of the center of the object
        /// @param object_image_path the path of image
        /// @param speed the speed of object. The unit of speed is /s
        MoveObjects(float x, float y, const char * object_image_path, float speed);

        /// @brief create a instance by using preset parameters not image
        /// @param color the color of object
        MoveObjects(float x, float y, const std::array<unsigned char, 4>& color, const int h, const int w, float speed);
        float x, y;
        int h, w;
        float speed;
        float left_edge() const;
        float right_edge() const;
        float up_edge() const;
        float down_edge() const;
        GameLib2D::ImageMat image_mat;
        MoveObjects(const MoveObjects&);
    };
    MoveObjects boats;
    std::vector<MoveObjects> aliens;
    std::vector<MoveObjects> bullets;
    bool is_clear;
    bool is_defeated;

    /// @brief detect crash
    bool is_crash(const MoveObjects&, const MoveObjects&);
    public:
    virtual Base * update(Base * const) override;
    Play(const char * alien_path, const char * boats_path, GameLib2D::Framework2D * const fra);

    /// @brief for every aliens, bullets and ship, detect crash
    void crash_process();

    /// @brief draw ship, aliens and bullets
    void draw();
    virtual ~Play();
};
#endif