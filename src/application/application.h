//$Id: application.cpp 836 2013-01-03 03:02:38Z maggio $ -*- c++ -*-

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

#ifndef GANASH_APPLICATION_H
#define GANASH_APPLICATION_H

#include "bootstrap.h"
#include "ui/application-window.h"

#include <gtkmm/application.h>
#include <giomm/application.h>
#include <glibmm/stringutils.h>
#include <giomm/menu.h>
#include <giomm/simpleaction.h>
#include <giomm/simpleactiongroup.h>
#include <glibmm/threads.h>

namespace Ganash {

class Application : public Gtk::Application
{
public:
  enum Mode
    {
      Window,
      Console
    };
  static Glib::RefPtr<Ganash::Application> create();
  static Ganash::Application *instance();
  static Ganash::ApplicationWindow *get_main_window();

  Ganash::Bootstrap *m_bootstrap;
protected:
  Application();
  explicit Application(const Glib::ustring & application_id, Gio::ApplicationFlags flags = Gio::APPLICATION_FLAGS_NONE);
  explicit Application(int &argc, char ** &argv, const Glib::ustring & application_id, Gio::ApplicationFlags flags = Gio::APPLICATION_FLAGS_NONE);
  static Ganash::Application *_instance;

  //not virtual int run(int argc, char **argv);
  //not virtual int run();
  //virtual void on_activate();
  void print_help();
  void print_version();
  void print_license();

protected:
        int preferences;/*Ganash::Preference < Dom*/
        virtual int on_command_line(const Glib::RefPtr<Gio::ApplicationCommandLine>&command_line);
        virtual void on_activate();
        virtual void on_startup();
        virtual void property_startup();

        //void on_window_hide(Gtk::Window* window);
        void on_action_something(const Glib::VariantBase& parameter);
        Glib::RefPtr<Gio::Menu> m_menu;
        Glib::RefPtr<Gio::SimpleAction> m_action;

  void bootstrap_progress(std::string context, std::string message, float fraction);
  int loc_argc;
  char ** loc_argv;
  Gtk::Window *main_window;



};

} // namespace Ganash

#endif // GANASH_APPLICATION_H
