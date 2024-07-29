#ifndef TREASURE_COMPONENT_H
#define TREASURE_COMPONENT_H

#include "component.h"
#include <string>

class TreasureComponent : public Component
{
public:
    int value;
    TreasureComponent(int value) : value{value} {};
};

#endif // TREASURE_COMPONENT_H
