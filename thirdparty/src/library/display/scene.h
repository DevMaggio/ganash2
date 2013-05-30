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

#ifndef GANASH_WIDGET_SCENE_H
#define GANASH_WIDGET_SCENE_H

#include "display/object.h"
#include "graphics/renderer.h"

namespace Ganash {
namespace Display {

class Scene
{
public:
    Scene();
    void add(Ganash::Display::Object *child);
    //void add(Ganash::Widget::Graphics *child);
    //void add(Ganash::Widget::Object *child);

    //void remove(Ganash::Widget::Object *child);
    void render(Ganash::Graphics::Renderer *renderer);

    void dispatch(int x, int y);
protected:
    std::list<Ganash::Display::Object*> _children;

};

} // namespace Widget
} // namespace Ganash

#endif // GANASH_WIDGET_SCENE_H
