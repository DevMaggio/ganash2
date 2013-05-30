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

#include "graphics.h"
#include <iostream>

Ganash::Display::Graphics::Graphics() :
    _pen(0),
    _brush(0)
{

}

Ganash::Display::Graphics::~Graphics()
{
}

void Ganash::Display::Graphics::render(Ganash::Graphics::Renderer *renderer)
{
    //cr->save();
    //cr->set_source_rgba(1.0, 0.0, 1.0, 1.0);
    //std::cout << "Ganash::Display::Graphics::render : " <<  _dataPath._commands.size() << std::endl;

    //Ganash::Graphics::DataPath::CommandType command;
    int command;
    int iData = 0;
    for(int i = 0; i<_dataPath._commands.size(); i+=1)
    {
        command = _dataPath._commands.at(i);
        switch(command)
        {
        case Ganash::Graphics::DataPath::MoveTo :
            renderer->moveTo(_dataPath._datas[iData], _dataPath._datas[iData+1]);
            iData += 2;
            break;
        case Ganash::Graphics::DataPath::LineTo :
            renderer->lineTo(_dataPath._datas[iData], _dataPath._datas[iData+1]);
            iData += 2;
            break;
        case Ganash::Graphics::DataPath::QuadTo :
            {
                double c1x = (_dataPath._datas[iData+2] + 2 * _dataPath._datas[iData])   / 3;
                double c1y = (_dataPath._datas[iData-1] + 2 * _dataPath._datas[iData+1]) / 3;
                double c2x = (_dataPath._datas[iData+2] + 2 * _dataPath._datas[iData])   / 3;
                double c2y = (_dataPath._datas[iData+3] + 2 * _dataPath._datas[iData+1]) / 3;
                renderer->cubicTo(c1x, c1y, c2x, c2y, _dataPath._datas[iData+2], _dataPath._datas[iData+3]);
            }
            iData += 4;
            break;
        case Ganash::Graphics::DataPath::CubicTo :
            renderer->cubicTo(_dataPath._datas[iData], _dataPath._datas[iData+1],
                    _dataPath._datas[iData+2], _dataPath._datas[iData+3],
                    _dataPath._datas[iData+4], _dataPath._datas[iData+5]);
            iData += 6;
            break;
        }
    }


    if(_pen!=0 || _brush!=0)
    {
        renderer->save();
        renderer->setPen(_pen);
        renderer->setBrush(_brush);
    }

    renderer->paint();

    if(_pen!=0 || _brush!=0)
    {
        renderer->restore();
    }
}

/*
void Ganash::Display::Graphics::moveTo(double x, double y)
{
    _path._commands.push_back(Ganash::Graphics::DataPath::MoveTo);
    _path._datas.push_back(x);
    _path._datas.push_back(y);
}
*/
void Ganash::Display::Graphics::setPen(Ganash::Graphics::Pen *pen)
{
    _pen = pen;
}

void Ganash::Display::Graphics::setBrush(Ganash::Graphics::Brush *brush)
{
    _brush = brush;
}

void Ganash::Display::Graphics::setData(const Ganash::Graphics::DataPath &data)
{
    _dataPath = data;
}
