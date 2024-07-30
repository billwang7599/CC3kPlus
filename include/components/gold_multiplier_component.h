#ifndef GOLD_MULTIPLIER_COMPONENT_H
#define GOLD_MULTIPLIER_COMPONENT_H

#include "component.h"

class GoldMultiplierComponent : public Component {
    public:
    float percent;
    GoldMultiplierComponent(float percent) : percent{percent} {};
};
#endif // GOLD_MULTIPLIER_COMPONENT_H
