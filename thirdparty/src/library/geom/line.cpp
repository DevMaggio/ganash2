#include "line.h"
#include <iostream>

Ganash::Geom::Line::Line(double x0, double y0, double x1, double y1)
{
    if(x0<=x1)
    {
        _ax = x0;
        _ay = y0;
        _bx = x1;
        _by = y1;
    }
    else
    {
        _ax = x1;
        _ay = y1;
        _bx = x0;
        _by = y0;
    }

    double x = _ax;
    double y = std::min(_ay, _by);
    double w = _bx - x;
    double h = std::max(_ay, _by) - y;

    rect.setX(x);
    rect.setY(y);
    rect.setWidth(w);
    rect.setHeight(h);
}

Ganash::Geom::Line::~Line()
{
}

Ganash::Geom::Rectangle Ganash::Geom::Line::getBoundingBox()
{
    return rect;
}

std::vector<double> Ganash::Geom::Line::intersect(double k)
{
    std::vector<double> r;
    double s;
    if(rect.width() != 0.0)
    {
        s = (k - _ay) * (_bx-_ax) / (_by-_ay) + _ax;
        if( rect.left() <= s && s <= rect.right() )
        {
            r.push_back(s);
        }
    }
    else
    {
        if( rect.bottom() <= k && k <= rect.top())
        {
            r.push_back(_ax);
        }
    }

    return r;
}

/*
std::ostream& operator <<(std::ostream& stream, const Ganash::Geom::Line &line)
{
    stream << "Line{" << line._ax << ", " << line._ay << ", " << line._bx << ", " << line._by << "}";
    return stream;
}
*/
