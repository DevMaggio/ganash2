/**
 * This file is part of Ganash
 *
 * Copyright (C) 2012  Sergio DE VASCONCELOS
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef GANASH_GEOM_BEZIER_H
#define GANASH_GEOM_BEZIER_H

#include "geom/point.h"
#include "geom/rectangle.h"
#include "math/polynomial.h"

#include <vector>

namespace Ganash {
namespace Geom {

class Bezier
{
public:

    class Quadratic
    {
    public:
        Quadratic(double p0_x, double p0_y, double p1_x, double p1_y, double p2_x, double p2_y);
        Ganash::Geom::Point f(double t);
        Ganash::Geom::Rectangle getBoundingBox();
        std::vector<double> intersect(double y);
    protected:
        double _p0_x;
        double _p0_y;
        double _p1_x;
        double _p1_y;
        double _p2_x;
        double _p2_y;
    };

    class Cubic
    {
    public:
        Cubic(double p0_x, double p0_y,
              double p1_x, double p1_y,
              double p2_x, double p2_y,
              double p3_x, double p3_y);
        Ganash::Geom::Point f(double t);
        Ganash::Geom::Rectangle getBoundingBox();
        std::vector<double> intersect(double y);
    protected:
        double _p0_x;
        double _p0_y;
        double _p1_x;
        double _p1_y;
        double _p2_x;
        double _p2_y;
        double _p3_x;
        double _p3_y;
    };
};

} // namespace Geom
} // namespace Ganash

#endif // GANASH_GEOM_BEZIER_H
