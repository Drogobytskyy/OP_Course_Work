#ifndef GAME_ZONE_H
#define GAME_ZONE_H

#include <iostream>
#include "globals.h"

class Game_zone{
    int play_zone[7][9];
    int ship_placing_counter = 0;
    int ship_deleting_counter = 0;

    public:
        Game_zone();
        void print(int play_zone[7][9]);
        void copy_zone(int src[7][9], int dest[7][9]);
        bool is_inside_zone(int x, int y);
        bool is_ship(int *zone);
        bool has_nearby_ship(int x, int y, int play_zone[7][9]);
        bool is_valid(int *zone);
        void increment_ship_placing_counter() { ship_placing_counter++; }
        void increment_ship_deleting_counter() { ship_deleting_counter++; }
        int get_ship_placing_counter() const { return ship_placing_counter; }
        int get_ship_deleting_counter() const { return ship_deleting_counter; }
};



#endif