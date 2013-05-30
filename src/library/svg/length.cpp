#include "svg/length.h"
#include "svg/utils.h"

#include <iostream>
#include <sstream>
#include <string.h>
#include <math.h>

Ganash::Svg::Length::Length() :
    _number(0),
    _type(Ganash::Svg::Length::UNKNOWN)
{
}

Ganash::Svg::Length::~Length()
{
}

bool Ganash::Svg::Length::parse(const xmlChar *string)
{
    float number;
    Ganash::Svg::Length::Type type;

    const xmlChar *ptr = string;
    const xmlChar *end = ptr + xmlStrlen(string);

    // return const char *ptr where number end or NULL if error occure
    if (!Ganash::Svg::Utils::ParseNumber(ptr, end, number)) {
        //ec = SYNTAX_ERR;
        return false;
    }

    type = ParseType(ptr, end);
    if (type == Ganash::Svg::Length::UNKNOWN)
    {
        //ec = SYNTAX_ERR;
        return false;
    }

    _number = number;
    _type = type;

    return true;
}

inline Ganash::Svg::Length::Type
Ganash::Svg::Length::ParseType(const xmlChar*& ptr, const xmlChar* end)
{
    if (ptr == end)
        return Ganash::Svg::Length::NUMBER;

    const xmlChar firstChar = *ptr;

    if (++ptr == end)
        return firstChar == '%' ? Ganash::Svg::Length::PERCENTAGE : Ganash::Svg::Length::UNKNOWN;

    const xmlChar secondChar = *ptr;

    if (++ptr != end)
        return Ganash::Svg::Length::UNKNOWN;

    if (firstChar == 'e' && secondChar == 'm')
        return Ganash::Svg::Length::EMS;
    if (firstChar == 'e' && secondChar == 'x')
        return Ganash::Svg::Length::EXS;
    if (firstChar == 'p' && secondChar == 'x')
        return Ganash::Svg::Length::PX;
    if (firstChar == 'c' && secondChar == 'm')
        return Ganash::Svg::Length::CM;
    if (firstChar == 'm' && secondChar == 'm')
        return Ganash::Svg::Length::MM;
    if (firstChar == 'i' && secondChar == 'n')
        return Ganash::Svg::Length::IN;
    if (firstChar == 'p' && secondChar == 't')
        return Ganash::Svg::Length::PT;
    if (firstChar == 'p' && secondChar == 'c')
        return Ganash::Svg::Length::PC;

    return Ganash::Svg::Length::UNKNOWN;
}
