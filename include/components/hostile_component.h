#ifndef HOSTILE_COMPONENT_H
#define HOSTILE_COMPONENT_H

#include "component.h"

class HostileComponent : public Component
{
public:
    bool hostile;
    HostileComponent(bool hostile) : hostile{hostile} {};
};


#endif // HOSTILE_COMPONENT_H
