#ifndef GANASH_CORE_ACTIONCONTAINER_H
#define GANASH_CORE_ACTIONCONTAINER_H

#include "core/action.h"

#include <gtkmm.h>
#include <glib/glist.h>
#include <libxml/tree.h>

namespace Ganash {
namespace Core {

class ActionContainerPlaceholder;

class ActionContainer
{
public:
    explicit ActionContainer(xmlNodePtr node);
    virtual ~ActionContainer();
    virtual inline char* name() const { return m_name;}
    virtual inline GList* children() const { return m_children;}
    virtual inline int index() const { return m_index;}
    virtual inline xmlNodePtr node() const { return m_node;}
    virtual inline ActionContainer* parent() const { return m_parent;}
    virtual inline Gtk::Widget* widget() const { return 0;}
    virtual ActionContainer* setAction(Glib::RefPtr<Gtk::Action> action) {
        // TODO check DTD, libxml le fait, mais faut l'activer ...
        xmlNewProp(node(), BAD_CAST "action", BAD_CAST action->get_name().c_str());
        return this;
    }
protected:
    virtual inline void setIndex(int index) { m_index = index;}
    virtual inline void setNode(xmlNodePtr node) { m_node = node;}
    virtual inline void setParent(ActionContainer* parent) { m_parent = parent;}

    template <class ActionContainerTemplate> ActionContainerTemplate* get(const char *name, const char *tag);

    int m_index;
    char * m_name;
    ActionContainer* m_parent;
    xmlNodePtr m_node;
    GList* m_children;
};

//--- Subclassing ---


class ActionContainerSeparator : public ActionContainer
{
public:
    explicit ActionContainerSeparator(xmlNodePtr node);
};


class ActionContainerMenuItem : public ActionContainer
{
public:
    explicit ActionContainerMenuItem(xmlNodePtr node);
};


class ActionContainerMenu : public ActionContainer
{
public:
    explicit ActionContainerMenu(xmlNodePtr node);
    virtual ~ActionContainerMenu();

    ActionContainerMenu* menu(const char *name);
    ActionContainerMenuItem* menuitem(const char *name);
    ActionContainerSeparator*  separator(int index);
    ActionContainerPlaceholder* placeholder(const char *name);
};


class ActionContainerToolItem : public ActionContainer
{
public:
    explicit ActionContainerToolItem(xmlNodePtr node);

    // ???
    // ActionContainerMenu* menu(const char *name);
};


class ActionContainerToolBar : public ActionContainer
{
public:
    explicit ActionContainerToolBar(xmlNodePtr node);
    virtual ~ActionContainerToolBar();

    ActionContainerToolItem* toolitem(const char *name);
    ActionContainerSeparator* separator(int index);
    ActionContainerPlaceholder* placeholder(const char *name);
};


class ActionContainerAccelerator : public ActionContainer
{
public:
    explicit ActionContainerAccelerator(xmlNodePtr node);
};


// --- ---


class ActionContainerPlaceholder : public ActionContainerMenu
{
public:
    explicit ActionContainerPlaceholder(xmlNodePtr node);
    virtual ~ActionContainerPlaceholder();

    ActionContainerToolItem* toolitem(const char *name);
};


class ActionContainerMenuBar : public ActionContainerMenu
{
public:
    explicit ActionContainerMenuBar(xmlNodePtr node);
};


class ActionContainerPopUp : public ActionContainerMenu
{
public:
    explicit ActionContainerPopUp(xmlNodePtr node);
};


// --- ---

class ActionContainerUi : public ActionContainer
{
public:
    explicit ActionContainerUi(xmlNodePtr node = 0);
    virtual ~ActionContainerUi();

    ActionContainerMenuBar* menubar(const char *name);
    ActionContainerToolBar* toolbar(const char *name);
    ActionContainerPopUp* popup(const char *name);
    ActionContainerAccelerator* accelerator(const char *name);
};



} // namespace Core
} // namespace Ganash

#endif // GANASH_CORE_ACTIONCONTAINER_H
