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

#include "brush.h"

Ganash::Graphics::Brush::Brush() :
    _style(Ganash::Graphics::Brush::PatternSolid),
    _color(0)
{
}

Ganash::Graphics::Brush::Brush(Ganash::Graphics::Brush::PatternStyle style, Ganash::Graphics::Color *color) :
    _style(style),
    _color(color)
{
}

Ganash::Graphics::Brush::~Brush()
{
}

void Ganash::Graphics::Brush::setStyle(const Ganash::Graphics::Brush::PatternStyle style)
{
    _style = style;
}

void Ganash::Graphics::Brush::setColor(Ganash::Graphics::Color *color)
{
    _color = color;
}

/*inline*/Ganash::Graphics::Color *Ganash::Graphics::Brush::getColor()
{
    return _color;
}
