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

#ifndef GANASH_GRAPHICS_COLOR_H
#define GANASH_GRAPHICS_COLOR_H

namespace Ganash {
namespace Graphics {

class Color
{
public:
    explicit Color();
    Color(double red, double green, double blue, double alpha = 1.0);
    Color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha = 255);
    virtual ~Color();
    double getRed();
    double getGreen();
    double getBlue();
    double getAlpha();
    //toString();
    //toInteger();
protected:
    float _red;
    float _green;
    float _blue;
    float _alpha;
};


} // namespace Display
} // namespace Ganash

#endif // GANASH_GRAPHICS_COLOR_H
