#include "component.h"
#include <string>

class PlayerRaceComponent : public Component
{
public:
    std::string race;
    PlayerRaceComponent(std::string race) : race{race} {};
};
