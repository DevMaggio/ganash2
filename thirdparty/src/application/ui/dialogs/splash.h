//$Id: splash.h 2 2003-01-21 13:41:59Z maggio $ -*- c++ -*-

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

#ifndef GANASH_UI_DIALOG_SPLASH_H
#define GANASH_UI_DIALOG_SPLASH_H

#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/button.h>
#include <glibmm.h>

namespace Ganash {
namespace Ui {
namespace Dialog {

class Splash : public Gtk::Window
{
public:
  Splash();
  virtual ~Splash();
  void update(const std::string label1, const std::string label2, gdouble percentage);
  void shutdown();

  Glib::Dispatcher signal_progress;

  //void on_shutdown_complete();
  //signal accessor:
  typedef sigc::signal<void> type_signal_shutdown_complete;
  Ganash::Ui::Dialog::Splash::type_signal_shutdown_complete signal_shutdown_complete();

protected:
  gdouble    _opacity;
  Gtk::Image _background;
  Gtk::Label _label1;
  Gtk::Label _label2;
  Gtk::Button _cancel;
  Gtk::ProgressBar _progress;

  bool my_timeout_function();
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);

  Ganash::Ui::Dialog::Splash::type_signal_shutdown_complete m_signal_shutdown_complete;
private:
};

} // namespace Dialog
} // namespace Ui
} // namespace Ganash


#endif // GANASH_UI_DIALOG_SPLASH_H


