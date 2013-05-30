#ifndef GANASH_SVG_PARSER_H
#define GANASH_SVG_PARSER_H

#include "svg/template.h"

#include <libxml2/libxml/parser.h>
//#include <libxml/parser.h>
#include <libxml2/libxml/tree.h>

namespace Ganash {
namespace Svg {

class Parser
{
public:
    explicit Parser();
    virtual ~Parser();
    void parse(xmlNode * a_node);
    void setTemplate(Ganash::Svg::Template *tpl);
protected:
    Ganash::Svg::Template *_template;
};

} // namespace Svg
} // namespace Ganash

#endif // GANASH_SVG_PARSER_H
