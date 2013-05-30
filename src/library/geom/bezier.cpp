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

#include "bezier.h"

#include <algorithm>
#include <iostream>

Ganash::Geom::Bezier::Quadratic::Quadratic(double p0_x, double p0_y,
                                           double p1_x, double p1_y,
                                           double p2_x, double p2_y) :
    _p0_x(p0_x), _p0_y(p0_y),
    _p1_x(p1_x), _p1_y(p1_y),
    _p2_x(p2_x), _p2_y(p2_y)
{
}

Ganash::Geom::Rectangle Ganash::Geom::Bezier::Quadratic::getBoundingBox()
{
    double left, right, top, bottom;
    left   = std::min(_p0_x, _p2_x);
    right  = std::max(_p0_x, _p2_x);
    top    = std::max(_p0_y, _p2_y);
    bottom = std::min(_p0_y, _p2_y);

    // To polynomial
    Ganash::Math::Polynomial polynome_x(_p0_x,
                                        2 * (_p1_x - _p0_x),
                                        _p0_x - 2 * _p1_x + _p2_x);

    // To polynomial
    Ganash::Math::Polynomial polynome_y(_p0_y,
                                        2 * (_p1_y - _p0_y),
                                        _p0_y - 2 * _p1_y + _p2_y);

    Ganash::Math::Polynomial *derived_x = polynome_x.d();
    Ganash::Math::Polynomial *derived_y = polynome_y.d();

    std::vector<double> roots_x = derived_x->roots();
    if(roots_x.size()>0)// au moins 1 solution
    {
        if(0.0<=roots_x[0] && roots_x[0]<=1.0)
        {
            Ganash::Geom::Point p = f(roots_x[0]);
            left   = std::min(left,  p.x());
            right  = std::max(right, p.x());
        }
    }
    std::vector<double> roots_y = derived_y->roots();
    if(roots_y.size()>0)// au moins 1 solution
    {
        if(0.0<=roots_y[0] && roots_y[0]<=1.0)
        {
            Ganash::Geom::Point p = f(roots_y[0]);
            top    = std::max(top,    p.y());
            bottom = std::min(bottom, p.y());
        }
    }

    return Ganash::Geom::Rectangle(left, bottom, right-left, top-bottom);
}

Ganash::Geom::Point Ganash::Geom::Bezier::Quadratic::f(double t)
{
    double t2  = t * t;
    double _t  = 1 - t;
    double _t2 = _t * _t;
    double t_t = 2 * t * _t;
    double x = _p0_x * _t2 + _p1_x * t_t + _p2_x * t2;
    double y = _p0_y * _t2 + _p1_y * t_t + _p2_y * t2;

    return Ganash::Geom::Point(x, y);
}

std::vector<double> Ganash::Geom::Bezier::Quadratic::intersect(double y)
{
    std::vector<double> r;
    // To polynomial
    Ganash::Math::Polynomial polynome_y(_p0_y - y,
                                        2 * (_p1_y - _p0_y),
                                        _p0_y - 2 * _p1_y + _p2_y);

    std::vector<double> s = polynome_y.roots();
    if(s.size()>0 && 0.0<= s[0] && s[0] <= 1.0)
    {
        Ganash::Geom::Point pt1 = f(s[0]);
        r.push_back(pt1.x());
    }
    if(s.size()>1 && 0.0<= s[1] && s[1] <= 1.0)
    {
        Ganash::Geom::Point pt1 = f(s[1]);
        r.push_back(pt1.x());
    }

    return r;
}

Ganash::Geom::Bezier::Cubic::Cubic(double p0_x, double p0_y,
                                   double p1_x, double p1_y,
                                   double p2_x, double p2_y,
                                   double p3_x, double p3_y) :
    _p0_x(p0_x), _p0_y(p0_y),
    _p1_x(p1_x), _p1_y(p1_y),
    _p2_x(p2_x), _p2_y(p2_y),
    _p3_x(p3_x), _p3_y(p3_y)
{
}

Ganash::Geom::Rectangle Ganash::Geom::Bezier::Cubic::getBoundingBox()
{
    double left, right, top, bottom;
    left   = std::min(_p0_x, _p3_x);
    right  = std::max(_p0_x, _p3_x);
    top    = std::max(_p0_y, _p3_y);
    bottom = std::min(_p0_y, _p3_y);

    // To polynomial
    Ganash::Math::Polynomial polynome_x(_p0_x,
                                        3 * (_p1_x - _p0_x),
                                        3 * (_p0_x - 2 * _p1_x + _p2_x),
                                        - _p0_x + 3 * _p1_x - 3 * _p2_x + _p3_x);

    // To polynomial
    Ganash::Math::Polynomial polynome_y(_p0_y,
                                        3 * (_p1_y - _p0_y),
                                        3 * (_p0_y - 2 * _p1_y + _p2_y),
                                        - _p0_y + 3 * _p1_y - 3 * _p2_y + _p3_y);

    Ganash::Math::Polynomial *derived_x = polynome_x.d();
    Ganash::Math::Polynomial *derived_y = polynome_y.d();

    std::vector<double> roots_x = derived_x->roots();
    if(roots_x.size()>0)// au moins 1 solution
    {
        if(0.0<=roots_x[0] && roots_x[0]<=1.0)
        {
            Ganash::Geom::Point p = f(roots_x[0]);
            left   = std::min(left,  p.x());
            right  = std::max(right, p.x());
        }
    }
    if(roots_x.size()>1)// 2 solutions
    {
        if(0.0<=roots_x[1] && roots_x[1]<=1.0)
        {
            Ganash::Geom::Point p = f(roots_x[1]);
            left   = std::min(left,  p.x());
            right  = std::max(right, p.x());
        }
    }
    std::vector<double> roots_y = derived_y->roots();
    if(roots_y.size()>0)// au moins 1 solution
    {
        if(0.0<=roots_y[0] && roots_y[0]<=1.0)
        {
            Ganash::Geom::Point p = f(roots_y[0]);
            top    = std::max(top,    p.y());
            bottom = std::min(bottom, p.y());
        }
    }
    if(roots_y.size()>1)// 2 solutions
    {
        if(0.0<=roots_y[1] && roots_y[1]<=1.0)
        {
            Ganash::Geom::Point p = f(roots_y[1]);
            top    = std::max(top,    p.y());
            bottom = std::min(bottom, p.y());
        }
    }

    return Ganash::Geom::Rectangle(left, bottom, right-left, top-bottom);

}

Ganash::Geom::Point Ganash::Geom::Bezier::Cubic::f(double t)
{
    double _t = 1 - t;
    double _t2 = _t * _t;
    double _t3 = _t2 * _t;
    double t2 = t * t;
    double t3 = t * t2;
    double t_t2 = 3 * t * _t2;
    double t2_t = 3 * t2 * _t;
    double x = _p0_x * _t3 + _p1_x * t_t2 + _p2_x * t2_t + _p3_x * t3;// 16 OP
    double y = _p0_y * _t3 + _p1_y * t_t2 + _p2_y * t2_t + _p3_y * t3;

    return Ganash::Geom::Point(x, y);
}

std::vector<double> Ganash::Geom::Bezier::Cubic::intersect(double y)
{
    std::vector<double> r;
    // To polynomial
    Ganash::Math::Polynomial polynome_y(_p0_y - y,
                                        3 * (_p1_y - _p0_y),
                                        3 * (_p0_y - 2 * _p1_y + _p2_y),
                                        - _p0_y + 3 * _p1_y - 3 * _p2_y + _p3_y);//11

    std::vector<double> s = polynome_y.roots();
    std::vector<double> tmp;
    if(s.size()>0 && 0.0<= s[0] && s[0] <= 1.0)
    {
        tmp.push_back(s[0]);
    }
    if(s.size()>1 && 0.0<= s[1] && s[1] <= 1.0)
    {
        tmp.push_back(s[1]);
    }
    if(s.size()>2 && 0.0<= s[2] && s[2] <= 1.0)
    {
        tmp.push_back(s[2]);
    }


    if(tmp.size()>0)
    {
        Ganash::Geom::Point pt1 = f(tmp[0]);
        r.push_back(pt1.x());
    }
    if(tmp.size()>1 && tmp[0] != tmp[1])
    {
        Ganash::Geom::Point pt1 = f(tmp[1]);
        r.push_back(pt1.x());
    }
    if(tmp.size()>2 && tmp[0] != tmp[2] && tmp[1] != tmp[2])
    {
        Ganash::Geom::Point pt1 = f(tmp[2]);
        r.push_back(pt1.x());
    }

    return r;
}
