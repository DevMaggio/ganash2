#ifndef GANASH_UI_ACTIONMANAGER_H
#define GANASH_UI_ACTIONMANAGER_H

#include <glibmm.h>
#include <gtkmm/action.h>
#include <gtkmm/actiongroup.h>
#include <gtkmm/uimanager.h>
/**
 *
 * \see http://doc.qt.digia.com/qtcreator-extending/core-actionmanager.html
 *
 * <example>
 * Ganash::Core::Internal::*
 * Ganash::Core::Command
 * Ganash::Core::Context
 * Ganash::Core::ActionContainer
 *
 * Ganash::Core::ActionManager *actionManager = Ganash::Core::Window::actionManager();
 * Gtk::Action *action = Gtk::Action::create("FileNewProject", Gtk::Stock::NEW, "New Project", "Create a new project");
 *
 * actionManager->setAction(action, "/MenuBar/FileMenu/FileNew");
 * actionManager->getAction("/MenuBar/FileMenu/FileNew/FileNewProject");
 *
 * Ganash::Core::Command *command = new Ganash::Core::Command(action);
 * command->connect(&my_callback);
 *
 * </example>
 *
 *
 Core::ActionManager *am = Core::ICore::actionManager();
 QAction *myAction = new QAction(tr("My Action"), this);
 Core::Command *cmd = am->registerAction(myAction,
                                          "myplugin.myaction",
                                          Core::Context(C_GLOBAL));
 cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+u")));
 connect(myAction, SIGNAL(triggered()), this, SLOT(performMyAction()));

 *
 */
#include <libxml/tree.h>
class Path;

namespace Ganash {
  namespace Ui {
    
    class ActionManager
    {
    public:
      static Ganash::Ui::ActionManager *instance();
      // TODO STL
      void registerAction(const Glib::RefPtr<Gtk::Action>& action);
      void registerAction(const Glib::RefPtr<Gtk::Action>& action, const Gtk::AccelKey& accel_key);
      void registerAction(const Glib::RefPtr<Gtk::Action>& action, const Gtk::Action::SlotActivate& slot);
      void registerAction(const Glib::RefPtr<Gtk::Action>& action, const Gtk::AccelKey& accel_key, const Gtk::Action::SlotActivate& slot);

      char *toString();
      void setAction(char *path, char *name);

      void merge(const Glib::ustring &buffer);
      Glib::RefPtr<Gtk::UIManager> m_refUIManager;
      Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
    protected:
      ActionManager();
      xmlNodePtr get(char *path, xmlNodePtr node);
      static Ganash::Ui::ActionManager* _instance;
      xmlDocPtr m_doc;
    };
    
  } // namespace Ui
} // namespace Ganash

#endif // GANASH_UI_ACTIONMANAGER_H
