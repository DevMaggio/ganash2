
#include "application/application.h"


/**
 * @brief main
 * @param argc
 * @param argv
 * @return int
 *
 */
int main(int argc, char *argv[])
{
  Ganash::Application *application = Ganash::Application::instance();

  const int status = application->run(argc, argv);

  return status;
}
