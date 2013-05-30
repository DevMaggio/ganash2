//$Id: splash.cpp 2 2003-01-21 13:41:59Z maggio $ -*- c++ -*-

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

#include "splash.h"

#include <glibmm/miscutils.h>
#include <gtkmm/button.h>
#include <gtkmm/fixed.h>
#include <gdkmm/screen.h>
#include <glibmm/main.h>

Ganash::Ui::Dialog::Splash::Splash():
  Gtk::Window(Gtk::WINDOW_TOPLEVEL),
  _cancel("Annuler")
{
  Glib::RefPtr<Gdk::Screen> screen = get_screen();
  Glib::RefPtr<Gdk::Visual> visual = screen->get_rgba_visual();

  if (!visual)
    {
      visual = screen->get_system_visual();
    }

  gtk_widget_set_visual (GTK_WIDGET(this->gobj()), visual->gobj());




  set_name("splash");

  GtkCssProvider *provider;
  GdkDisplay *display;
  GdkScreen *screenX;

  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screenX = gdk_display_get_default_screen (display);

  gtk_style_context_add_provider_for_screen (screenX,
                                             GTK_STYLE_PROVIDER(provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
/*
  gtk_css_provider_load_from_data (GTK_CSS_PROVIDER (provider),
                                     " GtkWindow {\n"
                                     "   background-color: transparent;\n"
                                     "}\n", -1, NULL);
*/
  gtk_css_provider_load_from_data (GTK_CSS_PROVIDER (provider),
                                     " #splash {\n"
                                     "   background-color: transparent;\n"
                                     "}\n", -1, NULL);
  g_object_unref (provider);








  set_position(Gtk::WIN_POS_CENTER);
  set_app_paintable(true);
  set_decorated(false);
  set_keep_above(true);
  set_type_hint(Gdk::WINDOW_TYPE_HINT_SPLASHSCREEN);


  const std::string filename = Glib::build_filename(PACKAGE_IMG_DIR, "splash.png");

  _background.set(filename);
  const int width  = _background.get_width();
  const int height = _background.get_height();
  set_default_size(width, height);

  Gtk::Fixed *fixed_container = new Gtk::Fixed();
  _label1.set_text("Initializing...");
  _progress.set_fraction(0.0);

  //get_window()->set_back_pixmap(pixmap);
  //get_window()->set_background(pattern);

  fixed_container->add(_background);
  fixed_container->put(_progress, 250, 180);
  fixed_container->put(_label1, 250, 200);
  fixed_container->put(_cancel, 586 - 80, 20);

  add(*fixed_container);
  show_all();
}

bool Ganash::Ui::Dialog::Splash::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
  //Cairo::Operator op = cr->get_operator();
  //cr->set_operator(Cairo::OPERATOR_SOURCE);
  Gtk::Window::on_draw(cr);

  //cr->set_operator(op);

  return false;
}

Ganash::Ui::Dialog::Splash::~Splash()
{

}


void Ganash::Ui::Dialog::Splash::update(const std::string label1, const std::string label2, gdouble percentage)
{
  _label1.set_text(label1);
  _label1.set_ellipsize(Pango::ELLIPSIZE_START);
  _label1.set_size_request(200, -1);
  _progress.set_fraction(percentage);
}

bool Ganash::Ui::Dialog::Splash::my_timeout_function()
{
  _opacity -= 0.1;
  set_opacity(_opacity);
  if(_opacity<=0.0)
    {
      // TODO emit shutdown_complete
      m_signal_shutdown_complete.emit();
      hide();
      return false;
    }
  return true;
}

void Ganash::Ui::Dialog::Splash::shutdown()
{
  _opacity = 1.0;
  //Glib::signal_timeout().connect(sigc::ptr_fun(&Ganash::Ui::Dialog::Splash::my_timeout_function), 1000);
  Glib::signal_timeout().connect(sigc::mem_fun(*this, &Ganash::Ui::Dialog::Splash::my_timeout_function), 50);

}

Ganash::Ui::Dialog::Splash::type_signal_shutdown_complete
Ganash::Ui::Dialog::Splash::signal_shutdown_complete()
{
  return m_signal_shutdown_complete;
}
