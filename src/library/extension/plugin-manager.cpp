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

#include "plugin-manager.h"
#include "plugin-loader.h"

#include <gtkmm/main.h>
#include <glibmm/fileutils.h>
#include <glibmm/miscutils.h>

#include <list>
#include <string>
#include <iostream>

Ganash::Extension::PluginManager::PluginManager() :
  m_paths()
{

}

Ganash::Extension::PluginManager::~PluginManager()
{

}

sigc::signal<void, std::string, std::string, float> Ganash::Extension::PluginManager::signal_progress()
{
  return m_signal_progress;
}

int Ganash::Extension::PluginManager::size()
{
  return 20;
}

/**
 * @brief Ganash::Extension::PluginManager::addPluginPath
 * @param path
 */
void Ganash::Extension::PluginManager::addLoaderPath(const std::string &path)
{
	m_paths.push_back(path);
}

void Ganash::Extension::PluginManager::load()
{
  for(std::list<std::string>::const_iterator it =  m_paths.begin(); it != m_paths.end(); ++it)
    {
      const std::string directory_path = *it;

      try
      {
          Glib::Dir dir(directory_path);

          for(Glib::Dir::iterator p = dir.begin(); p != dir.end(); ++p)
            {
              const std::string file_name = *p;
              if(! isPluginFilename(file_name))
                {
                  continue;
                }

              // @TODO isPluginEnable
              // if verbose
              const std::string file_path = Glib::build_filename(directory_path, file_name);
              loader.setFileName(file_path);

              m_signal_progress.emit("Loading", loader.fileName(), 0.0);

              loader.load();
              if(loader.isLoaded())
                {
                  Ganash::Extension::PluginAbstract * plugin = loader.instance();
                  m_plugins.push_front(plugin);
                }
            }
      }
      catch(Glib::FileError& e)
      {
        std::cout << "Catched " << e.what() << std::endl;
        continue;
      }
    }
/*
  for(int i=0; i<size(); i++)
    {
      g_usleep(0.1 * 1000 * 1000);
      m_signal_progress.emit("Loading", "libname.so", float(i)/float(size()));
    }
*/
}

void Ganash::Extension::PluginManager::init()
{
  for(std::list<Ganash::Extension::PluginAbstract*>::const_iterator it =  m_plugins.begin(); it != m_plugins.end(); ++it)
    {
      Ganash::Extension::PluginAbstract* plugin = *it;
      m_signal_progress.emit("Initialisation", plugin->get_name(), 0.0);
      plugin->init();
    }

/*
  for(int i=0; i<size(); i++)
    {
      g_usleep(0.01 * 1000 * 1000);
      m_signal_progress.emit("Initialisation", "Ganash::Plugin::Name", float(i)/float(size()));
    }
*/
}

Ganash::Extension::PluginManager * Ganash::Extension::PluginManager::instance()
{
	static Ganash::Extension::PluginManager * instance = 0;
	if(instance==0) {
		instance = new Ganash::Extension::PluginManager();
	}
	return instance;
}

Ganash::Extension::PluginAbstract * Ganash::Extension::PluginManager::getPluginByClassName(std::string name)
{
  Ganash::Extension::PluginAbstract* plugin = 0;
  for(std::list<Ganash::Extension::PluginAbstract*>::const_iterator it =  m_plugins.begin(); it != m_plugins.end(); ++it)
    {
      Ganash::Extension::PluginAbstract* p = *it;
      if(name == p->get_name())
        {
          plugin = p;
          break;
        }
    }

  return plugin;
}

bool Ganash::Extension::PluginManager::isPluginFilename(const std::string &filename)
{
	const std::string::size_type size = filename.size();

	const std::string suffix = std::string(".") + G_MODULE_SUFFIX;
	const std::string::size_type suffix_size = suffix.size();
	if(size < suffix_size)
		return false;

	const std::string possible_suffix = filename.substr(size - suffix_size);
	if(possible_suffix != suffix)
	  return false;

	return true;
}
