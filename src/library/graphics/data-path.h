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

#ifndef GANASH_GRAPHICS_DATAPATH_H
#define GANASH_GRAPHICS_DATAPATH_H

#include "data-interface.h"

#include <vector>

namespace Ganash {
namespace Graphics {

class DataPath : public Ganash::Graphics::DataInterface
{
public:

    enum WindingType {
        NonZero,
        EvenOdd
    };

    enum CommandType {
        WideTo,
        MoveTo,
        LineTo,
        QuadTo,
        CubicTo
    };

    DataPath();
    DataPath(DataInterface &p);
    //GraphicsPath(QVector<GraphicsPathCommand> commands, QVector<qreal> data, GraphicsPathWinding winding);
    ~DataPath();

    // TODO inline
	void wide();
    void moveTo(float x, float y);
    void lineTo(float x, float y);
    void quadTo(float control_x, float control_y, float anchor_x, float anchor_y);
    void cubicTo(float control1_x, float control1_y, float control2_x, float control2_y, float anchor_x, float anchor_y);
	// function relative to Winding
	int commandCount() const;
    CommandType commandAt(int index);

    WindingType _winding;
protected:
private:
};

} // namespace Display
} // namespace Ganash

#endif // GANASH_GRAPHICS_DATAPATH_H
