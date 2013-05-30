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

#include "motion/property.h"
#include "geom/rectangle.h"

namespace Glib
{

/**** Glib::Variant<bool> ****************************************************/

 // static
 const VariantType& Variant<Ganash::Geom::Rectangle>::variant_type()
 {
  static VariantType type(VARIANT_TYPE_RECTANGLE);
  return type;
 }

 Variant<Ganash::Geom::Rectangle> Variant<Ganash::Geom::Rectangle>::create(Ganash::Geom::Rectangle data)
 {
  //Glib::Variant::create();
  //Glib::Variant::init()
  //Variant<Ganash::Geom::Rectangle> result = Variant<Ganash::Geom::Rectangle>(g_variant_new_boolean(data));
  GVariant *r = g_variant_new ("(dddd)", data.x(), data.y(), data.width(), data.height());
  Variant<Ganash::Geom::Rectangle> result = Variant<Ganash::Geom::Rectangle>(r);



  // Remove the floating reference (since it is newly created).
  //g_variant_ref_sink(result.gobj());

  return result;
 }

 Ganash::Geom::Rectangle Variant<Ganash::Geom::Rectangle>::get() const
 {
    gdouble x, y, width, height;
    g_variant_get (gobject_, "(dddd)", &x, &y, &width, &height);
    g_print("---> %f\n", width);

  //return g_variant_get_boolean(gobject_);
    Ganash::Geom::Rectangle rect(x, y, width, height);
    return rect;
 }

} // end namespace Glib


Ganash::Motion::Property::Property()
{
}

Ganash::Motion::Property::Property(const std::string & propertyName, Ganash::Display::Object * dispalyObject) :
    _name(propertyName),
    _target(dispalyObject)
{
}

void Ganash::Motion::Property::setName(const std::string & propertyName)
{
    _name = propertyName;
}

void Ganash::Motion::Property::setTarget(Ganash::Display::Object * dispalyObject)
{
    _target = dispalyObject;
}

void Ganash::Motion::Property::setDuration(int duration)
{
}

void Ganash::Motion::Property::setStartValue(const Glib::VariantBase &value)
{

    //Glib::Variant<Ganash::Geom::Rectangle> rect = static_cast<Glib::Variant<Ganash::Geom::Rectangle > >(value.gobj());
    //g_print("setStartValue %f\n", rect.get().height());
    Glib::VariantType varType = value.get_type();
    g_print("Value Size %d\n", value.get_size());
    g_print("Value Type %s\n", value.get_type_string().c_str());

    double x, y, width, height;

    g_variant_get(value.gobj_copy(), "(dddd)", &x, &y, &width, &height);
    g_print("Value is Rect{%f, %f, %f, %f}\n", x, y, width, height);
}

void Ganash::Motion::Property::setEndValue(const Glib::VariantBase &value)
{
}

void Ganash::Motion::Property::setEasing(Ganash::Motion::Easing::Curve curve)
{
    _curve = curve;
}

void Ganash::Motion::Property::start()
{
}

void Ganash::Motion::Property::stop()
{
}

void Ganash::Motion::Property::setTimeLine(Ganash::Motion::TimeLine * timeLine)
{
    _timeLine = timeLine;
}

