#ifndef ATTACK_COMPONENT_H
#define ATTACK_COMPONENT_H

#include "component.h"

class AttackComponent : public Component
{
public:
    int attackPower;
    AttackComponent(int attackPower) : attackPower{attackPower} {};
};

#endif