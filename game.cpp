#include "game.h"

// initalizating of ships
Game :: Game() : Game_zone(){
    
    ship_list = {
        new Linked_ships(4),
        new Linked_ships(3), new Linked_ships(3),
        new Linked_ships(2), new Linked_ships(2), new Linked_ships(2),
        new Linked_ships(1), new Linked_ships(1), new Linked_ships(1), new Linked_ships(1)
    };
}

// destructing all ships
Game :: ~Game() {
    for (Linked_ships* sh : ship_list) {
        delete sh;
    }
    ship_list.clear(); 
}

/* ----------------------------------------------------------------------[<]-
    Function: remove_ship 
    Synopsis: function for deleting already placed ship from the field,
              if there is such need. It works when we have to come back
              and delete the wrong placed ship.
    ---------------------------------------------------------------------[>]-*/

bool Game :: remove_ship(int play_zone[7][9], Linked_ships* ship, int x, int y, bool vertical, int &ships_placed_count) {
    int length = ship->get_data();

    if (vertical) {
        for (int i = 0; i < length; ++i) {
            play_zone[x + i][y] = VALID;
        }
    } else {
        for (int i = 0; i < length; ++i) {
            play_zone[x][y + i] = VALID;
        }
    }
   
    ships_placed_count--;
    increment_ship_deleting_counter();

    return true;
}

/* ----------------------------------------------------------------------[<]-
    Function: place_ship_if_possible 
    Synopsis: function for placing ships in the field. It checks is it
              possible starts from vertical and finish with horizontal
              ship rotations.
    ---------------------------------------------------------------------[>]-*/

bool Game :: place_ship_if_possible(int play_zone[7][9], Linked_ships* ship, int x, int y, bool vertical, int &ships_placed_count) {
    int length = ship->get_data();
    
    if (vertical) {
        if (x + length > 7) {
            return false;
        }
        
        for (int i = 0; i < length; ++i) {
            if (!is_valid(&play_zone[x + i][y]) || has_nearby_ship(x + i, y, play_zone)) {
                return false;
            }
        }

        for (int i = 0; i < length; ++i) {
            play_zone[x + i][y] = ship->get_data();
        }
        
        ships_placed_count++;

        return true;

    } else {

        if (y + length > 9) {
            return false;
        }

        for (int i = 0; i < length; ++i) {
            if (!is_valid(&play_zone[x][y + i]) || has_nearby_ship(x, y + i, play_zone)) {
                return false;
            }
        }

        for (int i = 0; i < length; ++i) {
            play_zone[x][y + i] = ship->get_data();
        }
        
        ships_placed_count++;

        return true;
    }
}

/* ----------------------------------------------------------------------[<]-
    Function: place_all_ships 
    Synopsis: the heart of algorithm. It is representing of back-tracking
              way to find the right solution. This function works like a 
              recursive mechanism and works until the solution is fined.
    ---------------------------------------------------------------------[>]-*/

bool Game :: place_all_ships(int play_zone[7][9], ship_vector& ship_list, int idx, int &ships_placed_count) {
    if (idx == (int)ship_list.size()) return true;

    Linked_ships* ship = ship_list[idx];
    
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 9; y++) {

            if (place_ship_if_possible(play_zone, ship, x, y, true, ships_placed_count)) {

                increment_ship_placing_counter();

                if (place_all_ships(play_zone, ship_list, idx + 1, ships_placed_count)) {
                    return true;
                }
                remove_ship(play_zone, ship, x, y, true, ships_placed_count);
            }

            if (place_ship_if_possible(play_zone, ship, x, y, false, ships_placed_count)) {

                increment_ship_placing_counter();

                if (place_all_ships(play_zone, ship_list, idx + 1, ships_placed_count)) {
                    return true;
                }
                remove_ship(play_zone, ship, x, y, false, ships_placed_count);
            }
        }
    }

    return false;
}