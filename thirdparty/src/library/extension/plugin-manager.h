//$Id: plugin-manager.h 2 2003-01-21 13:41:59Z maggio $ -*- c++ -*-

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

#ifndef GANASH_EXTENSION_PLUGINMANAGER_H
#define GANASH_EXTENSION_PLUGINMANAGER_H

//#include "plugin-abstract.h"
#include "plugin-loader.h"

#include <glibmm/dispatcher.h>
#include <sigc++/sigc++.h>
#include <gtkmm.h>

#include <string>
#include <list>

namespace Ganash {
namespace Extension {

  class PluginManager : public sigc::trackable
  {
  public:
    PluginManager();
    ~PluginManager();

    int size();
    void addLoaderPath(const std::string &path);
    void load();
    void init();
    //Ganash::Extension::PluginAbstract * getPluginByClassName ( const QString & className ) const;
    //Ganash::Extension::PluginAbstract * getPluginByName ( const QString & name ) const;
    Ganash::Extension::PluginAbstract * getPluginByClassName(std::string name);

    Ganash::Extension::PluginLoader loader;

    static Ganash::Extension::PluginManager * instance();

    sigc::signal<void, std::string, std::string, float> signal_progress();

  protected:
    sigc::signal<void, std::string, std::string, float> m_signal_progress;
    std::list<Ganash::Extension::PluginAbstract*> m_plugins;

  protected:
    std::list<std::string> m_paths;
    bool isPluginFilename(const std::string &filename);


  };
	
} // namespace Extension
} // namespace Ganash

#endif // GANASH_EXTENSION_PLUGINMANAGER_H
