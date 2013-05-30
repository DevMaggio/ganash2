#ifndef GANASH_SVG_LENGTH_H
#define GANASH_SVG_LENGTH_H

#include <libxml/xmlstring.h>

namespace Ganash {
namespace Svg {

class Length
{
public:

    typedef enum type_t {
        UNKNOWN,        //
        NUMBER,         //
        PERCENTAGE,     // "%"
        EMS,            // "em"
        EXS,            // "ex"
        PX,             // "px"
        CM,             // "cm"
        MM,             // "mm"
        IN,             // "in"
        PT,             // "pt"
        PC              // "pc"
    }Type;

    explicit Length();
    virtual ~Length();
    bool parse(const xmlChar *string);
    inline Ganash::Svg::Length::Type ParseType(const xmlChar*& ptr, const xmlChar* end);
    inline double number() {return _number;}// value
    inline double type() {return _type;}// unit
protected:
    double _number;
    Ganash::Svg::Length::Type _type;
};

} // namespace Svg
} // namespace Ganash

#endif // GANASH_SVG_LENGTH_H
