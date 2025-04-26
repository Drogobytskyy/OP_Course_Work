#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>

enum g_CellState {
    INVALID = 0,
    SPECIAL = -1,
    VALID = 9
};

extern int g_play_zone[7][9];

extern std::vector<std::string> vec_st_zone;

#endif