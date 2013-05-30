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

#ifndef GANASH_GRAPHICS_BRUSH_H
#define GANASH_GRAPHICS_BRUSH_H

#include "color.h"

namespace Ganash {
namespace Graphics {

class Brush
{
public:
    enum PatternStyle
    {
        PatternSolid,
        PatternGradientRadial,
        PatternGradientLinear
    };
    Brush();
    Brush(Ganash::Graphics::Brush::PatternStyle style, Ganash::Graphics::Color *color);
    virtual ~Brush();
    void setStyle(PatternStyle style);
    void setColor(Color *color);
    Color *getColor();

protected:
    PatternStyle _style;
    Color *_color;

};


} // namespace Display
} // namespace Ganash

#endif // GANASH_GRAPHICS_BRUSH_H
