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

#ifndef GANASH_DISPLAY_SHAPE_H
#define GANASH_DISPLAY_SHAPE_H

#include "display/object.h"

#include "gdkmm/event.h"

namespace Ganash {
namespace Display {

class Shape : public Object
{
public:
    Shape();
    ~Shape();

    void setMask(Ganash::Display::Object *mask);
    Ganash::Display::Object *getMask();
    void setHit(Ganash::Display::Object *hit);
    Ganash::Display::Object *getHit();

    virtual bool on_motion(GdkEventMotion *event);
    //virtual bool on_mouse_enter(GdkEventMotion *event);
    //virtual bool on_mouse_leave(GdkEventMotion *event);
    //virtual bool on_mouse_move(GdkEventMotion *event);
protected:
    Ganash::Display::Object *_mask;
    Ganash::Display::Object *_hit;

};

} // namespace Display
} // namespace Ganash

#endif // GANASH_DISPLAY_SHAPE_H
