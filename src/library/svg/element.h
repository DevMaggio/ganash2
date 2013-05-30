#ifndef GANASH_SVG_ELEMENT_H
#define GANASH_SVG_ELEMENT_H

#include "svg/length.h"

namespace Ganash {
namespace Svg {

class Element
{
public:
    Element();

    void setX(Ganash::Svg::Length x);
    void setY(Ganash::Svg::Length y);
    void setWidth(Ganash::Svg::Length width);
    void setHeight(Ganash::Svg::Length height);
    //void setRx(Ganash::Svg::Length rx);
    //void setRy(Ganash::Svg::Length ry);
protected:
    Ganash::Svg::Length _x;
    Ganash::Svg::Length _y;
    Ganash::Svg::Length _width;
    Ganash::Svg::Length _height;
};

} // namespace Svg
} // namespace Ganash

#endif // GANASH_SVG_ELEMENT_H
