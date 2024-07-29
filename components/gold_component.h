#ifndef GOLD_COMPONENT_H
#define GOLD_COMPONENT_H

#include "component.h"

class GoldComponent : public Component
{
public:
    int gold;
    GoldComponent(int gold);
};

#endif