//$Id: welcome.h 2 2003-01-21 13:41:59Z maggio $ -*- c++ -*-

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

#ifndef GANASH_PLUGIN_WELCOME_H
#define GANASH_PLUGIN_WELCOME_H

#include "extension/plugin-abstract.h"

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>

//G_MODULE_EXPORT myFunction
#include <iostream>


namespace Ganash {
namespace Plugin {

	class Welcome : public Ganash::Extension::PluginAbstract
	{
	public:
		Welcome();
		virtual ~Welcome();

		virtual bool init();

		Gtk::Widget *viewWelcome();

		void on_menu_file_new_baz();
	protected:
	  void getting_start();
	};

} // namespace Plugin
} // namespace Ganash

// EXPORT_PLUGIN(Ganash::Plugin::Welcome, "org.ganash.plugin.Welcome/1.0.0")

extern "C" {
	Ganash::Extension::PluginAbstract* getInstance(void);
}

#endif // GANASH_PLUGIN_WELCOME_H
