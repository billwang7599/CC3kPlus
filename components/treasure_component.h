#ifndef TREASURE_COMPONENT_H
#define TREASURE_COMPONENT_H

#include "component.h"

class TreasureComponent : public Component
{
public:
    int value;
    TreasureComponent(int value) : value{value} {}
};

#endif