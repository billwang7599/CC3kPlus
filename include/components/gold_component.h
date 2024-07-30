#ifndef GOLD_COMPONENT_H
#define GOLD_COMPONENT_H

#include "component.h"

class GoldComponent : public Component
{
public:
    float gold;
    GoldComponent(float gold) : gold{gold} {};
};

#endif // GOLD_COMPONENT_H
