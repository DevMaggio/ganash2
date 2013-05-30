//$Id: plugin-abstract.cpp 2 2003-01-21 13:41:59Z maggio $ -*- c++ -*-

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

#include "plugin-abstract.h"

Ganash::Extension::PluginAbstract::PluginAbstract():
  m_name("")
{
}

Ganash::Extension::PluginAbstract::~PluginAbstract()
{
}

std::string Ganash::Extension::PluginAbstract::get_name()
{
  return m_name;
}

bool Ganash::Extension::PluginAbstract::init()
{
	return true;
}

void Ganash::Extension::PluginAbstract::setup()
{

}
