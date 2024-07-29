#include "component.h"

class LifestealComponent : public Component
{
public:
    float percentageStolen;
    LifestealComponent(float percent);
};