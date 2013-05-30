#ifndef GANASH_SVG_TEMPLATE_H
#define GANASH_SVG_TEMPLATE_H

// TEMPORARY
#include "display/object.h"

namespace Ganash {
namespace Svg {

class Template
{
public:
    explicit Template(){}
    virtual ~Template(){}
    virtual Ganash::Display::Object *rect() = 0;
};


} // namespace Svg
} // namespace Ganash

#endif // GANASH_SVG_TEMPLATE_H
