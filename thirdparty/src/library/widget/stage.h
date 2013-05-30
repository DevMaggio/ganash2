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

#ifndef GANASH_WIDGET_STAGE_H
#define GANASH_WIDGET_STAGE_H

#include "display/scene.h"

#include <gtkmm/drawingarea.h>

namespace Ganash {
namespace Widget {

// @see drawing on and reusing an off-screen image surface
class Stage : public Gtk::DrawingArea
{
public:
    Stage();
    ~Stage();
    void setScene(Ganash::Display::Scene *scene);
    Ganash::Display::Scene *getScene();
protected:
    Ganash::Display::Scene *_scene;
    bool timeout_handler();

    //void on_start();
    //void on_draw();
    //void on_stop();
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    bool on_motion_notify_event(GdkEventMotion*event);
};

} // namespace Widget
} // namespace Ganash

#endif // GANASH_WIDGET_STAGE_H
