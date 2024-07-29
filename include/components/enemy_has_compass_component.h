#ifndef ENEMY_HAS_COMPASS_COMPONENT_H
#define ENEMY_HAS_COMPASS_COMPONENT_H

#include "component.h"

class EnemyHasCompassComponent : public Component
{
public:
    bool has_compass;
    EnemyHasCompassComponent(bool has_compass) : has_compass{has_compass} {};
};

#endif // ENEMY_HAS_COMPASS_COMPONENT_H
