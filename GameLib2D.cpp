#include"GameLib2D.hpp"
#include <array>

GameLib2D::Framework2D * GameLib2D::Framework2D::frame = NULL;

void GameLib2D::Framework2D::clear(std::array<unsigned char, 3> color)
{
    int i;
    int max_i = frame_height * frame_width * 3;
    for (i = 0; i < max_i; i+=3)
    {
        frame_data[i] = color[0];
        frame_data[i + 1] = color[1];
        frame_data[i + 2] = color[2];
    }
}

GameLib2D::ImageMat::ImageMat(const char* image_path)
{
    cv::Mat image = cv::imread(image_path);
    if (image.empty() || image.channels() == 1)
    {
        std::cout << "Please input ture color image path!" << std::endl;
        exit(-1);
    }
    image_data = new UINT[image.cols * image.rows];
    int i, j;
    image_height = image.rows;
    image_width = image.cols;
    bool has_alpha = true;
    unsigned char b, g, r, alpha;

    /// If image has no alpha channel, we set alpha value of pixels as 255.
    if (image.channels() == 3)
    {
        has_alpha = false;  
    }
    
    for (i = 0; i < image_height; i++)
    {
        for (j = 0; j < image_width; j++)
        {
            if (has_alpha)
            {
                b = image.at<cv::Vec4b>(i, j)[0];
                g = image.at<cv::Vec4b>(i, j)[1];
                r = image.at<cv::Vec4b>(i, j)[2];
                alpha = image.at<cv::Vec4b>(i, j)[3];
            }
            else
            {
                b = image.at<cv::Vec3b>(i, j)[0];
                g = image.at<cv::Vec3b>(i, j)[1];
                r = image.at<cv::Vec3b>(i, j)[2];
            }

            /// convert coordinates in cv::Mat coordinate system into coordinates in ImageMat
            /// coordinate system
            int x_index = j;
            int y_index = image_height - i - 1;

            int index = x_index + y_index * image_width;

            image_data[index] = r;
            image_data[index] <<= 8;
            image_data[index] += g;
            image_data[index] <<= 8;
            image_data[index] += b;
            image_data[index] <<= 8;

            if (has_alpha)
            {
                image_data[index] += alpha;
            }
            else
            {
                image_data[index] += 0xFF;
            }
        }
    }
}

GameLib2D::ImageMat::ImageMat(unsigned int h, unsigned int w, const std::array<unsigned char, 4>& color):
image_height(h), image_width(w) 
{
    image_data = new UINT[w * h];
    int i, j;
    for (i = 0; i < w * h; i++)
    {
        image_data[i] = color[0];
        image_data[i] << 8;
        image_data[i] += color[1];
        image_data[i] << 8;
        image_data[i] += color[2];
        image_data[i] << 8;
        image_data[i] += color[3];
        image_data[i] << 8;
    }
}

GameLib2D::ImageMat::ImageMat(const GameLib2D::ImageMat& image_mat)
{
    image_width = image_mat.image_width;
    image_height = image_mat.image_height;
    int length = image_mat.image_height * image_mat.image_width;
    image_data = new UINT[length];
    int i;
    for (i = 0; i < length; i++)
    {
        image_data[i] = image_mat.image_data[i];
    }
}

const GameLib2D::ImageMat& GameLib2D::ImageMat::operator=(const GameLib2D::ImageMat& image_mat)
{
    delete image_data;
    image_width = image_mat.image_width;
    image_height = image_mat.image_height;
    int length = image_mat.image_height * image_mat.image_width;
    image_data = new UINT[length];
    int i;
    for (i = 0; i < length; i++)
    {
        image_data[i] = image_mat.image_data[i];
    }
    return image_mat;
}

const unsigned int GameLib2D::ImageMat::width() const
{
    return image_width;
}

const unsigned int GameLib2D::ImageMat::height() const
{
    return image_height;
}

UINT * const GameLib2D::ImageMat::data() const
{
    return image_data;
}

GameLib2D::ImageMat::~ImageMat()
{
    delete image_data;
}

GameLib2D::Framework2D::Framework2D(const unsigned int w, const unsigned int h, GLFWwindow * windows):frame_width(w),
frame_height(h), finish(false), window(windows), count_num(0)
{
    frame_data = new unsigned char[w * h * 3];
    frame_input.resize(7);
    time_queue.resize(11);
}
GameLib2D::Framework2D::~Framework2D()
{
    delete []frame_data;
}

void GameLib2D::Framework2D::record_time()
{
    /// record current time and delete the earliest time in queue
    time_queue.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count());
    time_queue.erase(time_queue.begin());
    count_num++;
}

double GameLib2D::Framework2D::average_delta_time()
{
    if (count_num > 11)
    {
        double deltas = time_queue[10] - time_queue[0];
        return deltas / 10;
    }
    else
    {
        return 0;
    }
}

GameLib2D::Framework2D* GameLib2D::Framework2D::instance(const int w, const int h, GLFWwindow * const windows)
{
    if (!frame)
    {
        frame = new Framework2D(w, h, windows);
    }
    return frame;
}

unsigned char * GameLib2D::Framework2D::data()
{
    return frame_data;
}


const int GameLib2D::Framework2D::height()
{
    return frame_height;
}

const int GameLib2D::Framework2D::width()
{
    return frame_width;
}

bool GameLib2D::Framework2D::is_finish()
{
    return finish;
}

void GameLib2D::Framework2D::destory()
{
    finish = true;
}

void GameLib2D::Framework2D::draw_image(const ImageMat& image, int x, int y)
{
    int half_image_height = image.height() / 2;
    int half_image_width = image.width() / 2;
    int x_start = x - half_image_width;
    int y_start = y - half_image_height;
    int x_max = x_start + image.width();
    int y_max = y_start + image.height();
    int x_fin = x_max <= this->width() ? x_max : this->width();
    int y_fin = y_max <= this->height() ? y_max : this->height();
    int x_index;
    int y_index;

    /// if image out of screen, do not draw
    if (x_start >= this->width() || y_start >= this->height() || x_max < 0 || y_max < 0)
    {
        return;
    }

    /// draw the pixels if it on screen
    for (y_index = y_start >= 0 ? y_start : 0; y_index < y_fin; y_index++)
    {
        for (x_index = x_start >= 0 ? x_start : 0; x_index < x_fin; x_index++)
        {
            
            /// convert coordinates in screen coordinates system into coordinates in ImageMat
            /// coordinate system
            int mat_i = x_index - x_start;
            int mat_j = y_index - y_start;
            
            UINT value = image.data()[mat_i + mat_j * image.width()];
            unsigned char alpha = value % 0x100;
            value >>= 8;
            unsigned char b = value % 0x100;
            value >>= 8;
            unsigned char g = value % 0x100;
            value >>= 8;
            unsigned char r = value;
            int fra_index = (x_index + y_index * this->width()) * 3;
            double fact = double(alpha) / 255;
            double left_fact = 1 - fact;

            /// draw the pixel by using alpha value
            this->frame_data[fra_index] = fact * r + this->frame_data[fra_index] * left_fact;
            this->frame_data[fra_index + 1] = fact * g + this->frame_data[fra_index + 1] * left_fact;
            this->frame_data[fra_index + 2] = fact * b + this->frame_data[fra_index + 2] * left_fact;
        }
    }
}

GameLib2D::InputKey GameLib2D::Framework2D::read_input() const
{
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            return GameLib2D::UP;
        }
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            return GameLib2D::DOWN;
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            return GameLib2D::LEFT;
        }
        else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            return GameLib2D::RIGHT;
        }
        else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            return GameLib2D::ESCAPE;
        }
        else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        {
            return GameLib2D::P;
        }
        else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            return GameLib2D::SPACE;
        }
        else
        {
            return GameLib2D::NUL;
        }
}

GameLib2D::InputKey GameLib2D::Framework2D::read_once_input() const
{
        static bool is_released[7] = {true, true, true, true, true, true, true};
        /// if you pressing a key continously, is_released[key] would be false until you release
        /// the key.
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && is_released[UP])
        {
            is_released[UP] = false;
            return GameLib2D::UP;
        }
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && is_released[DOWN])
        {
            is_released[DOWN] = false;
            return GameLib2D::DOWN;
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && is_released[LEFT])
        {
            is_released[LEFT] = false;
            return GameLib2D::LEFT;
        }
        else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && is_released[DOWN])
        {
            is_released[RIGHT] = false;
            return GameLib2D::RIGHT;
        }
        else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && is_released[ESCAPE])
        {
            is_released[ESCAPE] = false;
            return GameLib2D::ESCAPE;
        }
        else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && is_released[P])
        {
            is_released[P] = false;
            return GameLib2D::P;
        }
        else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && is_released[SPACE])
        {
            is_released[SPACE] = false;
            return GameLib2D::SPACE;
        }
        else
        {
            /// If key is realeased, set is_released[key] as true
            if (!is_released[UP] && glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE)
            {
                is_released[UP] = true;
            }
            if (!is_released[DOWN] && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE)
            {
                is_released[DOWN] = true;
            }
            if (!is_released[LEFT] && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)
            {
                is_released[LEFT] = true;
            }
            if (!is_released[RIGHT] && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE)
            {
                is_released[RIGHT] = true;
            }
            if (!is_released[ESCAPE] && glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
            {
                is_released[ESCAPE] = true;
            }
            if (!is_released[P] && glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
            {
                is_released[P] = true;
            }
            if (!is_released[SPACE] && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
            {
                is_released[SPACE] = true;
            }
            return GameLib2D::NUL;
        }
}