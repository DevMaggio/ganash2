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

#include "stage.h"

#include "display/shape.h"
#include "display/scene.h"

#include <glibmm/threads.h>
#include <glibmm/thread.h>
#include <glibmm.h>
#include <gtkmm.h>


Ganash::Widget::Stage::Stage() :
    Gtk::DrawingArea(),
    _scene(0)
{
    add_events(Gdk::POINTER_MOTION_MASK);

    Glib::signal_timeout().connect(sigc::mem_fun(*this, &Ganash::Widget::Stage::timeout_handler), 1000);
    //sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &Ganash::Widget::Stage::timeout_handler), 0);
    //sigc::connection conn = Glib::signal_timeout().connect(my_slot, 1500);
}

Ganash::Widget::Stage::~Stage()
{
}

bool Ganash::Widget::Stage::timeout_handler()
{
    //g_print("timeout_handler\n");
    queue_draw();
    return true;
}

bool Ganash::Widget::Stage::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  // scale to unit square and translate (0, 0) to be (0.5, 0.5), i.e.
  // the center of the window
  cr->scale(1.0, 1.0);
  cr->translate(0.0, 0.0);
  cr->set_line_width(1.0);

  cr->save();
  cr->set_source_rgba(1.0, 1.0, 1.0, 1.0);
  cr->paint();
  cr->restore();


  if(_scene)
  {
      Ganash::Graphics::RendererCairo renderer(cr);
      getScene()->render(&renderer);
  }
  // Ganash::Application::launch(sigc::mem( &Ganash::RenderThread));

}

void Ganash::Widget::Stage::setScene(Ganash::Display::Scene *scene)
{
    _scene = scene;
}

Ganash::Display::Scene *Ganash::Widget::Stage::getScene()
{
    return _scene;
}

bool Ganash::Widget::Stage::on_motion_notify_event(GdkEventMotion *event)
{
    int x;
    int y;
    get_pointer(x, y);
    //g_print("mouse[%d, %d]\n", x, y);
    //getScene()->on_motion(x, y);
    if(_scene)
    {
        getScene()->dispatch(x, y);
    }

    return false;
}
