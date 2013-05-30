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

#include "renderer.h"

Ganash::Graphics::Pen   *Ganash::Graphics::Renderer::default_pen   = new Ganash::Graphics::Pen(
            Ganash::Graphics::Pen::LineSolid,
            new Ganash::Graphics::Color()
            );
Ganash::Graphics::Brush *Ganash::Graphics::Renderer::default_brush = new Ganash::Graphics::Brush(
            Ganash::Graphics::Brush::PatternSolid,
            new Ganash::Graphics::Color()
            );


Ganash::Graphics::Renderer::Renderer() :
    _stack(),
    _pen(Ganash::Graphics::Renderer::default_pen),
    _brush(Ganash::Graphics::Renderer::default_brush)
{
}

Ganash::Graphics::Renderer::~Renderer()
{
}

void Ganash::Graphics::Renderer::setPen(Ganash::Graphics::Pen *pen)
{
    _pen = pen;
}

void Ganash::Graphics::Renderer::setBrush(Ganash::Graphics::Brush *brush)
{
    _brush = brush;
}

void Ganash::Graphics::Renderer::save()
{
    Ganash::Graphics::Renderer::Style style;
    style.pen   = _pen;
    style.brush = _brush;
    _stack.push_back(style);
}

void Ganash::Graphics::Renderer::restore()
{
    Ganash::Graphics::Renderer::Style style = _stack.back();
    _pen   = style.pen;
    _brush = style.brush;
    _stack.pop_back();
}

/**
 * @brief Ganash::Graphics::RendererCairo::RendererCairo
 * @param cr
 */
Ganash::Graphics::RendererCairo::RendererCairo(const Cairo::RefPtr<Cairo::Context>& cr) :
    _cairo(cr)
{
}

void Ganash::Graphics::RendererCairo::moveTo(double x, double y)
{
    _cairo->move_to(x, y);
}

void Ganash::Graphics::RendererCairo::lineTo(double x, double y)
{
    _cairo->line_to(x, y);
}

void Ganash::Graphics::RendererCairo::cubicTo(double x1, double y1, double x2, double y2, double x3, double y3)
{
    _cairo->curve_to(x1, y1, x2, y2, x3, y3);
}


void Ganash::Graphics::RendererCairo::setPen(Ganash::Graphics::Pen *pen)
{
    Ganash::Graphics::Renderer::setPen(pen);
}

void Ganash::Graphics::RendererCairo::setBrush(Ganash::Graphics::Brush *brush)
{
    Ganash::Graphics::Renderer::setBrush(brush);
    // _cairo->set_surface...
}

void Ganash::Graphics::RendererCairo::paint()
{
    if(_brush)
    {
        _cairo->set_source_rgba(_brush->getColor()->getRed(),
                                _brush->getColor()->getGreen(),
                                _brush->getColor()->getBlue(),
                                _brush->getColor()->getAlpha());
        if(_pen)
        {
            _cairo->fill_preserve();
        }
        else
        {
            _cairo->fill();
        }
    }
    if(_pen)
    {
        _cairo->set_source_rgba(_pen->getColor()->getRed(),
                                _pen->getColor()->getGreen(),
                                _pen->getColor()->getBlue(),
                                _pen->getColor()->getAlpha());
        _cairo->set_line_width(_pen->getWidth());
        _cairo->stroke();
    }
}

void Ganash::Graphics::RendererCairo::stroke()
{
    _cairo->set_source_rgba(_pen->getColor()->getRed(),
                            _pen->getColor()->getGreen(),
                            _pen->getColor()->getBlue(),
                            _pen->getColor()->getAlpha());
    _cairo->set_line_width(_pen->getWidth());
    _cairo->stroke_preserve();
    //_cairo->stroke();
}

void Ganash::Graphics::RendererCairo::fill()
{
    if(_brush)
    {
        _cairo->set_source_rgba(_brush->getColor()->getRed(),
                                _brush->getColor()->getGreen(),
                                _brush->getColor()->getBlue(),
                                _brush->getColor()->getAlpha());
        _cairo->fill();
        //_cairo->fill_preserve();
    }
}
