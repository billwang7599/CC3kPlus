#ifndef GOLDSTEAL_COMPONENT_H
#define GOLDSTEAL_COMPONENT_H

#include "component.h"

class GoldStealComponent : public Component
{
public:
    float amountStolen;
    GoldStealComponent(float amount) : amountStolen{amount} {};
};
#endif // GOLDSTEAL_COMPONENT_H
