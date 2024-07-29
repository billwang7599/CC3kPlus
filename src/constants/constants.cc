#include "constants/constants.h"

const std::vector<std::string> BOARD = {
    "|-----------------------------------------------------------------------------|",
    "|                                                                             |",
    "| |--------------------------|        |-----------------------|               |",
    "| |..........................|        |.......................|               |",
    "| |..........................+########+.......................|-------|       |",
    "| |..........................|   #    |...............................|--|    |",
    "| |..........................|   #    |..................................|--| |",
    "| |----------+---------------|   #    |----+----------------|...............| |",
    "|            #                 #############                |...............| |",
    "|            #                 #     |-----+------|         |...............| |",
    "|            #                 #     |............|         |...............| |",
    "|            ###################     |............|   ######+...............| |",
    "|            #                 #     |............|   #     |...............| |",
    "|            #                 #     |-----+------|   #     |--------+------| |",
    "|  |---------+-----------|     #           #          #              #        |",
    "|  |.....................|     #           #          #         |----+------| |",
    "|  |.....................|     ########################         |...........| |",
    "|  |.....................|     #           #                    |...........| |",
    "|  |.....................|     #    |------+--------------------|...........| |",
    "|  |.....................|     #    |.......................................| |",
    "|  |.....................+##########+.......................................| |",
    "|  |.....................|          |.......................................| |",
    "|  |---------------------|          |---------------------------------------| |",
    "|                                                                             |",
    "|-----------------------------------------------------------------------------|",
};

const std::vector<std::vector<std::pair<int, int>>> ROOMS = {
    {
        // Room 0, top left room
        {3, 3},
        {3, 4},
        {3, 5},
        {3, 6},
        {3, 7},
        {3, 8},
        {3, 9},
        {3, 10},
        {3, 11},
        {3, 12},
        {3, 13},
        {3, 14},
        {3, 15},
        {3, 16},
        {3, 17},
        {3, 18},
        {3, 19},
        {3, 20},
        {3, 21},
        {3, 22},
        {3, 23},
        {3, 24},
        {3, 25},
        {3, 26},
        {3, 27},
        {3, 28},
        {4, 3},
        {4, 4},
        {4, 5},
        {4, 6},
        {4, 7},
        {4, 8},
        {4, 9},
        {4, 10},
        {4, 11},
        {4, 12},
        {4, 13},
        {4, 14},
        {4, 15},
        {4, 16},
        {4, 17},
        {4, 18},
        {4, 19},
        {4, 20},
        {4, 21},
        {4, 22},
        {4, 23},
        {4, 24},
        {4, 25},
        {4, 26},
        {4, 27},
        {4, 28},
        {5, 3},
        {5, 4},
        {5, 5},
        {5, 6},
        {5, 7},
        {5, 8},
        {5, 9},
        {5, 10},
        {5, 11},
        {5, 12},
        {5, 13},
        {5, 14},
        {5, 15},
        {5, 16},
        {5, 17},
        {5, 18},
        {5, 19},
        {5, 20},
        {5, 21},
        {5, 22},
        {5, 23},
        {5, 24},
        {5, 25},
        {5, 26},
        {5, 27},
        {5, 28},
        {6, 3},
        {6, 4},
        {6, 5},
        {6, 6},
        {6, 7},
        {6, 8},
        {6, 9},
        {6, 10},
        {6, 11},
        {6, 12},
        {6, 13},
        {6, 14},
        {6, 15},
        {6, 16},
        {6, 17},
        {6, 18},
        {6, 19},
        {6, 20},
        {6, 21},
        {6, 22},
        {6, 23},
        {6, 24},
        {6, 25},
        {6, 26},
        {6, 27},
        {6, 28},
    },
    {
        // Room 1, top right room
        {3, 39},
        {3, 40},
        {3, 41},
        {3, 42},
        {3, 43},
        {3, 44},
        {3, 45},
        {3, 46},
        {3, 47},
        {3, 48},
        {3, 49},
        {3, 50},
        {3, 51},
        {3, 52},
        {3, 53},
        {3, 54},
        {3, 55},
        {3, 56},
        {3, 57},
        {3, 58},
        {3, 59},
        {3, 60},
        {3, 61},
        {4, 39},
        {4, 40},
        {4, 41},
        {4, 42},
        {4, 43},
        {4, 44},
        {4, 45},
        {4, 46},
        {4, 47},
        {4, 48},
        {4, 49},
        {4, 50},
        {4, 51},
        {4, 52},
        {4, 53},
        {4, 54},
        {4, 55},
        {4, 56},
        {4, 57},
        {4, 58},
        {4, 59},
        {4, 60},
        {4, 61},
        {5, 39},
        {5, 40},
        {5, 41},
        {5, 42},
        {5, 43},
        {5, 44},
        {5, 45},
        {5, 46},
        {5, 47},
        {5, 48},
        {5, 49},
        {5, 50},
        {5, 51},
        {5, 52},
        {5, 53},
        {5, 54},
        {5, 55},
        {5, 56},
        {5, 57},
        {5, 58},
        {5, 59},
        {5, 60},
        {5, 61},
        {5, 62},
        {5, 63},
        {5, 64},
        {5, 65},
        {5, 66},
        {5, 67},
        {5, 68},
        {5, 69},
        {6, 39},
        {6, 40},
        {6, 41},
        {6, 42},
        {6, 43},
        {6, 44},
        {6, 45},
        {6, 46},
        {6, 47},
        {6, 48},
        {6, 49},
        {6, 50},
        {6, 51},
        {6, 52},
        {6, 53},
        {6, 54},
        {6, 55},
        {6, 56},
        {6, 57},
        {6, 58},
        {6, 59},
        {6, 60},
        {6, 61},
        {6, 62},
        {6, 63},
        {6, 64},
        {6, 65},
        {6, 66},
        {6, 67},
        {6, 68},
        {6, 69},
        {6, 70},
        {6, 71},
        {6, 72},
        {7, 61},
        {7, 62},
        {7, 63},
        {7, 64},
        {7, 65},
        {7, 66},
        {7, 67},
        {7, 68},
        {7, 69},
        {7, 70},
        {7, 71},
        {7, 72},
        {7, 73},
        {7, 74},
        {7, 75},
        {8, 61},
        {8, 62},
        {8, 63},
        {8, 64},
        {8, 65},
        {8, 66},
        {8, 67},
        {8, 68},
        {8, 69},
        {8, 70},
        {8, 71},
        {8, 72},
        {8, 73},
        {8, 74},
        {8, 75},
        {9, 61},
        {9, 62},
        {9, 63},
        {9, 64},
        {9, 65},
        {9, 66},
        {9, 67},
        {9, 68},
        {9, 69},
        {9, 70},
        {9, 71},
        {9, 72},
        {9, 73},
        {9, 74},
        {9, 75},
        {10, 61},
        {10, 62},
        {10, 63},
        {10, 64},
        {10, 65},
        {10, 66},
        {10, 67},
        {10, 68},
        {10, 69},
        {10, 70},
        {10, 71},
        {10, 72},
        {10, 73},
        {10, 74},
        {10, 75},
        {11, 61},
        {11, 62},
        {11, 63},
        {11, 64},
        {11, 65},
        {11, 66},
        {11, 67},
        {11, 68},
        {11, 69},
        {11, 70},
        {11, 71},
        {11, 72},
        {11, 73},
        {11, 74},
        {11, 75},
        {12, 61},
        {12, 62},
        {12, 63},
        {12, 64},
        {12, 65},
        {12, 66},
        {12, 67},
        {12, 68},
        {12, 69},
        {12, 70},
        {12, 71},
        {12, 72},
        {12, 73},
        {12, 74},
        {12, 75},
    },
    {
        // Room 2, middle small room
        {10, 38},
        {10, 39},
        {10, 40},
        {10, 41},
        {10, 42},
        {10, 43},
        {10, 44},
        {10, 45},
        {10, 46},
        {10, 47},
        {10, 48},
        {10, 49},
        {11, 38},
        {11, 39},
        {11, 40},
        {11, 41},
        {11, 42},
        {11, 43},
        {11, 44},
        {11, 45},
        {11, 46},
        {11, 47},
        {11, 48},
        {11, 49},
        {12, 38},
        {12, 39},
        {12, 40},
        {12, 41},
        {12, 42},
        {12, 43},
        {12, 44},
        {12, 45},
        {12, 46},
        {12, 47},
        {12, 48},
        {12, 49},
    },
    {
        // Room 3, Bottom left room
        {15, 4},
        {15, 5},
        {15, 6},
        {15, 7},
        {15, 8},
        {15, 9},
        {15, 10},
        {15, 11},
        {15, 12},
        {15, 13},
        {15, 14},
        {15, 15},
        {15, 16},
        {15, 17},
        {15, 18},
        {15, 19},
        {15, 20},
        {15, 21},
        {15, 22},
        {15, 23},
        {15, 24},
        {16, 4},
        {16, 5},
        {16, 6},
        {16, 7},
        {16, 8},
        {16, 9},
        {16, 10},
        {16, 11},
        {16, 12},
        {16, 13},
        {16, 14},
        {16, 15},
        {16, 16},
        {16, 17},
        {16, 18},
        {16, 19},
        {16, 20},
        {16, 21},
        {16, 22},
        {16, 23},
        {16, 24},
        {17, 4},
        {17, 5},
        {17, 6},
        {17, 7},
        {17, 8},
        {17, 9},
        {17, 10},
        {17, 11},
        {17, 12},
        {17, 13},
        {17, 14},
        {17, 15},
        {17, 16},
        {17, 17},
        {17, 18},
        {17, 19},
        {17, 20},
        {17, 21},
        {17, 22},
        {17, 23},
        {17, 24},
        {18, 4},
        {18, 5},
        {18, 6},
        {18, 7},
        {18, 8},
        {18, 9},
        {18, 10},
        {18, 11},
        {18, 12},
        {18, 13},
        {18, 14},
        {18, 15},
        {18, 16},
        {18, 17},
        {18, 18},
        {18, 19},
        {18, 20},
        {18, 21},
        {18, 22},
        {18, 23},
        {18, 24},
        {19, 4},
        {19, 5},
        {19, 6},
        {19, 7},
        {19, 8},
        {19, 9},
        {19, 10},
        {19, 11},
        {19, 12},
        {19, 13},
        {19, 14},
        {19, 15},
        {19, 16},
        {19, 17},
        {19, 18},
        {19, 19},
        {19, 20},
        {19, 21},
        {19, 22},
        {19, 23},
        {19, 24},
        {20, 4},
        {20, 5},
        {20, 6},
        {20, 7},
        {20, 8},
        {20, 9},
        {20, 10},
        {20, 11},
        {20, 12},
        {20, 13},
        {20, 14},
        {20, 15},
        {20, 16},
        {20, 17},
        {20, 18},
        {20, 19},
        {20, 20},
        {20, 21},
        {20, 22},
        {20, 23},
        {20, 24},
        {21, 4},
        {21, 5},
        {21, 6},
        {21, 7},
        {21, 8},
        {21, 9},
        {21, 10},
        {21, 11},
        {21, 12},
        {21, 13},
        {21, 14},
        {21, 15},
        {21, 16},
        {21, 17},
        {21, 18},
        {21, 19},
        {21, 20},
        {21, 21},
        {21, 22},
        {21, 23},
        {21, 24},
    },
    {
        // Room 5, bottom right room
        {16, 65},
        {16, 66},
        {16, 67},
        {16, 68},
        {16, 69},
        {16, 70},
        {16, 71},
        {16, 72},
        {16, 73},
        {16, 74},
        {16, 75},
        {17, 65},
        {17, 66},
        {17, 67},
        {17, 68},
        {17, 69},
        {17, 70},
        {17, 71},
        {17, 72},
        {17, 73},
        {17, 74},
        {17, 75},
        {18, 65},
        {18, 66},
        {18, 67},
        {18, 68},
        {18, 69},
        {18, 70},
        {18, 71},
        {18, 72},
        {18, 73},
        {18, 74},
        {18, 75},
        {19, 37},
        {19, 38},
        {19, 39},
        {19, 40},
        {19, 41},
        {19, 42},
        {19, 43},
        {19, 44},
        {19, 45},
        {19, 46},
        {19, 47},
        {19, 48},
        {19, 49},
        {19, 50},
        {19, 51},
        {19, 52},
        {19, 53},
        {19, 54},
        {19, 55},
        {19, 56},
        {19, 57},
        {19, 58},
        {19, 59},
        {19, 60},
        {19, 61},
        {19, 62},
        {19, 63},
        {19, 64},
        {19, 65},
        {19, 66},
        {19, 67},
        {19, 68},
        {19, 69},
        {19, 70},
        {19, 71},
        {19, 72},
        {19, 73},
        {19, 74},
        {19, 75},
        {20, 37},
        {20, 38},
        {20, 39},
        {20, 40},
        {20, 41},
        {20, 42},
        {20, 43},
        {20, 44},
        {20, 45},
        {20, 46},
        {20, 47},
        {20, 48},
        {20, 49},
        {20, 50},
        {20, 51},
        {20, 52},
        {20, 53},
        {20, 54},
        {20, 55},
        {20, 56},
        {20, 57},
        {20, 58},
        {20, 59},
        {20, 60},
        {20, 61},
        {20, 62},
        {20, 63},
        {20, 64},
        {20, 65},
        {20, 66},
        {20, 67},
        {20, 68},
        {20, 69},
        {20, 70},
        {20, 71},
        {20, 72},
        {20, 73},
        {20, 74},
        {20, 75},
        {21, 37},
        {21, 38},
        {21, 39},
        {21, 40},
        {21, 41},
        {21, 42},
        {21, 43},
        {21, 44},
        {21, 45},
        {21, 46},
        {21, 47},
        {21, 48},
        {21, 49},
        {21, 50},
        {21, 51},
        {21, 52},
        {21, 53},
        {21, 54},
        {21, 55},
        {21, 56},
        {21, 57},
        {21, 58},
        {21, 59},
        {21, 60},
        {21, 61},
        {21, 62},
        {21, 63},
        {21, 64},
        {21, 65},
        {21, 66},
        {21, 67},
        {21, 68},
        {21, 69},
        {21, 70},
        {21, 71},
        {21, 72},
        {21, 73},
        {21, 74},
        {21, 75},
    }};
