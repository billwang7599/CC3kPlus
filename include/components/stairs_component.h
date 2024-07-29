#ifndef STAIRS_COMPONENT_H
#define STAIRS_COMPONENT_H

#include "component.h"

class StairsComponent : public Component
{
public:
    bool visible;
    StairsComponent(bool visible) : visible{visible} {};
};

#endif // STAIRS_COMPONENT_H
