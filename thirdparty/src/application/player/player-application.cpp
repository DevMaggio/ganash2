#include "player-application.h"
#include "player-window.h"

Ganash::PlayerApplication::PlayerApplication(const Glib::ustring & application_id, Gio::ApplicationFlags flags) :
    Gtk::Application(application_id, flags)
{
}

Glib::RefPtr<Ganash::PlayerApplication> Ganash::PlayerApplication::create()
{
  return Glib::RefPtr<Ganash::PlayerApplication>( new Ganash::PlayerApplication("org.gnome.ganash", Gio::APPLICATION_HANDLES_COMMAND_LINE|Gio::APPLICATION_HANDLES_OPEN) );
}

int Ganash::PlayerApplication::on_command_line(const Glib::RefPtr<Gio::ApplicationCommandLine>&command_line)
{
    int argc;
    char **argv = command_line->get_arguments(argc);

    activate();
    return 0;
}

void Ganash::PlayerApplication::on_activate()
{
  g_print("PlayerApplication::on_activate\n");

  Ganash::PlayerWindow *window = new Ganash::PlayerWindow();
  add_window(*window);
  window->set_default_size(900, 600);
  window->set_position(Gtk::WIN_POS_CENTER);
  window->show_all();
}
