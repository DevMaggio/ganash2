//$Id: plugin-loader.cpp 2 2003-01-21 13:41:59Z maggio $ -*- c++ -*-

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

#include "plugin-loader.h"
#include "gtk/gtk.h"


#include <iostream>

Ganash::Extension::PluginLoader::PluginLoader() :
	m_plugin(0),
	m_fileName(""),
	m_loaded(false)
{
	
	
}

Ganash::Extension::PluginLoader::PluginLoader(const std::string & fileName) :
	m_plugin(0),
	m_fileName(fileName),
	m_loaded(false)
{
	
	
}

Ganash::Extension::PluginLoader::~PluginLoader()
{
	unload();
}

std::string Ganash::Extension::PluginLoader::fileName() const
{
	return m_fileName;
}

Ganash::Extension::PluginAbstract * Ganash::Extension::PluginLoader::instance()
{
	if(m_plugin==0) {
		load();
	}
	
	return m_plugin;
}

bool Ganash::Extension::PluginLoader::isLoaded() const
{
	return m_loaded;
}

bool Ganash::Extension::PluginLoader::load()
{
	if (m_fileName.empty()) {
		return false;
	}



	//@FIXME Flags parameter
	//Glib::Module module(m_fileName);
	m_module = new Glib::Module(m_fileName);
	if(m_module)
	{
	    // signal_pulse()
		//@TODO sanity check
		//@see module.get_supported()
		typedef Ganash::Extension::PluginAbstract * (*LoaderPlugin)(void);
		LoaderPlugin getPluginInstance;
		bool found = m_module->get_symbol("getInstance", (void*&)getPluginInstance);
		if(found) {
			if(getPluginInstance) {
				m_plugin = getPluginInstance();
				m_loaded = true;
				return true;
			} else {
				std::cout << "symbole is null" << std::endl;
				std::cout << m_module->get_last_error() << std::endl;
			}
		} else {
			std::cout << "symbole wasn't found" << std::endl;
			std::cout << m_module->get_last_error() << std::endl;
		}
	} else {
		std::cout << "module not load" << std::endl;
		std::cout << m_module->get_last_error() << std::endl;
	}
	return false;
}

void Ganash::Extension::PluginLoader::setFileName(const std::string & fileName)
{
	if(m_fileName != fileName) {
		m_loaded = false;
	}
	m_fileName = fileName;
}

bool Ganash::Extension::PluginLoader::unload()
{
	if(m_plugin==0) {
		return true;
	}
	// @TODO unload module
	// GModuleUnload(&module)
	// @see http://developer.gnome.org/glib/2.28/glib-Dynamic-Loading-of-Modules.html
	return true;
}
