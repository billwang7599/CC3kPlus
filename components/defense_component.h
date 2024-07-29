#ifndef DEFENSE_COMPONENT_H
#define DEFENSE_COMPONENT_H

#include "component.h"

class DefenseComponent : public Component
{
public:
    int defense_power;
    DefenseComponent(int defense_power);
};

#endif