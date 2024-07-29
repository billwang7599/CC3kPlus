#ifndef MOVEABLE_COMPONENT_H
#define MOVEABLE_COMPONENT_H

#include "component.h"

class MoveableComponent : public Component
{
public:
    bool moveable;
    MoveableComponent(bool moveable);
};

#endif