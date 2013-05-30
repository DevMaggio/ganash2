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

#ifndef GANASH_WIDGET_OBJECT_H
#define GANASH_WIDGET_OBJECT_H

#include "graphics/data-interface.h"
#include "display/object.h"
#include "display/container.h"

namespace Ganash {
namespace Widget {

class Display
{
public:
    Display();
    virtual ~Display();

    void setData(const Ganash::Graphics::DataInterface &data);
    Ganash::Display::Object    *graphics();
    Ganash::Display::Container *controls();
    virtual const Ganash::Graphics::DataInterface &getDataControls();
    virtual const Ganash::Graphics::DataInterface &getDataGraphics();

protected:
    Ganash::Graphics::DataInterface _data;

    Ganash::Display::Object    *_graphics;
    Ganash::Display::Container *_controls;
};

} // namespace Widget
} // namespace Ganash

#endif // GANASH_WIDGET_OBJECT_H
