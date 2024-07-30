#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "component.h"

class HealthComponent : public Component
{
public:
    HealthComponent(const int max) : max_health{max}, current_health{max} {}; // one argument since max_heath == current_health on init
    const int max_health;
    int current_health;
};
#endif // HEALTH_COMPONENT_H
