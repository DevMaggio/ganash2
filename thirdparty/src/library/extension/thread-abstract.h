#ifndef GANASH_EXTENSION_THREADABSTRACT_H
#define GANASH_EXTENSION_THREADABSTRACT_H

#include <glibmm.h>
#include <sigc++/signal.h>

namespace Ganash {
namespace Extension {

class ThreadAbstract
{
public:
    explicit ThreadAbstract(int id);
    virtual ~ThreadAbstract();
    int id() const;
    void launch();
    void join();
    bool unfinished() const;
    sigc::signal<void>& signal_finished();
private:
    enum { ITERATIONS = 100 };
    // Note that the thread does not write to the member data at all. It only
    // reads signal_increment_, which is only written to before the thread is
    // launched. Therefore, no locking is required.
    Glib::Threads::Thread* thread_;
    int id_;
    unsigned int progress_;
    Glib::Dispatcher signal_increment_;
    sigc::signal<void> signal_finished_;
    void progress_increment();
    void thread_function();
};

} // namespace Extension
} // namespace Ganash

#endif // GANASH_EXTENSION_THREADABSTRACT_H
