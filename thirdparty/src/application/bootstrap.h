#ifndef GANASH_BOOTSTRAP_H
#define GANASH_BOOTSTRAP_H

#include "extension/plugin-manager.h"
#include "extension/thread-manager.h"

#include "ui/dialogs/splash.h"

#include <glibmm/thread.h>
#include <string>

namespace Ganash {
  
  class Bootstrap
  {
  public:
    explicit Bootstrap(int argc, char **argv);
    ~Bootstrap();

    // load_theme()
    // init_theme()

    void load_plugin();
    void init_plugin();

    // Ganash::Application::Setting
    // Ganash::Application::Bootstrap / Bootstrapper
    // Ganash::Application::Resource

    // _initStocks();
    // _initFoo()
    // _initBar()
    // _initBaz()
    //
    /*
    public function registerPluginResource($resource, $options = null);
    public function unregisterPluginResource($resource);
    public function hasPluginResource($resource);
    public function getPluginResource($resource);
    public function getPluginResources();
    public function getPluginResourceNames();
    public function setPluginLoader(Zend_Loader_PluginLoader_Interface $loader);
    public function getPluginLoader();
    */

    Ganash::Extension::ThreadManager *threadManager;

    Ganash::Extension::PluginManager *pluginManager;
    Ganash::Ui::Dialog::Splash *m_splash;

    void progress(std::string context, std::string message, float fraction);
    sigc::signal<void, std::string, std::string, float> signal_progress()
    {
      return m_signal_progress;
    }

  protected:
  sigc::signal<void, std::string, std::string, float> m_signal_progress;

  protected:

    int m_argc;
    char **m_argv;

  };
  
} // namespace Ganash

#endif // GANASH_BOOTSTRAP_H
