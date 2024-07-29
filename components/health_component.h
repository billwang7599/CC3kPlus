#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "component.h"

class HealthComponent : public Component
{
public:
    HealthComponent(int max, int current) : max_health{max}, current_health{current} {}
    const int max_health;
    int current_health;
};

#endif