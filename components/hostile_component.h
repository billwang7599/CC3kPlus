#include "component.h"

class HostileComponent : public Component
{
public:
    bool hostile;
    HostileComponent(bool hostile) : hostile{hostile} {};
};
