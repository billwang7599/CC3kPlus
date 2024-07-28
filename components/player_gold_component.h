#include "component.h"
#include <string>

class PlayerGoldComponent : public Component
{
public:
    int gold;
    PlayerGoldComponent(int gold) : gold{gold} {};
};
