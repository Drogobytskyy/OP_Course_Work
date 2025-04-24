#include "globals.h"
#include "ship_struct.h"
#include "game_zone.h"

using namespace std;


int main(void){
    cout << endl;
    Game g;
    cout << endl;

    g.print(g_play_zone);
    cout << endl;

    int temp_zone[7][9]; 
    g.copy_zone(g_play_zone, temp_zone);

    int ships_placed_count = 0;

    if (g.place_all_ships(temp_zone, g.ship_list, 0, ships_placed_count)) {
        cout << "Ships placed successfully!" << endl;
    } else {
        cout << "ERROR." << endl;
    }

    g.print(temp_zone);
    cout << "Total ships placed: " << g.get_ship_placing_counter() << endl;
    cout << "Total ships deleted: " << g.get_ship_deleting_counter() << endl;
    cout << endl;


    cout << endl;
    return 0;
}


