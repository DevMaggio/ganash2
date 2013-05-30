#include "extension/thread-abstract.h"
#include <iostream>

Ganash::Extension::ThreadAbstract::ThreadAbstract(int id) :
    thread_ (0),
    id_ (id),
    progress_ (0)
{
    // Connect to the cross-thread signal.
    signal_increment_.connect(sigc::mem_fun(*this, &Ganash::Extension::ThreadAbstract::progress_increment));
}

Ganash::Extension::ThreadAbstract::~ThreadAbstract()
{
    // It is an error if the thread is still running at this point.
    g_return_if_fail(thread_ == 0);
}

int Ganash::Extension::ThreadAbstract::id() const
{
    return id_;
}

void Ganash::Extension::ThreadAbstract::launch()
{
    // Create a joinable thread.
    thread_ = Glib::Threads::Thread::create(sigc::mem_fun(*this, &Ganash::Extension::ThreadAbstract::thread_function));
}

void Ganash::Extension::ThreadAbstract::join()
{
    thread_->join();
    thread_ = 0;
}

bool Ganash::Extension::ThreadAbstract::unfinished() const
{
    return (progress_ < ITERATIONS);
}

sigc::signal<void>& Ganash::Extension::ThreadAbstract::signal_finished()
{
    return signal_finished_;
}

void Ganash::Extension::ThreadAbstract::progress_increment()
{
    ++progress_;
    std::cout << "Thread " << id_ << ": " << progress_ << '%' << std::endl;
    if (progress_ >= ITERATIONS)
        signal_finished_();
}

void Ganash::Extension::ThreadAbstract::thread_function()
{
    Glib::Rand rand;
    for (int i = 0; i < ITERATIONS; ++i)
    {
        Glib::usleep(rand.get_int_range(2000, 20000));
        // Tell the main thread to increment the progress value.
        signal_increment_();
    }
}
