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

#ifndef GANASH_GRAPHICS_PEN_H
#define GANASH_GRAPHICS_PEN_H

#include "color.h"
#include "brush.h"

namespace Ganash {
namespace Graphics {

class Pen
{
public:
    enum CapStyle {
        CapSquare,
        CapFlat,
        CapRound
    };
    enum JoinStyle {
        JoinBevel,
        JoinMiter,
        JoinRound
    };
    enum LineStyle {
        LineSolid,
        LineDash,
        LineDot,
        LineDashDot,
        LineDashDotDot,
        LineCustomDash
    };

    Pen();
    Pen(LineStyle style, Color *color);
    virtual ~Pen();
    void setLineStyle(LineStyle style);
    void setJoinStyle(JoinStyle style);
    void setCapStyle(CapStyle style);
    void setColor(Color *color);
    Color *getColor();
    void setBrush(Brush *brush);
    Brush *getBrush();
    void setWidth(double width);
    double getWidth();
protected:
    LineStyle _lineStyle;
    JoinStyle _joinStyle;
    CapStyle _capStyle;
    Color *_color;
    Brush *_brush;
    double _width;
};


} // namespace Display
} // namespace Ganash

#endif // GANASH_GRAPHICS_PEN_H
