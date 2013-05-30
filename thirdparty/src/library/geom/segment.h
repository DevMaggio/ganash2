#ifndef GANASH_GEOM_BEZIERSEGMENT_H
#define GANASH_GEOM_BEZIERSEGMENT_H

#include "geom/rectangle.h"

namespace Ganash {
namespace Geom {

class Segment
{
public:
    Segment(double x1, double y1, double x2, double y2);
    Ganash::Geom::Rectangle getBoundingBox();
protected:
    double _x;
    double _y;
    double _w;
    double _h;
};

} // namespace Geom
} // namespace Ganash

#endif // GANASH_GEOM_BEZIERSEGMENT_H
