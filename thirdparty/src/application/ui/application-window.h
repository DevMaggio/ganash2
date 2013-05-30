
#ifndef GANASH_APPLICATIONWINDOW_H
#define GANASH_APPLICATIONWINDOW_H

#include <gtkmm/applicationwindow.h>

namespace Ganash {
  
  class ApplicationWindow : public Gtk::ApplicationWindow
  {
  public:
    ApplicationWindow();
    ~ApplicationWindow();

    void set_layout(std::string filename);

    Gtk::Widget *_dockbar;
    Gtk::Widget *_layout;
  protected:
    Gtk::Widget *_menubar;
    Gtk::Widget *_toolbar;
    Gtk::Widget *_statusbar;
    Gtk::Widget *setupUi();
    Gtk::Widget *setupMenu();
    Gtk::Widget *setupTool();
    Gtk::Widget *setupDock();

    void small_theme();
    void normal_theme();
    void large_theme();

    void foo();
    void baz();

    GtkWidget * dockItemTools;
    GtkWidget * dockItemDrawing;
    GtkWidget * dockItemBottom;
    GtkWidget * dockItemPropertiesA;
    GtkWidget * dockItemPropertiesB;

  };
  
} // namespace Ganash

#endif // GANASH_APPLICATIONWINDOW_H
