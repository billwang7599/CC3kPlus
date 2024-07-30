#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <string>
#include <map>
#include <utility>

extern const int NUM_FLOORS;
extern const int FLOOR_HEIGHT;
extern const int FLOOR_WIDTH;
extern const std::vector<std::string> BOARD;
extern const std::vector<std::vector<std::pair<int, int>>> ROOMS;
extern const std::map<std::string, std::pair<int, int>> DIRECTION_MAP;

#endif // CONSTANTS_H
