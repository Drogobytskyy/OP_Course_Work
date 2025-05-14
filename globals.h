#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>

/*
    some globals variables
*/

// enum for representing field
enum g_CellState {
    INVALID = 0,
    SPECIAL = 7,
    VALID = 9
};

extern int g_play_zone[7][9];

extern std::vector<std::string> vec_st_zone;

#endif