#ifndef GANASH_EXTENSION_THREADMANAGER_H
#define GANASH_EXTENSION_THREADMANAGER_H

#include "extension/thread-abstract.h"

#include <vector>
#include <sigc++/signal.h>
//#include <sigc++/sigc++.h>
#include <glibmm.h>

namespace Ganash {
namespace Extension {

class ThreadManager : public sigc::trackable
{
public:
    ThreadManager();
    virtual ~ThreadManager();
    void run();
private:
//    Glib::RefPtr<Glib::MainLoop> main_loop_;
    std::vector<Ganash::Extension::ThreadAbstract*> m_threads;
    void launch_threads();
    void on_progress_finished(Ganash::Extension::ThreadAbstract* thread);
};

} // namespace Extension
} // namespace Ganash

#endif // GANASH_EXTENSION_THREADMANAGER_H
