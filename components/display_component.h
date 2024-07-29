#ifndef DISPLAY_COMPONENT_H
#define DISPLAY_COMPONENT_H

#include "component.h"

class DisplayComponent : public Component
{
public:
    const char display_char;
    DisplayComponent(char display) : display_char{display} {}
};

#endif