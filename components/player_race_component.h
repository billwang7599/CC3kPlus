#include <string>

#include "component.h"

class PlayerRaceComponent : public Component
{
public:
    std::string race;
    PlayerRaceComponent(std::string race);
};