#ifndef GANASH_CORE_DOCKMANAGER_H
#define GANASH_CORE_DOCKMANAGER_H

namespace Ganash {
namespace Core {

class DockManager
{
public:
    DockManager();
    virtual ~DockManager();
    static DockManager* getInstance();
protected:
    static DockManager* _instance;
};

} // namespace Core
} // namespace Ganash

#endif // GANASH_CORE_DOCKMANAGER_H
