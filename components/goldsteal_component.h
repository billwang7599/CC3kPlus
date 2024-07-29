#include "component.h"

class GoldStealComponent : public Component
{
public:
    int amountStolen;
    GoldStealComponent(int amount);
};