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

#ifndef GANASH_GRAPHICS_DATAINTERFACE_H
#define GANASH_GRAPHICS_DATAINTERFACE_H

#include <vector>

namespace Ganash {
namespace Graphics {

class DataInterface
{
public:
    DataInterface() :
        _commands(),
        _datas()
    {
    }

    inline void push_back(int command)
    {
        _commands.push_back(command);
    }
    inline void push_back(int command, double data1)
    {
        _commands.push_back(command);
        _datas.push_back(data1);
    }
    inline void push_back(int command, double data1, double data2)
    {
        _commands.push_back(command);
        _datas.push_back(data1);
        _datas.push_back(data2);
    }
    inline void push_back(int command, double data1, double data2, double data3, double data4)
    {
        _commands.push_back(command);
        _datas.push_back(data1);
        _datas.push_back(data2);
        _datas.push_back(data3);
        _datas.push_back(data4);
    }
    inline void push_back(int command, double data1, double data2, double data3, double data4, double data5, double data6)
    {
        _commands.push_back(command);
        _datas.push_back(data1);
        _datas.push_back(data2);
        _datas.push_back(data3);
        _datas.push_back(data4);
        _datas.push_back(data5);
        _datas.push_back(data6);
    }
    std::vector<int> _commands;
    std::vector<double> _datas;
};

}
}

#endif // GANASH_GRAPHICS_DATAINTERFACE_H
