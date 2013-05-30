#ifndef GANASH_CORE_ACTION_H
#define GANASH_CORE_ACTION_H

namespace Ganash {
namespace Core {

class Action
{
public:
    Action();
    virtual ~Action();
    char* name();
    void setName(char* name);
protected:
    char* m_name;
};

} // namespace Core
} // namespace Ganash

#endif // GANASH_CORE_ACTION_H
