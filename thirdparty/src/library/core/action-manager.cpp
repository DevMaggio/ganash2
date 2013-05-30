#include "core/action-manager.h"

// include ActionContainer
    // #if PLATFORM(GTK)
    // include ... ActionContainerGtk
    // #if PLATFORM(QT)
    // include ... ActionContainerQt
    // #if USE(LIBXML)
    // include ... ActionContainerLibXML
    // #if ENABLE(SVG)

namespace Ganash {
namespace Core {


class ActionManagerImpl
{

};

ActionManager *ActionManager::_instance = 0;

ActionManager::ActionManager()
{
    m_container = new ActionContainerUi();
    m_target = m_container;

    m_manager = Gtk::UIManager::create();
    m_groups = g_hash_table_new(g_str_hash, g_str_equal);
}

ActionManager::~ActionManager()
{
}

ActionManager* ActionManager::getInstance()
{
    if(ActionManager::_instance == 0)
    {
        ActionManager::_instance = new ActionManager();
    }

    return ActionManager::_instance;
}

void ActionManager::nop()
{
    g_print("Hello World");
}

ActionManager* ActionManager::setAction(Glib::RefPtr<Gtk::Action> action, char* group)
{
    //GtkAction* gtk_ui_manager_get_action(GtkUIManager *manager, const gchar *path);
    Glib::RefPtr<Gtk::ActionGroup> actionGroup = getGroup(group);
    actionGroup->add(action, sigc::mem_fun(*this, &ActionManager::nop));

    m_target->setAction(action);// Add attribute action="MyActionName"
    return this;
}

Glib::RefPtr<Gtk::ActionGroup> ActionManager::getGroup(char *name)
{
    std::string groupName(name?name:"");
    Glib::RefPtr<Gtk::ActionGroup> group;
    std::vector<Glib::RefPtr<Gtk::ActionGroup> > groups = m_manager->get_action_groups();
    std::vector<Glib::RefPtr<Gtk::ActionGroup> >::iterator it;
    for (it = groups.begin(); it != groups.end(); ++it) {
        group= *it;
        if (group->get_name()==groupName)
        {
            return group;
        }
    }

    // Lazy initialize
    group = Gtk::ActionGroup::create(groupName);
    m_manager->insert_action_group(group);
    return group;
}

ActionManager* ActionManager::menubar(const char *name)
{
    //ActionContainerUi* container = static_cast<ActionContainerUi*>(m_target);
    m_target = m_container->menubar(name);
    return this;
}

ActionManager* ActionManager::menu(const char *name)
{
    ActionContainerMenuBar* container = static_cast<ActionContainerMenuBar*>(m_target);
    m_target = container->menu(name);
    return this;
}

ActionManager* ActionManager::menuitem(const char *name)
{
    ActionContainerMenuBar* container = static_cast<ActionContainerMenuBar*>(m_target);
    m_target = container->menuitem(name);
    return this;
}

ActionManager* ActionManager::toolbar(const char *name)
{
    //ActionContainerUi* container = static_cast<ActionContainerUi*>(m_target);
    m_target = m_container->toolbar(name);
    return this;
}

ActionManager* ActionManager::popup(const char *name)
{
    //ActionContainerUi* container = static_cast<ActionContainerUi*>(m_target);
    m_target = m_container->popup(name);
    return this;
}

ActionManager* ActionManager::accelerator(const char *name)
{
    //ActionContainerUi* container = static_cast<ActionContainerUi*>(m_target);
    m_target = m_container->accelerator(name);
    return this;
}


char *
ActionManager::toString()
{
    xmlChar *xmlbuff;
    int buffersize;
    xmlDocDumpFormatMemory(m_target->node()->doc, &xmlbuff, &buffersize, 1);
    return (char *) xmlbuff;
}


} // namespace Core
} // namespace Ganash
