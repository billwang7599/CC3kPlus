#include "systems/input_system.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

bool InputSystem::validDirection(std::string command) {
    return find(valid_directions.begin(), valid_directions.end(), command) != valid_directions.end();
}

void InputSystem::update(shared_ptr<Entity> player) {
    string input, command;
    getline(cin, input);
    stringstream iss(input);
    iss >> command;

    if (command == "u") {
        player->getComponent<ActionComponent>()->move = false;
        player->getComponent<ActionComponent>()->attack = false;
        player->getComponent<ActionComponent>()->use = true;
        command.clear();
        iss >> command;
    }  else if (command == "a") {
        player->getComponent<ActionComponent>()->move = false;
        player->getComponent<ActionComponent>()->attack = true;
        player->getComponent<ActionComponent>()->use = false;
        command.clear();
        iss >> command;
    } else {
        player->getComponent<ActionComponent>()->move = true;
        player->getComponent<ActionComponent>()->attack = false;
        player->getComponent<ActionComponent>()->use = false;
    }

    if (validDirection(command)) {
        player->getComponent<DirectionComponent>()->direction = command;
        return;
    }
    throw "Not valid command!";
}