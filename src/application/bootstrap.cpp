#include "bootstrap.h"
#include <gtkmm.h>

Ganash::Bootstrap::Bootstrap(int argc, char **argv)
{
  m_argc = argc;
  m_argv = argv;

  threadManager = new Ganash::Extension::ThreadManager();
  //threadManager->add_thread(new Ganash::Extension::ThreadAbstract());
  //threadManager->add_thread(new Ganash::Extension::ThreadPaint());
  //threadManager->add_thread(new Ganash::Extension::ThreadDrawingArea());

  // Ganash::Extension::ThreadPluginManager
  m_splash = new Ganash::Ui::Dialog::Splash();
  pluginManager = new Ganash::Extension::PluginManager();
  pluginManager->addLoaderPath(PACKAGE_PLUGIN_DIR);
  pluginManager->signal_progress().connect(sigc::mem_fun(*this, &Ganash::Bootstrap::progress));
}

Ganash::Bootstrap::~Bootstrap()
{
}

void Ganash::Bootstrap::load_plugin()
{
  pluginManager->load();
}

void Ganash::Bootstrap::init_plugin()
{
  pluginManager->init();
}

void Ganash::Bootstrap::progress(std::string context, std::string message, float fraction)
{
  m_signal_progress.emit(context, message, fraction);
}
