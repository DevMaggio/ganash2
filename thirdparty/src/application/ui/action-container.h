#ifndef GANASH_UI_ACTIONCONTAINER_H
#define GANASH_UI_ACTIONCONTAINER_H

/**
 *
 *
ActionManager am = ActionManager::getInstance();



ActionManager::menubar("MainMenu/FileMenu/Quit")->setAction(myAction, ActionManager::getGroup("myGroup"));
ActionManager::menubar("MainMenu")->menu("FileMenu")->menuitem("Quit")->setAction(myAction, ActionManager::group("myGroup"));
ActionManager::menubar("MainMenu")->menu("FileMenu")->menuitem("Quit")->setAction(myAction);
ActionManager::menubar("MainMenu")->menu("FileMenu")->menuitem("Quit")->setAction(myAction);
ActionManager::menubar("MainMenu")->getGroup()->setAction(myAction);
ActionManager::toolbar("name");
ActionManager::menubar("MainMenu")->menu("Help")->separator()->nextSibling();
ActionManager::menubar("MainMenu")->menu("Help")->placeholder("name");



Ganash::ActionManager
Ganash::ActionContainer
Ganash::ActionGroup
Ganash::Action


Ganash::Core
Ganash::Core::Command
Ganash::Core::Action
Ganash::Core::ActionManager [V]
Ganash::Core::ActionContainer
Ganash::Core::Extension
Ganash::Core::System

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
 *
 */

namespace Ganash {
namespace Ui { // Core

/**
 * @brief The ActionContainer class
 */
class ActionContainerBase // Adapter
{
public:
};


/**
 * @brief The ActionContainer class
 */
class ActionContainer
{
public:
    ActionContainer();
};


/**
 * @brief The ActionContainerToolBar class
 */
class ActionContainerToolBar : public ActionContainerBase
{
public:
    ActionContainerToolBar();
};


/**
 * @brief The ActionContainerMenuBar class
 */
class ActionContainerMenuBar : public ActionContainerBase
{
public:
    ActionContainerMenuBar();
};


/**
 * @brief The ActionContainerMenu class
 */
class ActionContainerMenu : public ActionContainerBase
{
public:
    ActionContainerMenu();
};


/**
 * @brief The ActionContainerMenuItem class
 */
class ActionContainerMenuItem : public ActionContainerBase
{
public:
    ActionContainerMenuItem();
};


/**
 * @brief The ActionContainerPlaceholder class
 */
class ActionContainerPlaceholder : public ActionContainerBase
{
public:
    ActionContainerPlaceholder();
};


} // namespace Ui
} // namespace Ganash

#endif // GANASH_UI_ACTIONCONTAINER_H
