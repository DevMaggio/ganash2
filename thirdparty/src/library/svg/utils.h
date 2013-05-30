#ifndef GANASH_SVG_PARSERUTILS_H
#define GANASH_SVG_PARSERUTILS_H

#include <libxml/xmlstring.h>

namespace Ganash {
namespace Svg {

class Utils
{
public:
    static bool ParseNumber(const xmlChar*& ptr, const xmlChar *end, float& number, bool skip = false);
};

} // namespace Svg
} // namespace Ganash

#endif // GANASH_SVG_PARSERUTILS_H
