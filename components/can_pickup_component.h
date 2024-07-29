#ifndef CAN_PICKUP_COMPONENT_H
#define CAN_PICKUP_COMPONENT_H

#include "component.h"

class CanPickupComponent : public Component
{
public:
    bool can_pickup;
    CanPickupComponent(bool can_pickup);
};

#endif