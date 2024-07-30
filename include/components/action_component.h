#ifndef ACTION_COMPONENT_H
#define ACTION_COMPONENT_H

#include "component.h"

class ActionComponent : public Component {
    public:
    bool move, attack, use;
    ActionComponent() : move{true}, attack{false}, use{false} {};
};
#endif // ACTION_COMPONENT_H
