#ifndef GANASH_GEOM_RECTANGLE_H
#define GANASH_GEOM_RECTANGLE_H

#include "geom/point.h"

namespace Ganash {// DEC_BEGIN_GANASH END_GANASH
namespace Geom {

class Rectangle
{
public:
    Rectangle(double x=0.0, double y=0.0, double width=0.0, double height=0.0);
    //Rectangle(Ganash::Geom::Point topLeft, Ganash::Geom::Point bottomRight);
    /*
struct Rectangle_t
{
    double _x;
    double _y;
    double _width;
    double _height;
}

    Rectangle ( const Point & topLeft, const Point & bottomRight )
    Rectangle ( const Point & topLeft, const Size & size )
    Rectangle ( int x, int y, int width, int height )

Geom::Point 	bottomLeft () const
Geom::Point 	bottomRight () const
    */
    inline double x() const { return _x;}
    inline double y() const { return _y;}
    inline double width()  const { return _width;}
    inline double height() const { return _height;}

    void setX(double x);
    void setY(double y);
    void setWidth(double width);
    void setHeight(double height);

    inline double top()    const { return _top;}
    inline double right()  const { return _right;}
    inline double bottom() const { return _bottom;}
    inline double left()   const { return _left;}
    // topLeft, topRight, bottomLeft, bottomRight

    void setTop(double top);
    void setRight(double right);
    void setBottom(double bottom);
    void setLeft(double left);

protected:
    double _x;
    double _y;
    double _width;
    double _height;
    double _top;
    double _right;
    double _bottom;
    double _left;
};

} // namespace Geom
} // namespace Ganash

std::ostream& operator <<(std::ostream& stream, const Ganash::Geom::Rectangle& rectangle);

#endif // GANASH_GEOM_RECTANGLE_H
