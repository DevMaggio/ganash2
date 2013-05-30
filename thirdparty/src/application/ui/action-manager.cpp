#include "action-manager.h"
#include <ctype.h>


// XPath

class Filter
{
public:
    virtual bool filter(xmlNodePtr node) = 0;
};

class FilterNodeName : public Filter
{
public:
    FilterNodeName(char *name) : m_name(name){}
    bool filter(xmlNodePtr node)
    {
        if(g_str_equal(node->name, m_name))
        {
            return true;
        }
        return false;
    }
protected:
    char *m_name;
};

class FilterNodeType : public Filter
{
public:
    FilterNodeType(xmlElementType type) : m_type(type){}
    bool filter(xmlNodePtr node)
    {
        if(node->type == m_type)
        {
            return true;
        }
        return false;
    }
protected:
    xmlElementType m_type;
};

class FilterNodeIndex : public Filter
{
public:
    FilterNodeIndex(int index) : m_index(index){}
    bool filter(xmlNodePtr node)
    {
        //xmlChildElementCount();
        xmlNodePtr cur_node;
        int index = 1;

        for (cur_node = node->parent->children; cur_node; cur_node = cur_node->next) {
            if(node == cur_node)
            {
                break;
            }
            ++index;
        }

        if(index == m_index)
        {
            return true;
        }
        return false;
    }
protected:
    int m_index;
};

class FilterNodeAttribute : public Filter
{
public:
    FilterNodeAttribute(char *name, char *value) : m_name(name), m_value(value){}
    bool filter(xmlNodePtr node)
    {
        xmlChar *value = xmlGetProp(node, BAD_CAST m_name);
        if(g_str_equal(value, m_value))
        {
            return true;
        }
        return false;
    }
protected:
    char *m_name;
    char *m_value;
};

class FilterNodeExpression : public Filter
{
public:
    explicit FilterNodeExpression(){}
    FilterNodeExpression(const char *content);
    virtual bool filter(xmlNodePtr node);
    std::vector<Filter *> m_filters;
};
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}
FilterNodeExpression::FilterNodeExpression(const char *content)
{
    // content = @name=value
    if(is_number(std::string(content)))
    {
        FilterNodeIndex *index = new FilterNodeIndex(atoi(content));
        m_filters.push_back(index);
    }
    if(content[0] == '@')
    {
        const char *pos = strchr(content, '=');
        if(pos != NULL)
        {
            char *name = g_strndup(content+1, pos-content);
            char *value= g_strdup(pos+1);
            FilterNodeAttribute *attr = new FilterNodeAttribute(name, value);
            m_filters.push_back(attr);
        }
    }

}
bool FilterNodeExpression::filter(xmlNodePtr node)
{
    bool ret = true;
    for(std::vector<Filter*>::iterator it = m_filters.begin(); it!=m_filters.end(); ++it)
    {
        Filter *f = *it;
        ret = ret && f->filter(node);
    }
    return ret;
}

class PathElement : public FilterNodeExpression
{
public:
    PathElement(const char *element);
    xmlNodePtr getChildNode(xmlNodePtr node);
    char *name;
    int   index;
};
PathElement::PathElement(const char *path) :
    FilterNodeExpression()
{
    const char *pos = strchr(path, '[');
    if(pos != NULL)
    {
        name = g_strndup(path, pos-path);
        const char *pos_end = strchr(path, ']');
        if(pos_end != NULL && pos_end>pos)
        {
            char *tmp = g_strndup(pos+1, pos_end-pos-1);
            m_filters.push_back(new FilterNodeType(XML_ELEMENT_NODE));
            m_filters.push_back(new FilterNodeName(name));
            m_filters.push_back(new FilterNodeExpression(tmp));
        }
    }
    else
    {
        name = g_strdup(path);
        m_filters.push_back(new FilterNodeType(XML_ELEMENT_NODE));
        m_filters.push_back(new FilterNodeName(name));
    }
}

xmlNodePtr PathElement::getChildNode(xmlNodePtr node)
{
    xmlNodePtr cur_node;

    for (cur_node = node->children; cur_node; cur_node = cur_node->next) {
        if (filter(cur_node)) {
            return cur_node;
        }
    }
    return NULL;
}
typedef PathElement* PathElementPtr;
class Path
{
public:
    explicit Path(char *path);
//protected:
    std::vector<PathElementPtr> m_elements;
};
Path::Path(char *path):
    m_elements()
{
    std::istringstream f(path);
    std::string s;
    while (std::getline(f, s, '/')) {
        if(s.empty())
        {
            continue;
        }
        PathElement *elt = new PathElement(s.c_str());
        m_elements.push_back(elt);
    }
}

/*extern*/ Ganash::Ui::ActionManager *Ganash::Ui::ActionManager::_instance = 0;

Ganash::Ui::ActionManager::ActionManager()
{
  m_refUIManager = Gtk::UIManager::create();
  m_refActionGroup = Gtk::ActionGroup::create();
  m_refUIManager->insert_action_group(m_refActionGroup);

  //add_accel_group(m_refUIManager->get_accel_group());

  /*
   * Create the document.
   */
  xmlDocPtr doc = NULL;
  xmlNodePtr root_node = NULL;
  xmlNodePtr node = NULL;

  doc = xmlNewDoc(BAD_CAST "1.0");
  root_node = xmlNewNode(NULL, BAD_CAST "ui");
  xmlDocSetRootElement(doc, root_node);

  node = xmlNewNode(NULL, BAD_CAST "menubar");
  xmlNewProp(node, BAD_CAST "name", BAD_CAST "MenuBar");
  root_node = xmlAddChild(root_node, node);
  /*
  node = xmlNewChild(root_node, NULL, BAD_CAST "menubar", BAD_CAST "this node has attributes");
  xmlNewProp(node, BAD_CAST "name", BAD_CAST "MenuBar");
  */

    m_doc = doc;
}

Ganash::Ui::ActionManager *Ganash::Ui::ActionManager::instance()
{
  if(Ganash::Ui::ActionManager::_instance == 0)
    {
      Ganash::Ui::ActionManager::_instance = new Ganash::Ui::ActionManager();
    }

  return Ganash::Ui::ActionManager::_instance;
}

void Ganash::Ui::ActionManager::registerAction(const Glib::RefPtr<Gtk::Action>& action)
{
  m_refActionGroup->add(action);
}

void Ganash::Ui::ActionManager::registerAction(const Glib::RefPtr<Gtk::Action>& action, const Gtk::Action::SlotActivate& slot)
{
  m_refActionGroup->add(action, slot);
}

void Ganash::Ui::ActionManager::registerAction(const Glib::RefPtr<Gtk::Action>& action, const Gtk::AccelKey& accel_key)
{
  m_refActionGroup->add(action, accel_key);
}
void Ganash::Ui::ActionManager::registerAction(const Glib::RefPtr<Gtk::Action>& action, const Gtk::AccelKey& accel_key, const Gtk::Action::SlotActivate& slot)
{
  m_refActionGroup->add(action, accel_key, slot);
}



void Ganash::Ui::ActionManager::merge(const Glib::ustring &buffer)
{
  m_refUIManager->add_ui_from_string(buffer);
}



/*
static void
Ganash::Ui::ActionManager::getMenubar()
{

}

*/

xmlNodePtr
Ganash::Ui::ActionManager::get(char *path, xmlNodePtr node)
{
    Path _path(path);
    xmlNodePtr cur_node = node;
    std::vector<PathElement*>::iterator it;
    for(it = _path.m_elements.begin(); it != _path.m_elements.end(); it++)
    {
        PathElement *elt = *it;
        node = elt->getChildNode(cur_node);
        if(node != NULL)
        {
            cur_node = node;
        }
        else
        {
            // create if not exists
            node = xmlNewNode(NULL, BAD_CAST elt->name);
            //xmlNodeSetContent(node, BAD_CAST "");
            //xmlNewProp(node, BAD_CAST "action", BAD_CAST "void");// elt->attributes();
            xmlAddChild(cur_node, node);
            cur_node = node;
        }
    }

    return node;
}

void
Ganash::Ui::ActionManager::setAction(char *path, char *name)
{
    xmlNode *cur_node = NULL;
    xmlNode *node = xmlDocGetRootElement(m_doc);
    g_print("Manager::setAction(%s)\n", path);
    cur_node = get(path, node);
    if(cur_node!=NULL)
    {
        xmlNewProp(cur_node, BAD_CAST "action", BAD_CAST name);
        g_print("current node = %s, %s\n", cur_node->name, xmlGetProp(cur_node, BAD_CAST "action"));
    }
    else
    {
        g_print("current node = not found\n");
    }
    //m_refActionGroup->add();

}
char *
Ganash::Ui::ActionManager::toString()
{
    xmlChar *xmlbuff;
    int buffersize;
    xmlDocDumpFormatMemory(m_doc, &xmlbuff, &buffersize, 1);
    return (char *) xmlbuff;
}


// get_widget
