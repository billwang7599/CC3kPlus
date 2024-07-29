#include "component.h"

class PotionEffectComponent : public Component
{
public:
    int attack_change, defense_change;
    PotionEffectComponent(int attack_change, int defense_change);
};