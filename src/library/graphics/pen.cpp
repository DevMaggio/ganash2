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

#include "pen.h"

Ganash::Graphics::Pen::Pen() :
    _lineStyle(Ganash::Graphics::Pen::LineSolid),
    _joinStyle(Ganash::Graphics::Pen::JoinRound),
    _capStyle(Ganash::Graphics::Pen::CapRound),
    _color(0),
    _brush(0),
    _width(1.0)
{
}

Ganash::Graphics::Pen::Pen(LineStyle style, Color *color) :
    _lineStyle(style),
    _joinStyle(Ganash::Graphics::Pen::JoinRound),
    _capStyle(Ganash::Graphics::Pen::CapRound),
    _color(color),
    _brush(0),
    _width(1.0)
{

}

Ganash::Graphics::Pen::~Pen()
{
}

void Ganash::Graphics::Pen::setLineStyle(LineStyle style)
{
    _lineStyle = style;
}

void Ganash::Graphics::Pen::setJoinStyle(JoinStyle style)
{
    _joinStyle = style;
}

void Ganash::Graphics::Pen::setCapStyle(CapStyle style)
{
    _capStyle = style;
}

void Ganash::Graphics::Pen::setColor(Ganash::Graphics::Color *color)
{
    _color = color;
}

/*inline*/Ganash::Graphics::Color *Ganash::Graphics::Pen::getColor()
{
    return _color;
}

void Ganash::Graphics::Pen::setBrush(Ganash::Graphics::Brush *brush)
{
    _brush = brush;
}

Ganash::Graphics::Brush *Ganash::Graphics::Pen::getBrush()
{
    return _brush;
}

void Ganash::Graphics::Pen::setWidth(double width)
{
    _width = width;
}

double Ganash::Graphics::Pen::getWidth()
{
    return _width;
}
