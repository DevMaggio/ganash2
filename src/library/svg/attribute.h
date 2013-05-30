#ifndef GANASH_SVG_ATTRIBUTE_H
#define GANASH_SVG_ATTRIBUTE_H

#include <libxml/xmlstring.h>
#include <glibmm/value.h>

namespace Ganash {
namespace Svg {

class Attribute
{
public:
    enum Type
    {
        UNKNOW,
        X,
        Y,
        WIDTH,
        HEIGHT
    };
    Attribute(const xmlChar *name);
    Attribute(Ganash::Svg::Attribute::Type type);
    ~Attribute();
    static Type asType(const xmlChar *name);
    inline Type type() { return _type;}
    void setValue(Glib::ValueBase *value);
    inline Glib::ValueBase *value() { return _value;}
protected:
    Type _type;
    Glib::ValueBase *_value;
};

} // namespace Svg
} // namespace Ganash

#endif // GANASH_SVG_ATTRIBUTE_H
