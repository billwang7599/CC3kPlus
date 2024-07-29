#include "component.h"

class MoveableComponent : public Component
{
public:
    bool moveable;
    MoveableComponent(bool moveable);
};