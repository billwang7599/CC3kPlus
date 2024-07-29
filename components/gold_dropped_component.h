#include "component.h"

class GoldDroppedComponent : public Component
{
public:
    int gold_dropped;
    GoldDroppedComponent(int gold_dropped) : gold_dropped{gold_dropped} {};
};
