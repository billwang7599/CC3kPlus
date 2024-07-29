#ifndef GOLD_STEAL_COMPONENT_H
#define GOLD_STEAL_COMPONENT_H

#include "component.h"

class GoldStealComponent : public Component
{
public:
    int amountStolen;
    GoldStealComponent(int amount);
};

#endif