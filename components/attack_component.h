#include "component.h"

class AttackComponent : public Component
{
public:
    int attack_power;
    AttackComponent(int attack_power);
};
