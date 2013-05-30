#ifndef GANASH_GEOM_LINE_H
#define GANASH_GEOM_LINE_H

#include "geom/point.h"
#include "geom/rectangle.h"
#include <vector>

namespace Ganash {
namespace Geom {

class Line
{
public:
    Line(double x0, double y0, double x1, double y1);
    ~Line();
    Ganash::Geom::Rectangle getBoundingBox();
    std::vector<double> intersect(double k);
protected:
    double _ax;
    double _ay;
    double _bx;
    double _by;
    //Ganash::Geom::Point a;
    //Ganash::Geom::Point b;
    Ganash::Geom::Rectangle rect;
};

} // namespace Geom
} // namespace Ganash

//std::ostream& operator <<(std::ostream& stream, const Ganash::Geom::Line& line);

#endif // GANASH_GEOM_LINE_H
