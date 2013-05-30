#include "svg/element.h"

Ganash::Svg::Element::Element()
{
}

void Ganash::Svg::Element::setX(Ganash::Svg::Length x)
{
    _x = x;
}

void Ganash::Svg::Element::setY(Ganash::Svg::Length y)
{
    _y = y;
}

void Ganash::Svg::Element::setWidth(Ganash::Svg::Length width)
{
    _width = width;
}

void Ganash::Svg::Element::setHeight(Ganash::Svg::Length height)
{
    _height = height;
}
