#include "component.h"

class DefenseComponent : public Component
{
public:
    int defense_power;
    DefenseComponent(int defense_power) : defense_power{defense_power} {};
};
