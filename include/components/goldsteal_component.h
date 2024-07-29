#ifndef GOLDSTEAL_COMPONENT_H
#define GOLDSTEAL_COMPONENT_H

#include "component.h"

class GoldStealComponent : public Component {
    public:
    int amountStolen;
    GoldStealComponent(int amount) : amountStolen{amount} {};

};
#endif // GOLDSTEAL_COMPONENT_H
