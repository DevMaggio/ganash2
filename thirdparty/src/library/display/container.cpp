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

#include "container.h"

Ganash::Display::Container::Container() :
    Ganash::Display::Object()
{
}

Ganash::Display::Container::~Container()
{
}

void Ganash::Display::Container::render(Ganash::Graphics::Renderer *renderer)
{
    Ganash::Display::Object* child;
    for (std::list<Ganash::Display::Object*>::iterator it = _children.begin(); it != _children.end(); it++)
    {
        child = *it;
        child->graphics.render(renderer);
    }
}

void Ganash::Display::Container::add(Ganash::Display::Object *child)
{
    _children.push_back(child);
}

void Ganash::Display::Container::remove(Ganash::Display::Object *child)
{
    _children.remove(child);
}
