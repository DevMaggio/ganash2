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
#include "display/shape.h"

Ganash::Widget::Shape::Shape() :
    Ganash::Widget::Display()
{
    _graphics = new Ganash::Display::Shape();
    _controls = new Ganash::Display::Container();
    // do the controls
    Ganash::Graphics::DataPath data;
    data.moveTo(0.5,  0.5);
    data.lineTo(6.5, 0.5);
    data.lineTo(6.5, 6.5);
    data.lineTo(0.5, 6.5);
    data.lineTo(0.5, 0.5);
    //Ganash::Graphics::Path *knot = new Ganash::Graphics::Path();
    //knot->setData(data);
    Ganash::Display::Shape *k = new Ganash::Display::Shape();
    k->setData(data);
    // .signal_x().connect();

    _controls->add(k);
}

Ganash::Widget::Shape::~Shape()
{
}
