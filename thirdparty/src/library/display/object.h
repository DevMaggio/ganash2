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

#ifndef GANASH_DISPLAY_OBJECT_H
#define GANASH_DISPLAY_OBJECT_H

#include "graphics/renderer.h"
#include "display/graphics.h"

namespace Ganash {
namespace Display {

class Object
{
public:
    Object();
    virtual ~Object();
    void dispatch(int x, int y);

    void   setName(const std::string &name);
    const std::string &getName();
    Ganash::Display::Graphics graphics;
    void   setAlpha(double alpha);
    double getAlpha();
    void   setX(double x);
    double getX();
    void   setY(double y);
    double getY();
    void   setWidth(double width);
    double getWidth();
    void   setHeight(double height);
    double getHeight();

protected:
    std::string _name;
    double _alpha;
    double _x;
    double _y;
    double _width;
    double _height;
};

} // namespace Display
} // namespace Ganash

#endif // GANASH_DISPLAY_OBJECT_H
