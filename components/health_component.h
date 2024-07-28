#include "component.h"

class HealthComponent : public Component
{
public:
    HealthComponent(const int max, const int current) : max_health{max}, current_health{current} {};
    const int max_health;
    int current_health;
};