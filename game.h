#ifndef GAME_H
#define GAME_H

#include "game_zone.h"


/* ----------------------------------------------------------------------[<]-
    Class: Game

    Synopsis: this header contains all the logic of the programm.
              The algorithm and everything for him.
              Also this class initilizes friend class for testing algorithm.
    ---------------------------------------------------------------------[>]-*/

class Game : public Game_zone{
    private:
        friend class GameTest;
        bool remove_ship(int play_zone[7][9], Linked_ships* ship, int x, int y, bool vertical, int &ships_placed_count);
        bool place_ship_if_possible(int play_zone[7][9], Linked_ships* ship, int x, int y, bool vertical, int &ships_placed_count);

    public:
        ship_vector ship_list;
        ship_vector& get_ship_list() { return ship_list; }
        Game();
        ~Game();
        bool place_all_ships(int play_zone[7][9], ship_vector& ship_list, int idx, int &ships_placed_count);

};


#endif
