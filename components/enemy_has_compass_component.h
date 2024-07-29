#include "component.h"

class EnemyHasCompassComponent : public Component
{
public:
    bool has_compass;
    EnemyHasCompassComponent(bool has_compass) : has_compass{has_compass} {};
};
