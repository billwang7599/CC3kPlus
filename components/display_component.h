#include "component.h"

class DisplayComponent : public Component
{
public:
    const char display_char;
    DisplayComponent(char display);
};