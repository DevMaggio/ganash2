//$Id: plugin-loader.h 2 2003-01-21 13:41:59Z maggio $ -*- c++ -*-

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

#ifndef GANASH_EXTENSION_PLUGINLOADER_H
#define GANASH_EXTENSION_PLUGINLOADER_H

#include "plugin-abstract.h"

#include <glibmm/module.h>

#include <string>

namespace Ganash {
namespace Extension {
	
	class PluginLoader
	{
	public:
		PluginLoader();
		PluginLoader(const std::string & fileName);
		~PluginLoader();
		std::string fileName() const;
		Ganash::Extension::PluginAbstract * instance();
		bool isLoaded() const;
		bool load();
		void setFileName(const std::string & fileName);
		bool unload();
	protected:
		Ganash::Extension::PluginAbstract * m_plugin;
		std::string m_fileName;
		bool m_loaded;
	private:
		Glib::Module * m_module;
	};
	
} // namespace Extension
} // namespace Ganash

#endif // GANASH_EXTENSION_PLUGINLOADER_H
