#include "core/action.h"

#include <glibmm.h>

namespace Ganash {
namespace Core {

Action::Action()
{
}
Action::~Action()
{
}
char* Action::name()
{
    return m_name;
}
void Action::setName(char* name)
{
    m_name = g_strdup(name);
}


} // namespace Core
} // namespace Ganash
