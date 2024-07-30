#ifndef DEFENSE_COMPONENT_H
#define DEFENSE_COMPONENT_H

#include "component.h"

class DefenseComponent : public Component
{
public:
    int defensePower;
    DefenseComponent(int defensePower) : defensePower{defensePower} {};
};

#endif // DEFENSE_COMPONENT_H
