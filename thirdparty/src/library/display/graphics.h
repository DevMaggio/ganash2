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

#ifndef GANASH_DISPLAY_GRAPHICS_H
#define GANASH_DISPLAY_GRAPHICS_H

#include "graphics/renderer.h"
#include "graphics/data-path.h"

namespace Ganash {
namespace Display {

class Graphics
{
public:
    Graphics();
    ~Graphics();
    // TODO setData Graphics::DataInterface
    void setData(const Ganash::Graphics::DataPath &data);
    inline Ganash::Graphics::DataInterface data(){ return _dataPath;}
    void setPen(Ganash::Graphics::Pen *pen);
    inline Ganash::Graphics::Pen* pen(){ return _pen;}
    void setBrush(Ganash::Graphics::Brush *brush);
    inline Ganash::Graphics::Brush* brush(){ return _brush;}

    void render(Ganash::Graphics::Renderer *renderer);

    inline void moveTo(double x, double y) { _dataPath.moveTo(x, y);}
    inline void lineTo(double x, double y) { _dataPath.lineTo(x, y);}
    inline void quadTo(double cx, double cy, double ax, double ay)
    { _dataPath.quadTo(cx, cy, ax, ay);}
    inline void cubicTo(double c1x, double c1y, double c2x, double c2y, double ax, double ay)
    { _dataPath.cubicTo(c1x, c1y, c2x, c2y, ax, ay);}

protected:
    Ganash::Graphics::DataPath _dataPath;
    Ganash::Graphics::Pen *_pen;
    Ganash::Graphics::Brush *_brush;
};

} // namespace Display
} // namespace Ganash

#endif // GANASH_DISPLAY_GRAPHICS_H
