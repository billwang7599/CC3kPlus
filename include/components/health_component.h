#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "component.h"

class HealthComponent : public Component
{
public:
    HealthComponent(const int max) : maxHealth{max}, currentHealth{max} {}; // one argument since max_heath == current_health on init
    const int maxHealth;
    int currentHealth;
};
#endif // HEALTH_COMPONENT_H
