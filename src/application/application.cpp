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


#include "application.h"
#include "ui/application-window.h"
#include "ui/action-manager.h"

#include <glibmm/optioncontext.h>


// But unlike normal pointers, RefPtrs are automatically initialized to null
Ganash::Application *Ganash::Application::_instance = 0;

Ganash::Application::Application(const Glib::ustring & application_id, Gio::ApplicationFlags flags)
: Gtk::Application(application_id, flags)
{
}

Ganash::Application::Application(int &argc, char ** &argv, const Glib::ustring & application_id, Gio::ApplicationFlags flags) :
  Gtk::Application(argc, argv, application_id, flags)
{
}

Glib::RefPtr<Ganash::Application> Ganash::Application::create()
{
  return Glib::RefPtr<Ganash::Application>( new Ganash::Application("org.gnome.ganash", Gio::APPLICATION_HANDLES_COMMAND_LINE|Gio::APPLICATION_HANDLES_OPEN) );
}

Ganash::Application *Ganash::Application::instance()
{
  if(!Ganash::Application::_instance)
    {
      Ganash::Application::_instance = new Ganash::Application("org.gnome.ganash", Gio::APPLICATION_HANDLES_COMMAND_LINE|Gio::APPLICATION_HANDLES_OPEN);
    }

  return Ganash::Application::_instance;
}

Ganash::ApplicationWindow *Ganash::Application::get_main_window()
{
  Ganash::Application *application = Ganash::Application::instance();
  Ganash::ApplicationWindow *win;
  std::vector<Gtk::Window*> windows = application->get_windows();

  std::vector<Gtk::Window*>::iterator i;
  for( i = windows.begin(); i != windows.end(); i++ )
    {
      Gtk::Window *w = *i;
      if( w->get_name() == "gtkmm__GtkApplicationWindow")
        {
          win = static_cast<Ganash::ApplicationWindow *>(w);
        }
    }
  return win;
}


int Ganash::Application::on_command_line(const Glib::RefPtr<Gio::ApplicationCommandLine>&command_line)
{
  g_print("on_command_line\n");

  // @see example http://git.gnome.org/browse/glibmm/tree/examples/options/main.cc?h=glibmm-2-24
  // @see console|graphic http://stackoverflow.com/questions/13852421/gtkmm-3-parse-command-line-with-gtkapplication

  bool          entry_version = FALSE;
  bool          entry_license = FALSE;
  bool          entry_mode    = FALSE;


  Glib::OptionContext context("[FICHIER|URI...]");

  Glib::OptionEntry option_version;
  option_version.set_short_name('v');
  option_version.set_long_name("version");
  option_version.set_description("Affiche l'information de version et quitte");

  Glib::OptionEntry option_license;
  option_license.set_short_name('l');
  option_license.set_long_name("license");
  option_license.set_description("Affiche l'information de licence et quitte");

  Glib::OptionEntry option_mode;
  option_mode.set_short_name('c');
  option_mode.set_long_name("console");
  option_mode.set_description("Lance l'application en mode console interactif");

  Glib::OptionGroup group_application("options", "Options de l'application :", "Affiche les options de l'application");
  group_application.add_entry(option_version, entry_version);
  group_application.add_entry(option_license, entry_license);
  group_application.add_entry(option_mode,    entry_mode);
  context.add_group(group_application);

  int argc;
  char **argv = command_line->get_arguments(argc);
  loc_argc = argc;
  loc_argv = argv;

  try
  {
    context.parse(argc, argv);
    if(entry_version)
      {
        print_version();
        // Ganash::ApplicationCommand::print_version();
      }
    else if(entry_license)
      {
        print_license();
        // Ganash::ApplicationCommand::print_license();
      }
    if(entry_mode)
      {
        g_print("console activate\n");
      }
    else
      {
        activate();
      }
  }
  catch(const Glib::Error& ex)
  {
    g_print("%s\n", ex.what().c_str() );
  }


  return 0;
}

void Ganash::Application::on_startup()
{
  g_print("on_startup\n");

  Gtk::Application::on_startup();

}

void Ganash::Application::property_startup()
{
  g_print("property_startup\n");
  //Sets or unsets the application menu for application.
  //This can only be done in the primary instance of the application, after it has been registered. Application::property_startup() is a good place to call this.
}

void Ganash::Application::on_activate()
{
  g_print("on_activate\n");


  m_bootstrap = new Ganash::Bootstrap(loc_argc, loc_argv);

  /*
  gimp_init_malloc ();
  gimp_env_init (FALSE);
  gimp_log_init ();
  gimp_init_i18n ();
  */

  //m_bootstrap->load_theme();
  add_window(*m_bootstrap->m_splash);

  m_bootstrap->signal_progress().connect(sigc::mem_fun(*this, &Ganash::Application::bootstrap_progress));
  //m_bootstrap->signal_complete().connect(sigc::mem_fun(*this, &Ganash::Application::bootstrap_complete));
  m_bootstrap->load_plugin();


  Ganash::ApplicationWindow *window = new Ganash::ApplicationWindow();
  add_window(*window);
  window->set_default_size(900, 600);
  window->set_position(Gtk::WIN_POS_CENTER);
  window->show_all();

  bootstrap_progress("", "", 0.0);

  m_bootstrap->init_plugin();

  remove_window(*m_bootstrap->m_splash);
  m_bootstrap->m_splash->shutdown();

  Ganash::Ui::ActionManager *actionManager = Ganash::Ui::ActionManager::instance();

  //actionManager->setAction("/menubar/menu", "Edit");
  //actionManager->setAction("/menubar/menu/menu", "Insert");
  //actionManager->setAction("/menubar/menu/menu/menuitem", "Path");
  //actionManager->setAction("/menubar/menu/menu/menuitem", "Shape");
  //actionManager->setAction("/menubar/menu/menu/menuitem[@action=rectangle]", "Rect");
  // Control/Launch/Player

  char * xmlbuff = actionManager->toString();
  printf("%s\n", xmlbuff);
  xmlFree(xmlbuff);

}

void Ganash::Application::bootstrap_progress(std::string context, std::string message, float fraction)
{
  m_bootstrap->m_splash->update(context, message, fraction);
  while( Gtk::Main::events_pending() )
    Gtk::Main::iteration();
}

/*void Ganash::Application::bootstrap_complete()
{
}*/


void Ganash::Application::on_action_something(const Glib::VariantBase& /* parameter */)
{
  g_print("%s\n", G_STRFUNC);
}
/*
void Ganash::Application::on_window_hide(Gtk::Window* window)
{

  delete window;
}
*/





void Ganash::Application::print_version()
{
  g_print("Ganash 0.0.1 (Jan 27 2013)\n");
}

void Ganash::Application::print_license()
{
  print_version();
  g_print("\n");
  g_print("Copyright (C) 2012-2013  Sergio DE VASCONCELOS\n");
}
