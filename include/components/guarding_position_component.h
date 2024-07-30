#ifndef GUARDING_POSITION_COMPONENT_H
#define GUARDING_POSITION_COMPONENT_H

#include "components/component.h"

class GuardingPositionComponent : public Component {
    public:
    const int row, col;
    GuardingPositionComponent(int row, int col) : row{row}, col{col} {};
};
#endif // GUARDING_POSITION_COMPONENT_H
