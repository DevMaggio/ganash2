#include "point.h"

Ganash::Geom::Point::Point(double x, double y) :
    _x(x),
    _y(y)
{
}

Ganash::Geom::Point& Ganash::Geom::Point::operator+=(const Ganash::Geom::Point &point)
{
    _x = _x + point.x();
    _y = _y + point.y();
    return *this;
}

Ganash::Geom::Point& Ganash::Geom::Point::operator-=(const Ganash::Geom::Point &point)
{
    _x = _x - point.x();
    _y = _y - point.y();
    return *this;
}

Ganash::Geom::Point& operator +(const Ganash::Geom::Point& point1, const Ganash::Geom::Point& point2)
{
    Ganash::Geom::Point point(point1);
    point += point2;
    return point;
}

Ganash::Geom::Point& operator -(const Ganash::Geom::Point& point1, const Ganash::Geom::Point& point2)
{
    Ganash::Geom::Point point(point1);
    point -= point2;
    return point;
}
