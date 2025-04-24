#include "globals.h"
#include "ship_struct.h"
#include "game_zone.h"

using namespace std;


typedef vector<Linked_ships*> ship_vector;


bool place_ship_if_possible(Game_zone& g, int play_zone[7][9], Linked_ships* ship, int x, int y, bool vertical, int &ships_placed_count) {
    int length = ship->get_data();
    
    if (vertical) {
        if (x + length > 7) {
            return false;
        }
        
        for (int i = 0; i < length; ++i) {
            if (!g.is_valid(&play_zone[x + i][y]) || g.has_nearby_ship(x + i, y, play_zone)) {
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
            if (!g.is_valid(&play_zone[x][y + i]) || g.has_nearby_ship(x, y + i, play_zone)) {
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

bool remove_ship(Game_zone& g, int play_zone[7][9], Linked_ships* ship, int x, int y, bool vertical, int &ships_placed_count) {
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
    g.increment_ship_deleting_counter();

    return true;
}

bool place_all_ships(Game_zone& g, int play_zone[7][9], ship_vector& ship_list, int idx, int &ships_placed_count) {
    if (idx == (int)ship_list.size()) return true;

    Linked_ships* ship = ship_list[idx];
    
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 9; y++) {
            if (place_ship_if_possible(g, play_zone, ship, x, y, true, ships_placed_count)) {
                g.increment_ship_placing_counter();
                if (place_all_ships(g, play_zone, ship_list, idx + 1, ships_placed_count)) {
                    return true;
                }
                remove_ship(g, play_zone, ship, x, y, true, ships_placed_count);
            }
            if (place_ship_if_possible(g, play_zone, ship, x, y, false, ships_placed_count)) {
                g.increment_ship_placing_counter();
                if (place_all_ships(g, play_zone, ship_list, idx + 1, ships_placed_count)) {
                    return true;
                }
                remove_ship(g, play_zone, ship, x, y, false, ships_placed_count);
            }
        }
    }

    return false;
}

int main(void){
    cout << endl;
    Game_zone g;
    ship_vector ship_list = {
        new Linked_ships(4),
        new Linked_ships(3), new Linked_ships(3),
        new Linked_ships(2), new Linked_ships(2), new Linked_ships(2),
        new Linked_ships(1), new Linked_ships(1), new Linked_ships(1), new Linked_ships(1)
    };

    cout << endl;

    g.print(g_play_zone);
    cout << endl;

    int temp_zone[7][9]; 
    g.copy_zone(g_play_zone, temp_zone);

    int ships_placed_count = 0;

    if (place_all_ships(g,temp_zone, ship_list, 0, ships_placed_count)) {
        cout << "Ships placed successfully!" << endl;
    } else {
        cout << "ERROR." << endl;
    }

    g.print(temp_zone);
    cout << "Total ships placed: " << g.get_ship_placing_counter() << endl;
    cout << "Total ships deleted: " << g.get_ship_deleting_counter() << endl;
    cout << endl;

    for (Linked_ships* sh : ship_list) {
        delete sh;
    }

    cout << endl;
    return 0;
}


