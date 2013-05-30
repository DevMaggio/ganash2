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

#ifndef GANASH_MOTION_TIMELINE_H
#define GANASH_MOTION_TIMELINE_H

#include <glibmm/timer.h>

namespace Ganash {
namespace Motion {

class TimeLine
{
public:
    TimeLine(int duration = 1000);
    ~TimeLine();
    void start();
    void stop();

    int currentFrame () const;
    int currentTime () const;
    double currentValue() const;
    int duration() const;
    void setDuration(int duration);
    void setFrameRange(int startFrame, int endFrame);
protected:
    int _duration;// milisecondes => 32bits => 0->4294967296 => +/-2147483648 milisecondes ~> +/-24jours )
    Glib::Timer _timer;
    int _frameStart;
    int _frameEnd;
};

} // namespace Motion
} // namespace Ganash

#endif // GANASH_MOTION_TIMELINE_H
