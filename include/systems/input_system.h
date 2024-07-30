#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include "entities/entity.h"
#include <memory>
#include <string>
#include <vector>
#include <string>

class InputSystem {
    std::vector<std::string> valid_directions = {"no","so","ea","we","ne","nw","se","sw"};
    bool valid_direction(std::string);
    public:
    void update(std::shared_ptr<Entity>);
};

#endif