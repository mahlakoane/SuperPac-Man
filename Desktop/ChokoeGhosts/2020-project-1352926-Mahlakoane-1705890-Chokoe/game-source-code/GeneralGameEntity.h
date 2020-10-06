#ifndef GENERALGAMEENTITY_H
#define GENERALGAMEENTITY_H
#include <tuple>
///General functionality expected from all game objects
///are captured through this class.


using x_and_y = std::tuple<float, float>;
using length_and_breadth = std::tuple<float, float>;

struct BoundingBox{
    float xTopLeft;
    float yTopLeft;
    float BoxLength;
    float BoxHeight;
};

template <typename ArbitraryType>
class GeneralGameEntity
{
    public:
        GeneralGameEntity() {}
        virtual ArbitraryType ObjectContainer() const=0;
        ~GeneralGameEntity() {}

    private:
};

#endif // GENERALGAMEENTITY_H
