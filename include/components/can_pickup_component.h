#include "component.h"

class CanPickupComponent : public Component
{
public:
    bool can_pickup;
    CanPickupComponent(bool can_pickup) : can_pickup{can_pickup} {};
};
