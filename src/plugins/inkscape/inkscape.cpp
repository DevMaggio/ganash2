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

#include "inkscape.h"
#include "application.h"
#include "ui/action-manager.h"
#include "ui/application-window.h"


#include "gdl/gdl-dock.h"
#include "gdl/gdl-dock-frame.h"
#include "gdl/gdl-dock-item.h"
#include "gdl/gdl-dock-object.h"
#include "gdl/gdl-dock-master.h"
#include "gdl/gdl-dock-layout.h"
#include "gdl/gdl-dock-item-grip.h"


#include <gtkmm.h>

#include <iostream>

Ganash::Plugin::Inkscape::Inkscape() :
  Ganash::Extension::PluginAbstract(),
  m_is_setup(false)
{
  m_name = std::string("org.ganash.plugin.InkScape");
  g_print("new Ganash::Plugin::Inkscape()\n");
}

Ganash::Plugin::Inkscape::~Inkscape()
{
}

bool Ganash::Plugin::Inkscape::init()
{

  Ganash::Ui::ActionManager *actionManager = Ganash::Ui::ActionManager::instance();
  Glib::RefPtr<Gtk::Action> actionIllustration = Gtk::Action::create("DisplayWorkbenchIllustration", Gtk::Stock::NEW, "Illustration", "Display illustration workbench");

  Glib::ustring ui_info_plugin =
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='DisplayMenu'>"
        "     <placeholder name='DisplayHolder'>"
        "      <menu action='DisplayWorkbench'>"
        "        <menuitem action='DisplayWorkbenchIllustration'/>"
        "      </menu>"
        "     </placeholder>"
        "    </menu>"
        "  </menubar>"
        "</ui>";


  actionManager->m_refActionGroup->add(actionIllustration, sigc::mem_fun(*this, &Ganash::Plugin::Inkscape::setup));

  actionManager->m_refUIManager->add_ui_from_string(ui_info_plugin);

  g_print("Ganash::Plugin::Inkscape::init()\n");
  return true;
}


void Ganash::Plugin::Inkscape::setup()
{
   std::cout << "A <File>New>Baz> menu item was selected." << std::endl;
   Ganash::ApplicationWindow *win = Ganash::Application::get_main_window();

   if(!m_is_setup)
     {
       setupUi();
     }

   std::string filename("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/thread/share/ganash/ui/layout.xml");
   win->set_layout(filename);

}

void Ganash::Plugin::Inkscape::setupUi()
{
  Ganash::ApplicationWindow *win = Ganash::Application::get_main_window();

  GError *error = NULL;
  GdkPixbuf *pixbuf;
  GtkWidget *dockbar   = win->_dockbar->gobj();

  GdlDockLayout * layout = gdl_dock_layout_new(G_OBJECT(dockbar));
  GdlDockMaster * master = GDL_DOCK_MASTER (gdl_dock_object_get_master (GDL_DOCK_OBJECT (dockbar)));

/*
  pixbuf = gdk_pixbuf_new_from_file("/home/sergio/Images/inkscape.logo.png", &error);
  GtkWidget * dockItemTools = gdl_dock_item_new_with_pixbuf_icon("tools", "", pixbuf, GDL_DOCK_ITEM_BEH_NORMAL);
  gtk_container_add(GTK_CONTAINER(dockItemTools), gtk_label_new("toolbox?"));
  GtkWidget * dockItemDrawing = gdl_dock_frame_new("main", "", GDL_DOCK_ITEM_BEH_NO_GRIP);
  gtk_container_add(GTK_CONTAINER(dockItemDrawing), gtk_label_new("Loading..."));

  GtkWidget * dockItemBottom = gdl_dock_item_new("bottom", "", GDL_DOCK_ITEM_BEH_NO_GRIP);
  gtk_container_add(GTK_CONTAINER(dockItemBottom), gtk_label_new("bottom"));

  //GtkWidget * dockItemPropertiesA = gdl_dock_item_new_with_stock("properties_a", "", GTK_STOCK_EXECUTE, GDL_DOCK_ITEM_BEH_NORMAL);
  error = NULL;
  pixbuf = gdk_pixbuf_new_from_file("/home/sergio/Images/icon_layers.png", &error);
  GtkWidget * dockItemPropertiesA = gdl_dock_item_new_with_pixbuf_icon("properties_a", "Fill & Stroke", pixbuf, GDL_DOCK_ITEM_BEH_NORMAL);
  //gdl_dock_item_grip_hide_handle(GDL_DOCK_ITEM_GRIP(gdl_dock_item_get_grip(GDL_DOCK_ITEM(dockItemPropertiesA))));
  gtk_container_add(GTK_CONTAINER(dockItemPropertiesA), GTK_WIDGET(gtk_label_new("Property")));

  GtkWidget * dockItemPropertiesB = gdl_dock_item_new_with_stock("properties_b", "", GTK_STOCK_EXECUTE, GDL_DOCK_ITEM_BEH_NORMAL);
  gtk_container_add(GTK_CONTAINER(dockItemPropertiesB), GTK_WIDGET(gtk_label_new("H")));

  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemTools), GDL_DOCK_LEFT);
  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemDrawing), GDL_DOCK_RIGHT);
  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemPropertiesA), GDL_DOCK_RIGHT);
  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemPropertiesB), GDL_DOCK_RIGHT);
  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemBottom), GDL_DOCK_BOTTOM);

  gdl_dock_item_dock_to(GDL_DOCK_ITEM(dockItemPropertiesA), GDL_DOCK_ITEM(dockItemPropertiesB), GDL_DOCK_BOTTOM, 0);

  gtk_widget_show_all(dockItemTools);
  gtk_widget_show_all(dockItemDrawing);
  gtk_widget_show_all(dockItemPropertiesA);
  gtk_widget_show_all(dockItemPropertiesB);
  gtk_widget_show_all(dockItemBottom);
*/

  m_is_setup = true;
}

Ganash::Extension::PluginAbstract * getInstance(void)
{
	Ganash::Extension::PluginAbstract *plugin = new Ganash::Plugin::Inkscape();
	return plugin;
}
