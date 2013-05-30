
#include "action-manager.h"
#include "application-window.h"
#include "ui/icon-factory.h"

#include "core/dock-manager.h"
#include "core/action-manager.h"
#include "core/action.h"

#include "ui/stock.h"

#include "gdl/gdl-dock.h"
#include "gdl/gdl-dock-frame.h"
#include "gdl/gdl-dock-item.h"
#include "gdl/gdl-dock-object.h"
#include "gdl/gdl-dock-master.h"
#include "gdl/gdl-dock-layout.h"
#include "gdl/gdl-dock-item-grip.h"

#include <gtkmm/stock.h>
#include <gtkmm/settings.h>

Ganash::ApplicationWindow::ApplicationWindow() :
  Gtk::ApplicationWindow()
{
  set_title("New Document - Ganash");
  set_default_size(200, 200);

  Glib::RefPtr<Ganash::Ui::IconFactory> iconFactory = Ganash::Ui::IconFactory::create();
  iconFactory->add_default();


  add(*setupUi());
}

Ganash::ApplicationWindow::~ApplicationWindow()
{

}

Gtk::Widget * Ganash::ApplicationWindow::setupUi()
{
  GtkWidget *vbox;
  GtkWidget *menubar;
  GtkWidget *toolbar;
  GtkWidget *dockbar;
  GtkWidget *statusbar;

  vbox      = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  menubar   = setupMenu()->gobj();//gtk_menu_bar_new();
  toolbar   = setupTool()->gobj();//gtk_toolbar_new();
  dockbar   = setupDock()->gobj();
  statusbar = gtk_statusbar_new();

  gtk_widget_set_vexpand(vbox, TRUE);
  gtk_widget_set_vexpand(dockbar, TRUE);
  //gtk_widget_set_vexpand(toolbar, FALSE);

  // ----------------

  Gtk::Toolbar *tools = new Gtk::Toolbar();
  //tools->set_property("orientation", Gtk::ORIENTATION_VERTICAL);
  //tools->set_property("toolbar-style", Gtk::TOOLBAR_ICONS);
  //tools->set_property("icon-size", Gtk::ICON_SIZE_SMALL_TOOLBAR);
  //tools->set_property("icon-size", Gtk::ICON_SIZE_LARGE_TOOLBAR);

  Gtk::ToolButton *cursor5_tool = new Gtk::ToolButton(Gtk::StockID(Ganash::Ui::Stock::SELECT));
  Gtk::ToolButton *cursor6_tool = new Gtk::ToolButton(Gtk::StockID(Ganash::Ui::Stock::TRANSFORM));
  tools->insert(*cursor5_tool, 0);
  tools->insert(*cursor6_tool, 1);
  // ----


  gtk_container_add(GTK_CONTAINER(vbox), menubar);
  gtk_container_add(GTK_CONTAINER(vbox), toolbar);
  gtk_container_add(GTK_CONTAINER(vbox), GTK_WIDGET(tools->gobj()));
  gtk_container_add(GTK_CONTAINER(vbox), dockbar);
  //gtk_container_add(GTK_CONTAINER(vbox), statusbar);

  _menubar   = Glib::wrap(menubar);
  _toolbar   = Glib::wrap(toolbar);
  _dockbar   = Glib::wrap(dockbar);
  _statusbar = Glib::wrap(statusbar);
  return Glib::wrap(vbox);
}

Gtk::Widget * Ganash::ApplicationWindow::setupMenu()
{
    Glib::RefPtr<Gtk::Action> action_file_new_file = Gtk::Action::create("file-new-file", Gtk::StockID(Gtk::Stock::NEW), "_New", "New empty file");
    Glib::RefPtr<Gtk::Action> action_file_quit = Gtk::Action::create("file-quit", Gtk::StockID(Gtk::Stock::QUIT), "_Quit", "Quit the application");

    Ganash::Core::ActionManager *am = Ganash::Core::ActionManager::getInstance();
    am->menubar("MainMenu")->menu("File")->menu("New")->menuitem("File")->setAction(action_file_new_file, "group");
    am->menubar("MainMenu")->menu("File")->menuitem("Quit")->setAction(action_file_quit, "group");
    //am->menubar("MainMenu")->menu("Help")->menuitem("About")->setAction(action_file_quit, "group");
    // ActionManager::get("/menubar[name=MainMenu]/menu[name=File]/menuitem[name=Quit]")->setAction(action, "group");
    // ActionManager::menubar("/MainMenu/File/Quit")->setAction(action, "group", sigc);
    Ganash::Core::DockManager *dm = Ganash::Core::DockManager::getInstance();

    char* buffer = am->toString();
    g_print("ActionManager {\n%s\n}\n", buffer);
    g_free(buffer);


  Ganash::Ui::ActionManager *instance = Ganash::Ui::ActionManager::instance();

  Glib::ustring ui_info =
        "<ui>"
          "<menubar name='MenuBar'>"
            "<menu action='FileMenu'>"
              "<menu action='FileNew'>"
              "</menu>"
              "<placeholder name='FileHolder' />"
              "<separator/>"
              "<menuitem action='FileQuit'/>"
            "</menu>"
            "<menu action='ViewMenu'>"
              "<menu action='ViewThemes'>"
                "<menuitem action='SmallViewThemes'/>"
                "<menuitem action='NormalViewThemes'/>"
                "<menuitem action='LargeViewThemes'/>"
              "</menu>"
            "</menu>"
            "<menu action='EditMenu'>"
              "<separator/>"
              "<menuitem action='EditPreferences'/>"
            "</menu>"
            "<menu action='DisplayMenu'>"
              "<placeholder name='DisplayHolder' />"
              "<menu action='DisplayWorkbench' />"
              "<separator/>"
              "<menuitem action='DisplayWelcome'/>"
            "</menu>"
            "<menu action='HelpMenu'>"
              "<menuitem action='HelpAbout'/>"
            "</menu>"
          "</menubar>"
        "</ui>"
      ;
  //Create actions for menus and toolbars:

  //File menu:
  //instance->registerAction(Gtk::Action::create("FileMenu", "File"));
  instance->m_refActionGroup->add(Gtk::Action::create("FileMenu", "File"));

  //Sub-menu.
  instance->m_refActionGroup->add(Gtk::Action::create("FileNew", Gtk::Stock::NEW),
          sigc::mem_fun(*this, &Ganash::ApplicationWindow::baz));
  instance->m_refActionGroup->add(Gtk::Action::create("FileQuit", Gtk::Stock::QUIT),
          sigc::mem_fun(*this, &Ganash::ApplicationWindow::foo));

  //Edit menu:
  instance->m_refActionGroup->add(Gtk::Action::create("EditMenu", "Edit"));
  instance->m_refActionGroup->add(Gtk::Action::create("EditPreferences", Gtk::Stock::PROPERTIES));

  //View menu:
  instance->m_refActionGroup->add(Gtk::Action::create("ViewMenu", "View"));
  instance->m_refActionGroup->add(Gtk::Action::create("ViewThemes", "Themes"));
  instance->m_refActionGroup->add(Gtk::Action::create("SmallViewThemes", "Small"),
                                  sigc::mem_fun(*this, &Ganash::ApplicationWindow::small_theme));
  instance->m_refActionGroup->add(Gtk::Action::create("NormalViewThemes", "Normal"),
                                  sigc::mem_fun(*this, &Ganash::ApplicationWindow::normal_theme));
  instance->m_refActionGroup->add(Gtk::Action::create("LargeViewThemes", "Large"),
                                  sigc::mem_fun(*this, &Ganash::ApplicationWindow::large_theme));

  //Display menu:
  instance->m_refActionGroup->add(Gtk::Action::create("DisplayMenu", "Window"));
  instance->m_refActionGroup->add(Gtk::Action::create("DisplayWelcome", Gtk::Stock::FULLSCREEN));

  instance->m_refActionGroup->add(Gtk::Action::create("DisplayWorkbench", "Workbench"));

  //Help menu:
  instance->m_refActionGroup->add(Gtk::Action::create("HelpMenu", "Help"));
  instance->m_refActionGroup->add(Gtk::Action::create("HelpAbout", Gtk::Stock::ABOUT));

  instance->m_refUIManager->add_ui_from_string(ui_info);


  return instance->m_refUIManager->get_widget("/MenuBar");
}

void Ganash::ApplicationWindow::small_theme()
{

    g_print("theme name = %s\n", Gtk::Settings::get_default()->property_gtk_theme_name().get_value().c_str());
    g_print("Change theme small\n");

// gtk-small-toolbar
// gtk-large-toolbar
// ICON_SIZE_SMALL_TOOLBAR
/*
    Glib::ustring theme_name_value("gtk-large-toolbar=16,16");
    Glib::Value<Glib::ustring> theme_name;
    theme_name.init(Glib::Value<Glib::ustring>::value_type());
    theme_name.set(theme_name_value);
    Gtk::Settings::get_default()->set_property_value("gtk-icon-sizes", theme_name);
*/


    /*
    Glib::ustring theme_name_value("Radiance");
    Glib::Value<Glib::ustring> theme_name;
    theme_name.init(Glib::Value<Glib::ustring>::value_type());
    theme_name.set(theme_name_value);

    Gtk::Settings::get_default()->set_property_value("gtk-theme-name", theme_name);
    */

    /*
    const gchar* file = "/home/ganash/Workspace/Gtk3/projects/ganash/thread/share/ganash/themes/Default/gtkrc";
    gtk_rc_parse(file);
    gtk_rc_add_default_file(file);
    gtk_rc_reparse_all();
*/

/*
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
    const gchar* home = "/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/trunk/share/test.css";
    //const gchar* home = "/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/thread/share/ganash/themes/Default/gtkrc";

    GError *error = 0;
    gtk_css_provider_load_from_path (provider,
                                        g_filename_to_utf8(home, strlen(home), &bytes_read, &bytes_written, &error),
                                        NULL);
    g_object_unref (provider);
    */
}

void Ganash::ApplicationWindow::normal_theme()
{
    Glib::ustring theme_name_value("gtk-large-toolbar=24,24");
    Glib::Value<Glib::ustring> theme_name;
    theme_name.init(Glib::Value<Glib::ustring>::value_type());
    theme_name.set(theme_name_value);

    Gtk::Settings::get_default()->set_property_value("gtk-icon-sizes", theme_name);
}

void Ganash::ApplicationWindow::large_theme()
{
    Glib::ustring theme_name_value("gtk-large-toolbar=32,32");
    Glib::Value<Glib::ustring> theme_name;
    theme_name.init(Glib::Value<Glib::ustring>::value_type());
    theme_name.set(theme_name_value);

    Gtk::Settings::get_default()->set_property_value("gtk-icon-sizes", theme_name);
}

// TODO ContainerManager
void Ganash::ApplicationWindow::baz()
{
  //std::string filename("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/trunk/share/ganash/ui/layout-main-tools.xml");
  std::string filename("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/trunk/share/ganash/ui/layout.xml");
  filename = std::string("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/trunk/src/application/plugin/welcome/layout.xml");
  //filename = std::string("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/trunk/share/ganash/ui/layout-welcome.xml");

  set_layout(filename);

}

void Ganash::ApplicationWindow::foo()
{
  // Ganash::Core::ContainerManager::remove_widget("main");
  // Ganash::Core::ContainerManager::add_widget(, "main");

  // Ganash::Core::ContainerManager::set_widget(, "main");
  // Ganash::Core::ContainerManager::get_widget("main");

  /*GdlDockMaster *master  = GDL_DOCK_MASTER (gdl_dock_object_get_master (GDL_DOCK_OBJECT (_dockbar->gobj())));
  const gchar *nick_name = "main";
  GdlDockObject *dockItem  = gdl_dock_master_get_object(master, nick_name);
  GList *children = gtk_container_get_children(GTK_CONTAINER(dockItem));
  gtk_container_remove(GTK_CONTAINER(dockItem), GTK_WIDGET(g_list_first(children)->data));

  GtkWidget *foo = gtk_label_new("Hello");
  gtk_widget_show(foo);
  gtk_container_add(GTK_CONTAINER(dockItem), foo);*/

  //GdlDockLayout * layout = gdl_dock_layout_new(GDL_DOCK(_dockbar->gobj()));
  //std::string filename("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/trunk/share/ganash/ui/layout-main-tools.xml");
  std::string filename("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/trunk/share/ganash/ui/layout.xml");

  set_layout(filename);

}

Gtk::Widget * Ganash::ApplicationWindow::setupTool()
{
  GtkWidget *toolbar;

  GtkToolItem *item_new;
  GtkToolItem *item_open;
  GtkToolItem *item_save;
  GtkToolItem *item_sep;
  GtkToolItem *item_exit;

  toolbar   = gtk_toolbar_new();

  gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
  //gtk_toolbar_set_icon_size (GTK_TOOLBAR (toolbar), GTK_ICON_SIZE_SMALL_TOOLBAR);
  GtkStyleContext *context;
  context = gtk_widget_get_style_context(toolbar);
  gtk_style_context_add_class(context, "primary-toolbar");

  gtk_container_set_border_width(GTK_CONTAINER(toolbar), 0);

  item_new = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item_new, -1);

  item_open = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item_open, -1);

  item_save = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item_save, -1);

  item_sep = gtk_separator_tool_item_new();
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item_sep, -1);

  item_exit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item_exit, -1);

  return Glib::wrap(toolbar);
}

Gtk::Widget * Ganash::ApplicationWindow::setupDock()
{
  GError *error = NULL;
  GdkPixbuf *pixbuf;

  GtkWidget *dockbar   = gdl_dock_new();
  /*
  GdlDockLayout * layout = gdl_dock_layout_new(G_OBJECT(dockbar));
  GdlDockMaster * master = GDL_DOCK_MASTER (gdl_dock_object_get_master (GDL_DOCK_OBJECT (dockbar)));
  //GdlDockMaster * master = GDL_DOCK_OBJECT_GET_MASTER(GDL_DOCK_OBJECT (dockbar));

  pixbuf = gdk_pixbuf_new_from_file("/home/sergio/Images/inkscape.logo.png", &error);
  dockItemTools = gdl_dock_item_new_with_pixbuf_icon("tools", "", pixbuf, GDL_DOCK_ITEM_BEH_NORMAL);
  gtk_container_add(GTK_CONTAINER(dockItemTools), gtk_label_new("toolbox?"));

  dockItemDrawing = gdl_dock_frame_new("main", "", GDL_DOCK_ITEM_BEH_NO_GRIP);
  gtk_container_add(GTK_CONTAINER(dockItemDrawing), gtk_label_new("Loading..."));

  //gtk_widget_set_name (GTK_WIDGET(dockItemDrawing), "welcome");
  //gtk_widget_set_name (GTK_WIDGET(dockItemDrawing), "main");

  dockItemBottom = gdl_dock_item_new("bottom", "", GDL_DOCK_ITEM_BEH_NO_GRIP);
  gtk_container_add(GTK_CONTAINER(dockItemBottom), gtk_label_new("bottom"));

  //GtkWidget * dockItemPropertiesA = gdl_dock_item_new_with_stock("properties_a", "", GTK_STOCK_EXECUTE, GDL_DOCK_ITEM_BEH_NORMAL);
  error = NULL;
  pixbuf = gdk_pixbuf_new_from_file("/home/sergio/Images/icon_layers.png", &error);
  dockItemPropertiesA = gdl_dock_item_new_with_pixbuf_icon("properties_a", "Fill & Stroke", pixbuf, GDL_DOCK_ITEM_BEH_NORMAL);
  //gdl_dock_item_grip_hide_handle(GDL_DOCK_ITEM_GRIP(gdl_dock_item_get_grip(GDL_DOCK_ITEM(dockItemPropertiesA))));
  gtk_container_add(GTK_CONTAINER(dockItemPropertiesA), GTK_WIDGET(gtk_label_new("Property")));

  dockItemPropertiesB = gdl_dock_item_new_with_stock("properties_b", "", GTK_STOCK_EXECUTE, GDL_DOCK_ITEM_BEH_NORMAL);
  gtk_container_add(GTK_CONTAINER(dockItemPropertiesB), GTK_WIDGET(gtk_label_new("H")));

  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemTools), GDL_DOCK_LEFT);
  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemDrawing), GDL_DOCK_RIGHT);
  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemPropertiesA), GDL_DOCK_RIGHT);
  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemPropertiesB), GDL_DOCK_RIGHT);
  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemBottom), GDL_DOCK_BOTTOM);

  gdl_dock_item_dock_to(GDL_DOCK_ITEM(dockItemPropertiesA), GDL_DOCK_ITEM(dockItemPropertiesB), GDL_DOCK_BOTTOM, 0);
*/

  _dockbar = Glib::wrap(dockbar);
  return _dockbar;
}

void Ganash::ApplicationWindow::set_layout(std::string filename)
{
  GdlDockLayout * layout = gdl_dock_layout_new(G_OBJECT(_dockbar->gobj()));

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

}
