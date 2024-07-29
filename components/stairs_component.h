#include "component.h"

class StairsComponent : public Component
{
public:
    bool visible;
    StairsComponent(bool visible) : visible{visible} {};
};
