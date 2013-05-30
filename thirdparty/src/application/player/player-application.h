#ifndef GANASH_PLAYERAPPLICATION_H
#define GANASH_PLAYERAPPLICATION_H

#include "player/player-application.h"

#include <gtkmm/application.h>

namespace Ganash {

class PlayerApplication : public Gtk::Application
{
public:
    PlayerApplication(const Glib::ustring & application_id, Gio::ApplicationFlags flags);
    static Glib::RefPtr<Ganash::PlayerApplication> create();
    int on_command_line(const Glib::RefPtr<Gio::ApplicationCommandLine>&command_line);
protected:
    void on_activate();
};

} // namespace Ganash

#endif // GANASH_PLAYERAPPLICATION_H
