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

#define GANASH_MOTION_MILISECONDE 1000.00

#define GANASH_MOTION_TIME_UNIT GANASH_MOTION_MILISECONDE

#include "motion/time-line.h"
#include <math.h>

Ganash::Motion::TimeLine::TimeLine(int duration) :
    _duration(duration),
    //_frame(),
    _timer()
{
    //_timer.reset(); no purpose
}

Ganash::Motion::TimeLine::~TimeLine()
{
}

void Ganash::Motion::TimeLine::start()
{
    _timer.start();
}

void Ganash::Motion::TimeLine::stop()
{
    _timer.stop();
}

int Ganash::Motion::TimeLine::currentFrame() const
{
    // seconds elapsed
    double d = _timer.elapsed();
    double seek = d * GANASH_MOTION_TIME_UNIT;
    return (_frameEnd - _frameStart) * seek / _duration;// converte to double ?
}

int Ganash::Motion::TimeLine::currentTime() const
{
    // seconds elapsed as a floating point value, including any fractional part.
    double d = _timer.elapsed();
    return int (round(d * GANASH_MOTION_TIME_UNIT));
}

double Ganash::Motion::TimeLine::currentValue() const
{
    return _timer.elapsed();
}

int Ganash::Motion::TimeLine::duration() const
{
    return _duration;
}

void Ganash::Motion::TimeLine::setDuration(int duration)
{
    _duration = duration;
}

void Ganash::Motion::TimeLine::setFrameRange(int startFrame, int endFrame)
{
    _frameStart = startFrame;
    _frameEnd   = endFrame;
}

/*
QTimeLine ( int duration = 1000, QObject * parent = 0 )
virtual 	~QTimeLine ()
int 	currentFrame () const
int 	currentTime () const
qreal 	currentValue () const

CurveShape 	curveShape () const
Direction 	direction () const
int 	duration () const

QEasingCurve 	easingCurve () const
int 	endFrame () const
int 	frameForTime ( int msec ) const
int 	loopCount () const
void 	setCurveShape ( CurveShape shape )
void 	setDirection ( Direction direction )
void 	setDuration ( int duration )
void 	setEasingCurve ( const QEasingCurve & curve )
void 	setEndFrame ( int frame )
void 	setFrameRange ( int startFrame, int endFrame )
void 	setLoopCount ( int count )
void 	setStartFrame ( int frame )
void 	setUpdateInterval ( int interval )
int 	startFrame () const
State 	state () const
int 	updateInterval () const
virtual qreal 	valueForTime ( int msec ) const
*/
