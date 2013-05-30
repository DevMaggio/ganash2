
#ifndef GANASH_UI_ICONFACTORY_H
#define GANASH_UI_ICONFACTORY_H

#include <gtkmm/iconfactory.h>
#include <gtkmm/iconsource.h>

namespace Ganash {
  namespace Ui {

class IconFactory : public Gtk::IconFactory
{
public:
  ~IconFactory();
  static Glib::RefPtr<Ganash::Ui::IconFactory> create();

  const Gtk::IconSource create_source(std::string filename, Gtk::BuiltinIconSize size);
protected:
  IconFactory();
};

} // Ui
} // Ganash

#endif // GANASH_UI_ICONFACTORY_H
