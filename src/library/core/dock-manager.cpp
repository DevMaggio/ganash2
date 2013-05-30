#include "dock-manager.h"

namespace Ganash {
namespace Core {

DockManager *DockManager::_instance = 0;

DockManager::DockManager()
{
}

DockManager::~DockManager()
{
}

DockManager* DockManager::getInstance()
{
    if(DockManager::_instance == 0)
    {
        DockManager::_instance = new DockManager();
    }

    return DockManager::_instance;
}


} // namespace Core
} // namespace Ganash
