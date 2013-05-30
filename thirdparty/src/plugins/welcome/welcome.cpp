//$Id: welcome.cpp 2 2003-01-21 13:41:59Z maggio $ -*- c++ -*-

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

#include "welcome.h"

#include "application.h"
#include "ui/action-manager.h"
#include "ui/application-window.h"
#include "ui/stock.h"


#include "gdl/gdl-dock.h"
#include "gdl/gdl-dock-frame.h"
#include "gdl/gdl-dock-item.h"
#include "gdl/gdl-dock-object.h"
#include "gdl/gdl-dock-master.h"
#include "gdl/gdl-dock-layout.h"
#include "gdl/gdl-dock-item-grip.h"


#include <gtkmm.h>

#include <iostream>

Ganash::Plugin::Welcome::Welcome() :
        Ganash::Extension::PluginAbstract()
{
  m_name = std::string("org.ganash.plugin.Welcome");
  std::cout << "new Ganash::Plugin::Welcome()" << std::endl;
}

Ganash::Plugin::Welcome::~Welcome()
{
}

// load()
// register()
// unregistre()
// unload()


bool Ganash::Plugin::Welcome::init()
{

  /*
       Core::ActionManager *am = Core::ICore::instance()->actionManager();

       QAction *action = new QAction(tr("Example action"), this);
       Core::Command *cmd = am->registerAction(action, Constants::ACTION_ID,
                                               Core::Context(Core::Constants::C_GLOBAL));
       cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+A")));
       connect(action, SIGNAL(triggered()), this, SLOT(triggerAction()));
   */

/*
  Ganash::Core::ActionManager *actionManager = Ganash::Core::ActionManager::instance();
  //File|New sub menu:
  Glib::RefPtr<Gtk::Action> action = Gtk::Action::create("FileNewBaz", Gtk::Stock::NEW, "New Baz", "Create a new file baz");

  actionManager->registerAction(Gtk::Action::create("FileNew", Gtk::Stock::NEW));
  //File menu:
  actionManager->registerAction(Gtk::Action::create("FileMenu", "_File"));

  Glib::ustring ui_info_plugin =
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='FileMenu'>"
        "      <menu action='FileNew'>"
        "        <menuitem action='FileNewBaz'/>"
        "      </menu>"
        "    </menu>"
        "  </menubar>"
        "</ui>";
  actionManager->registerAction(action, sigc::mem_fun(*this, &Ganash::Plugin::Welcome::on_menu_file_new_baz));
  actionManager->merge(ui_info_plugin);
  */

  // Install menu : can be donne by definition.ui.xml
  Ganash::Ui::ActionManager *actionManager = Ganash::Ui::ActionManager::instance();
  Glib::RefPtr<Gtk::Action> action = Gtk::Action::create("FileNewBaz", Gtk::Stock::NEW, "New Baz", "Create a new file baz");

  Glib::ustring ui_info_plugin =
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='FileMenu'>"
        "      <menu action='FileNew'>"
        "        <menuitem action='FileNewBaz'/>"
        "      </menu>"
        "    </menu>"
        "  </menubar>"
        "</ui>";

  Glib::ustring path("/MenuBar/FileMenu/FileNew");
  Glib::ustring name("FileNewBaz");
  Glib::ustring _action("FileNewBaz");
  actionManager->m_refActionGroup->add(action, sigc::mem_fun(*this, &Ganash::Plugin::Welcome::on_menu_file_new_baz));
  actionManager->m_refUIManager->add_ui(actionManager->m_refUIManager->new_merge_id(), path, name, _action, Gtk::UI_MANAGER_MENUITEM, false);


  /*
Core::Context
Core::Constant

Ganash::Core::ActionManager *am = Ganash::Core::Interface::instance()->actionManager();

Ganash::Core::ActionManager *am = Ganash::Core::ActionManager::instance();

QAction *action = new QAction(tr("Example action"), this);
Core::Command *cmd = am->registerAction(action, Constants::ACTION_ID, Core::Context(Core::Constants::C_GLOBAL));
cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+A")));
connect(action, SIGNAL(triggered()), this, SLOT(triggerAction()));
   */



        /**
Q_UNUSED(args);
Q_UNUSED(errMsg);

// Fetch the action manager
Core::ActionManager* am = Core::ICore::instance()->actionManager();
// Create a command for "About DoNothing".
Core::Command* cmd = am->registerAction(new QAction(this), "DoNothingPlugin.AboutDoNothing", QList<int>() << Core::Constants::C_GLOBAL_ID);
cmd->action()->setText("About DoNothing");
// Add the command to Help menu
am->actionContainer(Core::Constants::M_HELP)->addAction(cmd);
return true;

         */
/*
 * app = Ganash::Application::instance();
 *
 * Ganash::Kernel::Document* doc = app->document();
 * Ganash::Console* cli = app->console();
 * Ganash::Window* win = app->window();
 * if(win) else "Not window available"
 *
 * Core::Action act = app->actionManager();
 * Core::Container ctn = app->containerManager();
 * Core::Command* cmd = app->registerAction()
 *
 * Application
 *  -> ApplicationWindow
 *  -> ApplicationConsole
 *
 * Gtk::Application::set_menubar()
 * window = new Gtk::ApplicationWindow (app);
 *
 */


  // win->child_by_name();
  // Ganash::Core::Interface::instance()->containerManager();
  // Ganash::Core::Interface::instance()->containerManager();
  // Ganash::Core::ContainerManager *cm = Ganash::Core::ContainerManager::instance();
  // cm->get_child_by_name("main");
  // cm = Ganash::Core::ContainerManager::instance();

  // win = Application::instance()->activeWindow();
  // win->set_ui('layout.xml');
  // win->set_widget(gtk_label_new("main content"), "main");
  // itk_window_set_widget(win, label, ITK_WINDOW_MAIN_DOCK);

  Ganash::ApplicationWindow *win = Ganash::Application::get_main_window();

  /*
  GdlDockLayout * layout = gdl_dock_layout_new(G_OBJECT(win->_dockbar->gobj()));
  if(gdl_dock_layout_load_from_file (GDL_DOCK_LAYOUT (layout), filename.c_str()))
    {
      if (!gdl_dock_layout_load_layout (GDL_DOCK_LAYOUT (layout), "__default__"))
        {
          g_warning ("Loading layout failed!!");
        }
    }
  else
    {
      g_print("Load failed\n");
    }
  */


  /*
  GdlDockMaster *master  = GDL_DOCK_MASTER (gdl_dock_object_get_master (GDL_DOCK_OBJECT (win->_dockbar->gobj())));
  //GdlDockMaster * master = GDL_DOCK_OBJECT_GET_MASTER (win->_dockbar->gobj());
  const gchar *nick_name = "main";
  GdlDockObject *dockItem  = gdl_dock_master_get_object(master, nick_name);
  gtk_widget_set_name(GTK_WIDGET(dockItem), "welcome");

  GList *children = gtk_container_get_children(GTK_CONTAINER(dockItem));
  gtk_container_remove(GTK_CONTAINER(dockItem), GTK_WIDGET(g_list_first(children)->data));

  GtkWidget *foo = viewWelcome()->gobj();
  gtk_container_add(GTK_CONTAINER(dockItem), foo);
  gtk_widget_show_all(foo);


  std::string filename("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/trunk/share/ganash/ui/layout-void.xml");
  //std::string filename("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/trunk/share/ganash/ui/layout-main-tools.xml");
  //std::string filename("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/trunk/src/application/plugin/welcome/layout.xml");
  //std::string filename("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/trunk/share/ganash/ui/layout-welcome.xml");
  //filename = std::string("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/trunk/share/ganash/ui/layout.xml");
  std::cout << "ui dir =" << filename.c_str() << std::endl;

  win->set_layout(filename);
  */

  //GdlDockMaster *master  = GDL_DOCK_MASTER (gdl_dock_object_get_master (GDL_DOCK_OBJECT (win->_dockbar->gobj())));

  Gtk::Widget *welcome = viewWelcome();
  GtkWidget * dockItemWelcome = gdl_dock_frame_new("welcome", "", GDL_DOCK_ITEM_BEH_NO_GRIP);
  gtk_widget_set_name(GTK_WIDGET(dockItemWelcome), "welcome");
  gtk_container_add(GTK_CONTAINER(dockItemWelcome), welcome->gobj());
  gdl_dock_add_item(GDL_DOCK(win->_dockbar->gobj()), GDL_DOCK_ITEM(dockItemWelcome), GDL_DOCK_BOTTOM);
  welcome->show_all();


  std::string filename("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/trunk/src/application/plugin/welcome/layout.xml");
  win->set_layout(filename);

	std::cout << "Ganash::Plugin::Welcome::init()" << std::endl;

	//g_usleep(5*1000*1000);
	// http://doc.qt.digia.com/qtcreator-extending/first-plugin.html


/*
Glib::RefPtr<Gtk::Settings> settings = Gtk::Settings::get_default();
Glib::PropertyProxy<Glib::ustring> theme_name = settings->property_gtk_theme_name();
theme_name.get_name();
g_print ("theme name = %s\n", theme_name.get_name());
Glib::PropertyProxy<Glib::ustring>::PropertyType type = theme_name.get_value();
g_print ("theme name = %s\n", type.c_str());


        g_print ("theme name = %s\n", Gtk::Settings::get_default()->property_gtk_theme_name().get_value().c_str());
*/

/*
g_object_set (gtk_settings_get_default (),
              "gtk-theme-name", "Industrial",
              "gtk-font-name", "Sans 10",
              NULL);

gchar *theme_name;
g_object_get(G_OBJECT(gtk_settings_get_default()), "gtk-theme-name", &theme_name, NULL);
g_print ("theme name = %s\n", theme_name);
*/


	return true;
}

void Ganash::Plugin::Welcome::on_menu_file_new_baz()
{
   std::cout << "A <File>New>Baz> menu item was selected." << std::endl;
}

Ganash::Extension::PluginAbstract * getInstance(void)
{
  Ganash::Extension::PluginAbstract *plugin = new Ganash::Plugin::Welcome();
  return plugin;
}

// gtk-theme-name
// Settings
Gtk::Widget * Ganash::Plugin::Welcome::viewWelcome()
{
  GtkCssProvider *provider;
  GdkDisplay *display;
  GdkScreen *screen;

  GtkWidget *main;

  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  gsize bytes_written, bytes_read;

  // PACKAGE_IMG_DIR
  const gchar* home = "/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/trunk/share/custom_gtk.css";
  //const gchar* home = "/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/thread/share/ganash/themes/Default/gtkrc";

  GError *error = 0;
  gtk_css_provider_load_from_path (provider,
                                      g_filename_to_utf8(home, strlen(home), &bytes_read, &bytes_written, &error),
                                      NULL);
  g_object_unref (provider);

  GtkWidget *hbox_wrapper;
  GtkWidget *vbox_main;
  GtkWidget *hbox;
  GtkWidget *vbox;
  GtkWidget *button_box;
  GtkWidget *bg_logo;
  GtkWidget *title;
  GtkWidget *hrule;
  GtkWidget *button;
  GtkWidget *description;
  hbox_wrapper= gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  vbox_main   = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  hbox        = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 30);
  button_box  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  vbox        = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  title       = gtk_label_new("Welcome");
  hrule       = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  button      = gtk_button_new_with_label("Getting start >>");
  description = gtk_label_new("Inkscape est un puissant environnement de création graphique,\n"
                              "d'animations et de contenus multimédias.\n"
                              "Using the W3C standard Scalable Vector Graphics (SVG) file format.\n"
                              "Using the W3C standard Scalable Vector Graphics (SVG) file format.\n"
                              "Using the W3C standard."
                              );

  bg_logo     = gtk_image_new_from_file("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/trunk/share/ganash/pixmap/bg_logo.png");

  gtk_widget_set_name(title, "welcome_title");
  gtk_widget_set_name(description, "welcome_description");
  gtk_widget_set_size_request(title, -1, 60);
  gtk_widget_set_size_request(hrule, -1, 30);

  // "Inkscape is an intuitive, modern cross platform IDE"

  //gtk_label_set_line_wrap( GTK_LABEL( description ), TRUE );
  //gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_LEFT);
  //gtk_widget_set_hexpand(button, FALSE);
  //GtkWidget *recent_file = gtk_label_new("Open a recent file");
  //Gtk::Button *btn = new Gtk::Button(Gtk::StockID(Ganash::Ui::Stock::SELECT));
  //Gtk::Button *btn = new Gtk::Button(Gtk::StockID(Ganash::Ui::Stock::SELECT));
  //GtkWidget *recent_file = GTK_WIDGET(btn->gobj());
  GtkWidget *recent_file = gtk_button_new_from_stock("ganash-select");
/*
#welcome {
        background-image: -gtk-gradient (linear, center top, center bottom, from(#FFFFFF), to(#E0E0E0));
}
#welcome_description {
	color: #808080;
	font: Sans 8;
}
#welcome_title {
	color: #707070;
	font-weight: bold;
	font: Sans 16;
}
*/
  Gtk::Button *btn = Glib::wrap(GTK_BUTTON(button));
  btn->signal_clicked().connect(sigc::mem_fun(*this, &Ganash::Plugin::Welcome::getting_start));


  gtk_box_pack_end(GTK_BOX(button_box), button, FALSE, TRUE, 0);

  gtk_container_add(GTK_CONTAINER(vbox), title);
  gtk_container_add(GTK_CONTAINER(vbox), description);
  gtk_container_add(GTK_CONTAINER(vbox), hrule);
  gtk_container_add(GTK_CONTAINER(vbox), button_box);

  gtk_box_pack_start(GTK_BOX(hbox), bg_logo, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, 0);

  gtk_box_pack_start(GTK_BOX(vbox_main), hbox, FALSE, FALSE, 30);
  gtk_box_pack_start(GTK_BOX(vbox_main), GTK_WIDGET(recent_file), TRUE, TRUE, 0);

  gtk_box_pack_start(GTK_BOX(hbox_wrapper), vbox_main, TRUE, FALSE, 10);

  return Glib::wrap(hbox_wrapper);
}

void Ganash::Plugin::Welcome::getting_start()
{
  Ganash::Application *app = Ganash::Application::instance();
  Ganash::Extension::PluginAbstract *plugin = app->m_bootstrap->pluginManager->getPluginByClassName("org.ganash.plugin.InkWave");
  plugin->setup();
}
