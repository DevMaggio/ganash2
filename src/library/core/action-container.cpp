#include "core/action-container.h"

namespace Ganash {
namespace Core {

/**
 * TODO: gerer les destructeur : m_children : g_list_free();
 *
 *
 * Dans le ActionManager modifier la signature des fonction d'acces menubar(), menu(), menuitem(), ... par
 * ActionManager* menubar(const char *name);
 * Et ajouter un membre m_target a ActionManager de type ActionContainer
 */
ActionContainer::ActionContainer(xmlNodePtr node) :
    m_index(0),
    m_name(""),
    m_parent(0),
    m_node(node),
    m_children(0)
{
}

ActionContainer::~ActionContainer()
{
}

template <class ActionContainerTemplate>
ActionContainerTemplate* ActionContainer::get(const char *name, const char *tag)
{
    GList* child;
    ActionContainer* container = 0;
    for(child = g_list_first(m_children); child; child = g_list_next(child))
    {
        container = (ActionContainer*) child->data;
        if(xmlStrEqual(container->node()->name, BAD_CAST tag))
        {
            xmlChar* attr = xmlGetProp(container->node(), BAD_CAST "name");
            if(attr
               && xmlStrlen(attr)
               && xmlStrEqual(attr, BAD_CAST name))
            {
                // TODO add setName()
                container->m_name = g_strdup(name);
                xmlFree(attr);
                return static_cast<ActionContainerTemplate*>(container);
            }
            xmlFree(attr);
        }
    }

    // Lazy initialize
    xmlNodePtr node = xmlNewNode(NULL, BAD_CAST tag);
    xmlNewProp(node, BAD_CAST "name", BAD_CAST name);
    //xmlNewProp(node, BAD_CAST "action", BAD_CAST "N/A"); a-t-on besoin d'affecter systematiquement une action ?
    xmlAddChild(this->node(), node);// this->target() VS this->node()
    // TODO attach parents

    container = new ActionContainerTemplate(node);
    m_children = g_list_append(m_children, container);


    return static_cast<ActionContainerTemplate*>(container);
}


//--- Subclassing ---


ActionContainerSeparator::ActionContainerSeparator(xmlNodePtr node) :
    ActionContainer(node)
{
}


ActionContainerMenuItem::ActionContainerMenuItem(xmlNodePtr node) :
    ActionContainer(node)
{
}


ActionContainerMenu::ActionContainerMenu(xmlNodePtr node) :
    ActionContainer(node)
{
}
ActionContainerMenu::~ActionContainerMenu()
{
}
ActionContainerMenu* ActionContainerMenu::menu(const char *name)
{
    return ActionContainer::get<ActionContainerMenu>(name, "menu");
}
ActionContainerMenuItem* ActionContainerMenu::menuitem(const char *name)
{
    return ActionContainer::get<ActionContainerMenuItem>(name, "menuitem");
}
ActionContainerSeparator*  ActionContainerMenu::separator(int index)
{
    return ActionContainer::get<ActionContainerSeparator>("", "separator");
}
ActionContainerPlaceholder* ActionContainerMenu::placeholder(const char *name)
{
    return ActionContainer::get<ActionContainerPlaceholder>(name, "placeholder");
}


ActionContainerToolItem::ActionContainerToolItem(xmlNodePtr node) :
    ActionContainer(node)
{
}


ActionContainerToolBar::ActionContainerToolBar(xmlNodePtr node) :
    ActionContainer(node)
{
}
ActionContainerToolBar::~ActionContainerToolBar()
{
}
ActionContainerToolItem* ActionContainerToolBar::toolitem(const char *name)
{
    return ActionContainer::get<ActionContainerToolItem>(name, "toolitem");
}
ActionContainerSeparator* ActionContainerToolBar::separator(int index)
{
    return ActionContainer::get<ActionContainerSeparator>("", "separator");
}
ActionContainerPlaceholder* ActionContainerToolBar::placeholder(const char *name)
{
    return ActionContainer::get<ActionContainerPlaceholder>(name, "placeholder");
}


ActionContainerAccelerator::ActionContainerAccelerator(xmlNodePtr node) :
    ActionContainer(node)
{
}


// --- ---


ActionContainerPlaceholder::ActionContainerPlaceholder(xmlNodePtr node) :
    ActionContainerMenu(node)
{
}
ActionContainerPlaceholder::~ActionContainerPlaceholder()
{
}
ActionContainerToolItem* ActionContainerPlaceholder::toolitem(const char *name)
{
    return ActionContainer::get<ActionContainerToolItem>(name, "toolitem");
}


ActionContainerMenuBar::ActionContainerMenuBar(xmlNodePtr node) :
    ActionContainerMenu(node)
{
}


ActionContainerPopUp::ActionContainerPopUp(xmlNodePtr node) :
    ActionContainerMenu(node)
{
}


// --- ---

ActionContainerUi::ActionContainerUi(xmlNodePtr node) :
    ActionContainer(node)
{
    if(!node)
    {
        // Create the UI XML description
        xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
        xmlDocSetRootElement(doc, xmlNewNode(NULL, BAD_CAST "ui"));
        // dtd = xmlCreateIntSubset(doc, BAD_CAST "root", NULL, BAD_CAST "tree2.dtd");

        setNode(xmlDocGetRootElement(doc));
    }
}
ActionContainerUi::~ActionContainerUi()
{
}
ActionContainerMenuBar* ActionContainerUi::menubar(const char *name)
{
    return ActionContainer::get<ActionContainerMenuBar>(name, "menubar");
}
ActionContainerToolBar* ActionContainerUi::toolbar(const char *name)
{
    return ActionContainer::get<ActionContainerToolBar>(name, "toolbar");
}
ActionContainerPopUp* ActionContainerUi::popup(const char *name)
{
    return ActionContainer::get<ActionContainerPopUp>(name, "popup");
}
ActionContainerAccelerator* ActionContainerUi::accelerator(const char *name)
{
    return ActionContainer::get<ActionContainerAccelerator>(name, "accelerator");
}


} // namespace Core
} // namespace Ganash
