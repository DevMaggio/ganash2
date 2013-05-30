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

#include "object.h"
#include "geom/point.h"
#include "geom/line.h"
#include "geom/segment.h"
#include "geom/bezier.h"
#include "geom/rectangle.h"
#include "math/polynomial.h"

#include <iostream>

Ganash::Display::Object::Object() :
    graphics(),
    _name(""),
    _alpha(1.0),
    _x(0.0),
    _y(0.0),
    _width(0.0),
    _height(0.0)
{
}

Ganash::Display::Object::~Object()
{
}

void Ganash::Display::Object::dispatch(int x, int y)
{
    Ganash::Graphics::DataInterface p = graphics.data();
    Ganash::Graphics::DataPath path = static_cast<Ganash::Graphics::DataPath>(p);

    bool is_even = false;
    double org_x;
    double org_y;

    int command;
    int iData = 0;
    for(int i = 0; i<path._commands.size(); i+=1)
    {
        command = path._commands.at(i);
        switch(command)
        {
        case Ganash::Graphics::DataPath::MoveTo :
            org_x = path._datas[iData];
            org_y = path._datas[iData+1];
            iData += 2;
            break;
        case Ganash::Graphics::DataPath::LineTo :
            {
                Ganash::Geom::Line line(org_x, org_y, path._datas[iData], path._datas[iData+1]);
                Ganash::Geom::Rectangle box = line.getBoundingBox();
                if(box.bottom()<y && y<box.top())
                {
                    std::vector<double> s = line.intersect(y);
                    if(s.size()>0 && s[0]<=x)
                    {
                        is_even = !is_even;
                    }
                }
            }
            org_x = path._datas[iData];
            org_y = path._datas[iData+1];
            iData += 2;
            break;
        case Ganash::Graphics::DataPath::QuadTo :
            {
                Ganash::Geom::Bezier::Quadratic bezier(org_x, org_y,
                                                        path._datas[iData], path._datas[iData+1],
                                                        path._datas[iData+2], path._datas[iData+3]);
                Ganash::Geom::Rectangle box = bezier.getBoundingBox();
                if(box.bottom()<y && y<box.top())
                {
                    std::vector<double> s = bezier.intersect(y);
                    if(s.size()>0 && s[0]<=x)
                    {
                        is_even = !is_even;
                    }
                }
            }
            org_x = path._datas[iData+2];
            org_y = path._datas[iData+3];
            iData += 4;
            break;
        case Ganash::Graphics::DataPath::CubicTo :
            {
                Ganash::Geom::Bezier::Cubic bezier(org_x, org_y,
                                                    path._datas[iData], path._datas[iData+1],
                                                    path._datas[iData+2], path._datas[iData+3],
                                                    path._datas[iData+4], path._datas[iData+5]);
                Ganash::Geom::Rectangle box = bezier.getBoundingBox();
                if(box.bottom()<y && y<box.top())
                {
                    std::vector<double> s = bezier.intersect(y);
                    if(s.size()>0 && s[0]<=x)
                    {
                        is_even = !is_even;
                    }
                    if(s.size()>1 && s[1]<=x)
                    {
                        is_even = !is_even;
                    }
                    if(s.size()>2 && s[2]<=x)
                    {
                        is_even = !is_even;
                    }
                }
            }
            break;
        default :
            break;
        }
    }
    //std::cout << is_even << std::endl;
    if(is_even)
    {
        // if ! over
        // emit onMouseOver
    }
}

void Ganash::Display::Object::setName(const std::string &name)
{
    _name = name;
}

const std::string &Ganash::Display::Object::getName()
{
    return _name;
}

void Ganash::Display::Object::setAlpha(double alpha)
{
    _alpha = alpha;
}

double Ganash::Display::Object::getAlpha()
{
    return _alpha;
}

void Ganash::Display::Object::setX(double x)
{
    _x = x;
}

double Ganash::Display::Object::getX()
{
    return _x;
}

void Ganash::Display::Object::setY(double y)
{
    _y = y;
}

double Ganash::Display::Object::getY()
{
    return _y;
}

void Ganash::Display::Object::setWidth(double width)
{
    _width = width;
}

double Ganash::Display::Object::getWidth()
{
    return _width;
}


void Ganash::Display::Object::setHeight(double height)
{
    _height = height;
}

double Ganash::Display::Object::getHeight()
{
    return _height;
}
