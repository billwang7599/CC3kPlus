#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H
#include "component.h"

class PositionComponent : public Component
{
public:
    int row, col;
    PositionComponent(int row, int col) : row{row}, col{col} {};
};

#endif