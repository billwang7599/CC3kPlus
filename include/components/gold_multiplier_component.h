#include "component.h"

class GoldEffectComponent : public Component {
    float percent;
    GoldEffectComponent(float percent) : percent{percent} {};
};