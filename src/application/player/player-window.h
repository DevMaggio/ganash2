
#ifndef GANASH_PLAYERWINDOW_H
#define GANASH_PLAYERWINDOW_H

#include <gtkmm/applicationwindow.h>
#include <gtkmm/box.h>

namespace Ganash {
  
  class PlayerWindow : public Gtk::ApplicationWindow
  {
  public:
    PlayerWindow();
    ~PlayerWindow();
    void setup();
    void on_my_clicked();
  protected:
    Gtk::Box _box;
  };
  
} // namespace Ganash

#endif // GANASH_PLAYERWINDOW_H
