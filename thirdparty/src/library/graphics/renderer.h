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

#ifndef GANASH_GRAPHICS_RENDERER_H
#define GANASH_GRAPHICS_RENDERER_H


#include "data-path.h"
#include "pen.h"
#include "brush.h"

#include <cairomm/context.h>


namespace Ganash {
namespace Graphics {

class Renderer
{
public:
    Renderer();
    virtual ~Renderer();
    virtual void save();
    virtual void restore();
    virtual void setPen(Pen *pen);
    virtual void setBrush(Brush *brush);
    virtual void moveTo(double x ,  double y) = 0;
    virtual void lineTo(double x ,  double y) = 0;
    virtual void cubicTo(double x1, double y1, double x2, double y2, double x3, double y3) = 0;
    virtual void stroke() = 0;
    virtual void fill() = 0;
    virtual void paint() = 0;

    // default style : setDefaultPen, etc...
    static Ganash::Graphics::Pen *default_pen;
    static Ganash::Graphics::Brush *default_brush;
protected:
    struct Style
    {
        Pen *pen;
        Brush *brush;
    };
    std::list<Style> _stack;
    Pen *_pen;
    Brush *_brush;
};


class RendererCairo : public Renderer
{
public:
    RendererCairo(const Cairo::RefPtr<Cairo::Context> &cr);
    virtual void setPen(Pen *pen);
    virtual void setBrush(Brush *brush);
    virtual void moveTo(double x, double y);
    virtual void lineTo(double x, double y);
    virtual void cubicTo(double x1, double y1, double x2, double y2, double x3, double y3);
    virtual void stroke();
    virtual void fill();
    virtual void paint();
protected:
    const Cairo::RefPtr<Cairo::Context> &_cairo;
};


} // namespace Display
} // namespace Ganash

#endif // GANASH_GRAPHICS_RENDERER_H
