#include "svg/attribute.h"

Ganash::Svg::Attribute::Attribute(const xmlChar *name)
{
    _type = Ganash::Svg::Attribute::asType(name);
}

Ganash::Svg::Attribute::Attribute(Ganash::Svg::Attribute::Type type)
{
    _type = type;
}

Ganash::Svg::Attribute::~Attribute()
{
}

Ganash::Svg::Attribute::Type Ganash::Svg::Attribute::asType(const xmlChar *name)
{
    Ganash::Svg::Attribute::Type type = Ganash::Svg::Attribute::UNKNOW;
    if(xmlStrEqual(name, BAD_CAST "x"))
    {
        type = Ganash::Svg::Attribute::X;
    }
    else if(xmlStrEqual(name, BAD_CAST "y"))
    {
        type = Ganash::Svg::Attribute::Y;
    }
    else if(xmlStrEqual(name, BAD_CAST "width"))
    {
        type = Ganash::Svg::Attribute::WIDTH;
    }
    else if(xmlStrEqual(name, BAD_CAST "height"))
    {
        type = Ganash::Svg::Attribute::HEIGHT;
    }
    return type;
}

void Ganash::Svg::Attribute::setValue(Glib::ValueBase *value)
{
    _value = value;
}
