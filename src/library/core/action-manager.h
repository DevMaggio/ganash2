#ifndef GANASH_CORE_ACTIONMANAGER_H
#define GANASH_CORE_ACTIONMANAGER_H

#include "core/action-container.h"
#include "core/action.h"
#include <libxml/tree.h>
#include <glibmm.h>
#include <gtkmm/uimanager.h>


namespace Ganash {
namespace Core {

class ActionManager
{
public:
    explicit ActionManager();
    virtual ~ActionManager();
    static ActionManager* getInstance();

public:
    ActionManager* setAction(Glib::RefPtr<Gtk::Action> action, char* group);
    Glib::RefPtr<Gtk::ActionGroup> getGroup(char* name);

    ActionManager* menubar(const char *name);
    ActionManager* menu(const char *name);
    ActionManager* menuitem(const char *name);
    ActionManager* toolbar(const char *name);
    ActionManager* popup(const char *name);
    ActionManager* accelerator(const char *name);

    void nop();
    char* toString();

protected:
    ActionContainer* m_target;// TODO rename : m_targetContainer
    ActionContainerUi* m_container;// rename : m_uiContainer

    Glib::RefPtr<Gtk::UIManager> m_manager;
    GHashTable* m_groups; // Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;

    static ActionManager* _instance;
private:

};

} // namespace Core
} // namespace Ganash

#endif // GANASH_CORE_ACTIONMANAGER_H

/*
Core::ActionContainer->getWidget()

Core::ActionManager *am = Core::ICore::instance()->actionManager();

QAction *action = new QAction(tr("Example action"), this);
Core::Command *cmd = am->registerAction(action, Constants::ACTION_ID,
                                        Core::Context(Core::Constants::C_GLOBAL));
cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+A")));
connect(action, SIGNAL(triggered()), this, SLOT(triggerAction()));
/----------------------
Core::ActionContainer *menu = am->createMenu(Constants::MENU_ID);
menu->menu()->setTitle(tr("Example"));
menu->addAction(cmd);
am->actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);




am = ActionManager::getInstance();
ac = am->menubar("NAME");
ac = ac->menu("NAME");
ac = ac->menuitem("NAME");

am = ActionManager::getInstance();
am->registerAction();


ac = am->getAction("NAME");

*/
