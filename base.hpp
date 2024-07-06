#ifndef BASE_H_
#define BASE_H_
#include "GameLib2D.hpp"

/// @brief Base class, all status classes would inherit Base
class Base
{
    public:
    virtual Base * update(Base * const) = 0;
};
#endif