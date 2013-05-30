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

#include "color.h"

Ganash::Graphics::Color::Color() :
    _red(0.0),
    _green(0.0),
    _blue(0.0),
    _alpha(1.0)
{
}

Ganash::Graphics::Color::Color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha) :
    _red(float(red)/255.0),
    _green(float(green)/255.0),
    _blue(float(blue)/255.0),
    _alpha(float(alpha)/255.0)
{
}

Ganash::Graphics::Color::Color(double red, double green, double blue, double alpha) :
    _red(red),
    _green(green),
    _blue(blue),
    _alpha(alpha)
{
}

Ganash::Graphics::Color::~Color()
{
}

/*inline*/double Ganash::Graphics::Color::getRed()
{
    return _red;
}

/*inline*/double Ganash::Graphics::Color::getGreen()
{
    return _green;
}

/*inline*/double Ganash::Graphics::Color::getBlue()
{
    return _blue;
}

/*inline*/double Ganash::Graphics::Color::getAlpha()
{
    return _alpha;
}
