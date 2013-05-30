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

#ifndef GANASH_DISPLAY_CONTAINER_H
#define GANASH_DISPLAY_CONTAINER_H

#include "object.h"
#include "graphics/renderer.h"

#include <list>

namespace Ganash {
namespace Display {

class Container : public Object
{
public:
    Container();
    virtual ~Container();
    virtual void render(Ganash::Graphics::Renderer *renderer);
    void add(Object* child);
    void remove(Object* child);
protected:
    std::list<Object*> _children;
};

} // namespace Display
} // namespace Ganash

#endif // GANASH_DISPLAY_CONTAINER_H
