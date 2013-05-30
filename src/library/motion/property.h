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

#ifndef GANASH_MOTION_PROPERTY_H
#define GANASH_MOTION_PROPERTY_H

#include "geom/rectangle.h"

#include <glibmm/variant.h>

#define VARIANT_TYPE_RECTANGLE ((const GVariantType *) "z")

    namespace Glib
    {
    /** Specialization of Glib::Variant containing a bool type.
     * @newin{2,26}
     * @ingroup Variant
     */
    template <>
    class Variant<Ganash::Geom::Rectangle> : public VariantBase
    {
    public:
      typedef Ganash::Geom::Rectangle CType;

      /// Default constructor.
      Variant<Ganash::Geom::Rectangle>()
      : VariantBase()
      {}

      /** GVariant constructor.
       * @param castitem The GVariant to wrap.
       */
      explicit Variant<Ganash::Geom::Rectangle>(GVariant* castitem, bool take_a_reference = false)
      : VariantBase(castitem, take_a_reference)
      {}

      /** Gets the Glib::VariantType.
       * @return The Glib::VariantType.
       */
      static const VariantType& variant_type() G_GNUC_CONST;

      /** Creates a new Glib::Variant<bool>.
       * @param data The value of the new Glib::Variant<bool>.
       * @return The new Glib::Variant<bool>.
       */
      static Variant<Ganash::Geom::Rectangle> create(Ganash::Geom::Rectangle data);

      /** Gets the value of the Glib::Variant<bool>.
       * @return The bool value of the Glib::Variant<bool>.
       */
      Ganash::Geom::Rectangle get() const;
    protected:
      Ganash::Geom::Rectangle _rect;
    };
  } // end namespace Glib

// #include variant.h

#include "motion/time-line.h"
#include "motion/easing.h"
#include "display/object.h"

namespace Ganash {
namespace Motion {

class Property
{
public:
    explicit Property();
    Property(const std::string & propertyName, Ganash::Display::Object * dispalyObject);
    void setName(const std::string & propertyName);
    void setTarget(Ganash::Display::Object * dispalyObject);
    void setTimeLine(Ganash::Motion::TimeLine * timeLine);
    void setDuration(int duration);
    void setEasing(Ganash::Motion::Easing::Curve curve);
    void setStartValue(const Glib::VariantBase &value);
    void setEndValue(const Glib::VariantBase &value);
    void start();
    void stop();
protected:
    std::string _name;
    Ganash::Display::Object * _target;
    Ganash::Motion::TimeLine * _timeLine;
    Ganash::Motion::Easing::Curve _curve;
};

} // namespace Motion
} // namespace Ganash

#endif // GANASH_MOTION_PROPERTY_H
