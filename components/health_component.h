#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "component.h"

class HealthComponent : public Component
{
public:
    HealthComponent(int max, int current);
    const int max_health;
    int current_health;
};

#endif