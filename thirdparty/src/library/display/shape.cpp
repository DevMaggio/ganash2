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

#include "shape.h"
#include <iostream>

Ganash::Display::Shape::Shape() :
    Ganash::Display::Object(),
  _mask(0),
  _hit(0)
{
}

Ganash::Display::Shape::~Shape()
{
}

void Ganash::Display::Shape::setMask(Ganash::Display::Object *mask)
{
    _mask = mask;
}

Ganash::Display::Object *Ganash::Display::Shape::getMask()
{
    return _mask;
}

void Ganash::Display::Shape::setHit(Ganash::Display::Object *hit)
{
    _hit = hit;
}

Ganash::Display::Object *Ganash::Display::Shape::getHit()
{
    return _hit;
}

bool Ganash::Display::Shape::on_motion(GdkEventMotion *event)
{
    //
}
// 	Shape -> DisplayObject -> EventDispatcher -> Object
// boundingRect
