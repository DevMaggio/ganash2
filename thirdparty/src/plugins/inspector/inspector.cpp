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

#include "inspector.h"
#include "application.h"
#include "ui/action-manager.h"
#include "ui/application-window.h"
#include "ui/stock.h"
#include "display/shape.h"
#include "motion/property.h"
#include "motion/animator.h"
#include "motion/state.h"
#include "widget/stage.h"
//#include "widget/shape.h"


#include "gdl/gdl-dock.h"
#include "gdl/gdl-dock-frame.h"
#include "gdl/gdl-dock-item.h"
#include "gdl/gdl-dock-object.h"
#include "gdl/gdl-dock-master.h"
#include "gdl/gdl-dock-layout.h"
#include "gdl/gdl-dock-item-grip.h"


#include <gtkmm.h>

#include <iostream>

Ganash::Plugin::Inspector::Inspector() :
  Ganash::Extension::PluginAbstract(),
  m_is_setup(false)
{
  m_name = std::string("org.ganash.plugin.Inspector");
  g_print("new Ganash::Plugin::Inspector()\n");

}

Ganash::Plugin::Inspector::~Inspector()
{
}

bool Ganash::Plugin::Inspector::init()
{

  Ganash::Ui::ActionManager *actionManager = Ganash::Ui::ActionManager::instance();
  Glib::RefPtr<Gtk::Action> actionInspector = Gtk::Action::create("DisplayWorkbenchInspector", Gtk::Stock::NEW, "Inspector", "Display Inspector workbench");

  Glib::ustring ui_info_plugin =
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='DisplayMenu'>"
        "     <placeholder name='DisplayHolder'>"
        "      <menu action='DisplayWorkbench'>"
        "        <menuitem action='DisplayWorkbenchInspector'/>"
        "      </menu>"
        "     </placeholder>"
        "    </menu>"
        "  </menubar>"
        "</ui>";

  actionManager->m_refActionGroup->add(actionInspector, sigc::mem_fun(*this, &Ganash::Plugin::Inspector::setup));

  actionManager->m_refUIManager->add_ui_from_string(ui_info_plugin);

  g_print("Ganash::Plugin::Inspector::init()\n");
  return true;
}


void Ganash::Plugin::Inspector::setup()
{
   std::cout << "<Display>Workbench>Inspector>" << std::endl;
   Ganash::ApplicationWindow *win = Ganash::Application::get_main_window();

   if(!m_is_setup)
     {
       setupUi();
     }

   std::string filename("/home/ganash/Workspace/Gtk3/projects/ganash/thread/src/plugins/inspector/layout.xml");
   win->set_layout(filename);

}

WebKitWebView *
Ganash::Plugin::Inspector::setupInspector(WebKitWebInspector *inspector,
                            WebKitWebView *webview, void *data)
{
    /*
    GtkWidget *win;
    GtkWidget *view;
    printf("create_gtk_window_around_it\n");
    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_show_all(win);
    gtk_window_set_title(GTK_WINDOW(win), "Inspector");
    gtk_window_set_default_size(GTK_WINDOW(win), 600, 400);
    view = webkit_web_view_new();
    gtk_container_add(GTK_CONTAINER(win), view);

    gtk_widget_show(win);
    return WEBKIT_WEB_VIEW(view);
    */

    Ganash::ApplicationWindow *win = Ganash::Application::get_main_window();
    GtkWidget *dockbar   = win->_dockbar->gobj();

    GdlDockMaster *master  = GDL_DOCK_MASTER (gdl_dock_object_get_master (GDL_DOCK_OBJECT (dockbar)));
    //GdlDockMaster * master = GDL_DOCK_OBJECT_GET_MASTER (win->_dockbar->gobj());
    const gchar *nick_name = "bottom";
    GdlDockObject *dockItem  = gdl_dock_master_get_object(master, nick_name);

    GList *children = gtk_container_get_children(GTK_CONTAINER(dockItem));
    gtk_container_remove(GTK_CONTAINER(dockItem), GTK_WIDGET(g_list_first(children)->data));


    GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 0);
    /* the policy is one of GTK_POLICY AUTOMATIC, or GTK_POLICY_ALWAYS.
     * GTK_POLICY_AUTOMATIC will automatically decide whether you need
     * scrollbars, whereas GTK_POLICY_ALWAYS will always leave the scrollbars
     * there.  The first one is the horizontal scrollbar, the second,
     * the vertical. */
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    GtkWidget *view = webkit_web_view_new();
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), view);
    gtk_container_add(GTK_CONTAINER(dockItem), scrolled_window);

    gtk_widget_show_all(scrolled_window);
    return WEBKIT_WEB_VIEW(view);

}

void Ganash::Plugin::Inspector::setupUi()
{
  Ganash::ApplicationWindow *win = Ganash::Application::get_main_window();

  GError *error = NULL;
  GdkPixbuf *pixbuf;
  GtkWidget *dockbar   = win->_dockbar->gobj();

  // ----

  Gtk::Toolbar *tools = new Gtk::Toolbar();
  //tools->get_style_context()->add_class();
  tools->set_property("orientation", Gtk::ORIENTATION_VERTICAL);
  tools->set_property("toolbar-style", Gtk::TOOLBAR_ICONS);
  //tools->set_property("icon-size", Gtk::ICON_SIZE_SMALL_TOOLBAR);
  tools->set_property("icon-size", Gtk::ICON_SIZE_LARGE_TOOLBAR);
  Gtk::ToolButton *cursor5_tool = new Gtk::ToolButton(Gtk::StockID(Ganash::Ui::Stock::SELECT));
  Gtk::ToolButton *cursor6_tool = new Gtk::ToolButton(Gtk::StockID(Ganash::Ui::Stock::TRANSFORM));
  tools->insert(*cursor5_tool, 0, sigc::mem_fun(*this, &Ganash::Plugin::Inspector::on_cursor));
  tools->insert(*cursor6_tool, 0, sigc::mem_fun(*this, &Ganash::Plugin::Inspector::on_cursor));


  GdlDockLayout * layout = gdl_dock_layout_new(G_OBJECT(dockbar));
  GdlDockMaster * master = GDL_DOCK_MASTER (gdl_dock_object_get_master (GDL_DOCK_OBJECT (dockbar)));

  error = NULL;
  pixbuf = gdk_pixbuf_new_from_file("/home/sergio/Images/inkscape.logo.png", &error);
  GtkWidget * dockItemTools = gdl_dock_item_new_with_pixbuf_icon("tools", "", pixbuf, GDL_DOCK_ITEM_BEH_NORMAL);
  gtk_container_add(GTK_CONTAINER(dockItemTools), GTK_WIDGET(tools->gobj()));

  GtkWidget *webView = webkit_web_view_new();
  webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webView), "file:///home/ganash/Images/clouds.svg");
  g_object_set(G_OBJECT(webkit_web_view_get_settings(WEBKIT_WEB_VIEW(webView))), "enable-developer-extras", TRUE, NULL);
  WebKitWebInspector *inspector = webkit_web_view_get_inspector (WEBKIT_WEB_VIEW(webView));
  g_signal_connect (G_OBJECT (inspector), "inspect-web-view", G_CALLBACK(&Ganash::Plugin::Inspector::setupInspector), NULL);

  /*GtkWidget * dockItemDrawing = gdl_dock_frame_new("main", "", GDL_DOCK_ITEM_BEH_NO_GRIP);*/
  /*gtk_container_add(GTK_CONTAINER(dockItemDrawing), GTK_WIDGET(webView));*/
  GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
  gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), webView);

  GtkWidget * dockItemDrawing = gdl_dock_frame_new("main", "", GDL_DOCK_ITEM_BEH_NO_GRIP);
  gtk_container_add(GTK_CONTAINER(dockItemDrawing), scrolled_window/*gtk_label_new("properties")*/);

  GtkWidget *expander = gtk_expander_new("Computed style");
  gtk_container_add(GTK_CONTAINER(expander), gtk_label_new("properties"));
  error = NULL;
  pixbuf = gdk_pixbuf_new_from_file("/home/sergio/Images/inkscape.logo.png", &error);
  GtkWidget * dockItemProperties = gdl_dock_item_new_with_pixbuf_icon("properties", "", pixbuf, GDL_DOCK_ITEM_BEH_NORMAL);
  //GtkWidget * dockItemProperties = gdl_dock_item_new("properties", "", GDL_DOCK_ITEM_BEH_NORMAL);
  gtk_container_add(GTK_CONTAINER(dockItemProperties), expander);

  GtkWidget * dockItemBottom = gdl_dock_item_new("bottom", "", GDL_DOCK_ITEM_BEH_NO_GRIP);
  gtk_container_add(GTK_CONTAINER(dockItemBottom), gtk_label_new("bottom"));

  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemTools), GDL_DOCK_LEFT);
  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemDrawing), GDL_DOCK_RIGHT);
  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemProperties), GDL_DOCK_RIGHT);
  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemBottom), GDL_DOCK_RIGHT);

  gtk_widget_show_all(dockItemTools);
  gtk_widget_show_all(dockItemDrawing);
  gtk_widget_show_all(dockItemProperties);
  gtk_widget_show_all(dockItemBottom);

  m_is_setup = true;
}

void Ganash::Plugin::Inspector::on_cursor()
{
  g_print("cursor clicked");
}

/*
Gtk::Widget * Ganash::ApplicationWindow::setupTool()
{
  // Ganash::Ui::ActionManager::instance();
}
*/

Ganash::Extension::PluginAbstract * getInstance(void)
{
  Ganash::Extension::PluginAbstract *plugin = new Ganash::Plugin::Inspector();
  return plugin;
}
