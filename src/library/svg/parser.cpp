#include "svg/parser.h"
#include "svg/length.h"
#include "svg/attribute.h"
#include "svg/element.h"

#include "display/rectangle.h"

#include <libxml/xmlstring.h>
#include <glibmm/variant.h>
#include <iostream>

Ganash::Svg::Parser::Parser() :
    _template(0)
{
}

Ganash::Svg::Parser::~Parser()
{
}

void Ganash::Svg::Parser::setTemplate(Ganash::Svg::Template *tpl)
{
    _template = tpl;
}

void Ganash::Svg::Parser::parse(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;
    // object;
    // container
    /*, Ganash::Display::Container container*/
    Ganash::Display::Object *obj;
    Ganash::Svg::Element *elt;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next)
    {
        if (cur_node->type == XML_ELEMENT_NODE)
        {
            printf("node type: Element, name: %s\n", cur_node->name);
            if(xmlStrcmp(cur_node->name, BAD_CAST "svg")==0)
            {
                printf("svg\n");
            }
            else if(xmlStrcmp(cur_node->name, BAD_CAST "rect")==0)
            {
                printf("rect\n");

                // parse value, and build its display
                obj = _template->rect();
                elt = new Ganash::Svg::Element();
            }
        }

        xmlAttr* attribute = cur_node->properties;
        while(attribute && attribute->name && attribute->children)
        {
            xmlChar* value = xmlNodeListGetString(cur_node->doc, attribute->children, 1);
            printf("\tattribute[%s] = %s\n", attribute->name, value);

            Ganash::Svg::Attribute::Type type = Ganash::Svg::Attribute::asType(attribute->name);
            switch(type)
            {
            case Ganash::Svg::Attribute::X:
                break;
            case Ganash::Svg::Attribute::Y:
                break;
            case Ganash::Svg::Attribute::WIDTH:
                {
                    Ganash::Svg::Length *length = new Ganash::Svg::Length();
                    length->parse(value);

                    Glib::Value<Ganash::Svg::Length> *attr_value = new Glib::Value<Ganash::Svg::Length>;
                    attr_value->init(Glib::Value<Ganash::Svg::Length>::value_type());
                    attr_value->set(*length);

                    Ganash::Svg::Attribute *attr = new Ganash::Svg::Attribute(type);
                    attr->setValue(attr_value);

                    //Glib::Value<Ganash::Svg::Length> *len = static_cast<Glib::Value<Ganash::Svg::Length> *>(attr->value());
                    //std::cout << "Attribute.getValue = " << len->get().number() << std::endl;

                    elt->setWidth(*length);
                    //elt->setWidth(length.number());
                    //elt->setAttribute(attr);
                    //obj->setAttribute(attr);
                }
                break;
            case Ganash::Svg::Attribute::HEIGHT:
                break;
            case Ganash::Svg::Attribute::UNKNOW:
            default:
                break;
            }

            xmlFree(value);
            attribute = attribute->next;
        }

        parse(cur_node->children);
    }
}
