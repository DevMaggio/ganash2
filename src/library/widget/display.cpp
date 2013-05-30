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

#include "display.h"

Ganash::Widget::Display::Display() :
    _graphics(0),
    _controls(0)
{
}

Ganash::Widget::Display::~Display()
{
}

void Ganash::Widget::Display::setData(const Ganash::Graphics::DataInterface &data)
{
    _data = data;
    // setupGraphics()
    _graphics->setData(getDataGraphics());
    // setupControls()
    _controls->setData(getDataControls());// redo

}

Ganash::Display::Object *Ganash::Widget::Display::graphics()
{
    return _graphics;
}

Ganash::Display::Container *Ganash::Widget::Display::controls()
{
    return _controls;
}

const Ganash::Graphics::DataInterface &Ganash::Widget::Display::getDataControls()
{
    return _data;
}

const Ganash::Graphics::DataInterface &Ganash::Widget::Display::getDataGraphics()
{
    return _data;
}
