#ifndef LIFESTEAL_COMPONENT_H
#define LIFESTEAL_COMPONENT_H

#include "component.h"

class LifestealComponent : public Component {
    public:
    float percentageStolen;
    LifestealComponent(float percent) : percentageStolen{percent} {};
};
#endif // LIFESTEAL_COMPONENT_H
