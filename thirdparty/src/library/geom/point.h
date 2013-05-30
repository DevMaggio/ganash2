#ifndef GANASH_GEOM_POINT_H
#define GANASH_GEOM_POINT_H

#include <ostream>

namespace Ganash {
namespace Geom {

class Point
{
public:
    explicit Point(double x = 0.0, double y = 0.0);
    inline double x() const {return _x;}
    inline double y() const {return _y;}
    inline void setX(double x) {_x = x;}
    inline void setY(double y) {_y = y;}
    inline void getX(double *x) const {*x = _x;}
    inline void getY(double *y) const {*y = _y;}

    Point& operator+=(const Point & point);
    Point& operator-=(const Point & point);

protected:
    double _x;
    double _y;
};

} // namespace Geom
} // namespace Ganash

Ganash::Geom::Point& operator+(const Ganash::Geom::Point& point1, const Ganash::Geom::Point& point2);
Ganash::Geom::Point& operator-(const Ganash::Geom::Point& point1, const Ganash::Geom::Point& point2);

#endif // GANASH_GEOM_POINT_H
