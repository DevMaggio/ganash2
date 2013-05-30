#ifndef GANASH_CORE_DOCKMANAGER_H
#define GANASH_CORE_DOCKMANAGER_H

namespace Ganash {
namespace Core {

class DockManager
{
public:
    enum DockArea {
        Top    = 1<<0,
        Right  = 1<<1,
        Bottom = 1<<2,
        Left   = 1<<3
    };
    DockManager();
    virtual ~DockManager();
    static DockManager* getInstance();
protected:
    static DockManager* _instance;
};

} // namespace Core
} // namespace Ganash

#endif // GANASH_CORE_DOCKMANAGER_H
