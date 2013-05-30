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

#include "data-path.h"

Ganash::Graphics::DataPath::DataPath() :
    Ganash::Graphics::DataInterface(),
	_winding()
{
}

Ganash::Graphics::DataPath::DataPath(DataInterface &p) :
    Ganash::Graphics::DataInterface(),
    _winding()
{
    _commands = p._commands;
    _datas    = p._datas;
}

Ganash::Graphics::DataPath::~DataPath()
{
}

void Ganash::Graphics::DataPath::wide()
{
    _commands.push_back(Ganash::Graphics::DataPath::WideTo);// ?
}

void Ganash::Graphics::DataPath::moveTo(float x, float y)
{
    push_back(Ganash::Graphics::DataPath::MoveTo, x, y);
}

void Ganash::Graphics::DataPath::lineTo(float x, float y)
{
    push_back(Ganash::Graphics::DataPath::LineTo, x, y);
}

void Ganash::Graphics::DataPath::quadTo(float control_x, float control_y,
                                              float anchor_x, float anchor_y)
{
    push_back(Ganash::Graphics::DataPath::QuadTo, control_x, control_y,
              anchor_x, anchor_y);
}

void Ganash::Graphics::DataPath::cubicTo(float control1_x, float control1_y,
                                               float control2_x, float control2_y,
                                               float anchor_x, float anchor_y)
{
    push_back(Ganash::Graphics::DataPath::CubicTo, control1_x, control1_y,
              control2_x, control2_y,
              anchor_x, anchor_y);
}

int Ganash::Graphics::DataPath::commandCount() const
{
    return _commands.size();
}

Ganash::Graphics::DataPath::CommandType Ganash::Graphics::DataPath::commandAt(int index)
{
    return Ganash::Graphics::DataPath::CommandType(_commands.at(index));
}
