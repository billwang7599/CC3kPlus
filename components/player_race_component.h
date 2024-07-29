#ifndef PLAYER_RACE_COMPONENT_H
#define PLAYER_RACE_COMPONENT_H

#include <string>
#include "component.h"

class PlayerRaceComponent : public Component
{
public:
    std::string race;
    PlayerRaceComponent(std::string race) : race{race} {}
};

#endif