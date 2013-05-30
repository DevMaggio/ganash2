#include "rectangle.h"

Ganash::Geom::Rectangle::Rectangle(double x, double y, double width, double height) :
    _x(x),
    _y(y),
    _width(width),
    _height(height)
{
    _top    = _y + _height;
    _right  = _x + _width;
    _bottom = _y;
    _left   = _x;
}

void Ganash::Geom::Rectangle::setTop(double top)
{
    _top = top;
}
void Ganash::Geom::Rectangle::setRight(double right)
{
    _right = right;
}
void Ganash::Geom::Rectangle::setBottom(double bottom)
{
    _bottom = bottom;
}
void Ganash::Geom::Rectangle::setLeft(double left)
{
    _left = left;
}

void Ganash::Geom::Rectangle::setX(double x)
{
    _x = x;
    _right  = _x + _width;
    _left   = _x;
}
void Ganash::Geom::Rectangle::setY(double y)
{
    _y = y;
    _top    = _y + _height;
    _bottom = _y;
}
void Ganash::Geom::Rectangle::setWidth(double width)
{
    _width = width;
    _right  = _x + _width;
}
void Ganash::Geom::Rectangle::setHeight(double height)
{
    _height = height;
    _top    = _y + _height;
}

std::ostream& operator <<(std::ostream& stream, const Ganash::Geom::Rectangle &r)
{
    stream << "Rectangle{" << r.x() << ", " << r.y() << ", " << r.width() << ", " << r.height() << "}";
    return stream;
}
