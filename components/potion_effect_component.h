#ifndef POTION_EFFECT_COMPONENT_H
#define POTION_EFFECT_COMPONENT_H

#include "component.h"

class PotionEffectComponent : public Component
{
public:
    int attack_change, defense_change;
    PotionEffectComponent(int attack_change, int defense_change);
};

#endif