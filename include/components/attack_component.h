#ifndef ATTACK_COMPONENT_H
#define ATTACK_COMPONENT_H


#include "component.h"

class AttackComponent : public Component
{
public:
    int attack_power;
    AttackComponent(int attack_power) : attack_power{attack_power} {};
};

#endif