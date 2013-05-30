#include "segment.h"

Ganash::Geom::Segment::Segment(double x1, double y1, double x2, double y2)
{
    _x = std::min(x1, x2);
    _y = std::min(y1, y2);
    _w = std::max(x1, x2) - _x;
    _h = std::max(y1, y2) - _y;
}

Ganash::Geom::Rectangle Ganash::Geom::Segment::getBoundingBox()
{
    return Ganash::Geom::Rectangle(_x, _y, _w, _h);
}
