#ifndef POTION_EFFECT_COMPONENT_H
#define POTION_EFFECT_COMPONENT_H

#include "component.h"
#include <string>

class PotionEffectComponent : public Component
{
public:
    int attackChange, defenseChange;
    PotionEffectComponent(int attackChange, int defenseChange) : attackChange{attackChange}, defenseChange{defenseChange} {};
};

#endif // POTION_EFFECT_COMPONENT_H
