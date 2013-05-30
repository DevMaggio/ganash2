#include "extension/thread-manager.h"

#include <iostream>

Ganash::Extension::ThreadManager::ThreadManager() :
    m_threads (5)
{
    try
    {
        for (std::vector<Ganash::Extension::ThreadAbstract*>::size_type i = 0; i < m_threads.size(); ++i)
        {
            Ganash::Extension::ThreadAbstract *const progress = new Ganash::Extension::ThreadAbstract(i + 1);
            m_threads[i] = progress;
            progress->signal_finished().connect(
            sigc::bind<1>(sigc::mem_fun(*this, &Ganash::Extension::ThreadManager::on_progress_finished), progress));
        }
    }
    catch (...)
    {
        // In your own code, you should preferably use a smart pointer
        // to ensure exception safety.
        //std::for_each(m_threads.begin(), m_threads.end(),
        //DeletePtr<ThreadProgress*>());
        throw;
    }
}

Ganash::Extension::ThreadManager::~ThreadManager()
{
    //std::for_each(m_threads.begin(), m_threads.end(),
    //DeletePtr<Ganash::Extension::ThreadAbstract*>());
}

void Ganash::Extension::ThreadManager::run()
{
    // Install a one-shot idle handler to launch the threads.
    Glib::signal_idle().connect_once(sigc::mem_fun(*this, &Ganash::Extension::ThreadManager::launch_threads));
    //main_loop_->run();
}

void Ganash::Extension::ThreadManager::launch_threads()
{
    std::cout << "Launching " << m_threads.size() << " threads:" << std::endl;
    std::for_each(m_threads.begin(), m_threads.end(), std::mem_fun(&Ganash::Extension::ThreadAbstract::launch));
}

void Ganash::Extension::ThreadManager::on_progress_finished(Ganash::Extension::ThreadAbstract* thread)
{
    thread->join();
    std::cout << "Thread " << thread->id() << ": finished." << std::endl;
    // Quit if it was the last thread to be joined.
    //if (std::find_if(m_threads.begin(), m_threads.end(),
    //std::mem_fun(&Ganash::Extension::ThreadAbstract::unfinished)) == m_threads.end())
    //{
    //    //main_loop_->quit();
    //}
}
