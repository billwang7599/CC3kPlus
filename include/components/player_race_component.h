#ifndef PLAYER_RACE_COMPONENT_H
#define PLAYER_RACE_COMPONENT_H

#include "component.h"
#include <string>

class PlayerRaceComponent : public Component
{
public:
    std::string race;
    PlayerRaceComponent(std::string race) : race{race} {};
};

#endif // PLAYER_RACE_COMPONENT_H
