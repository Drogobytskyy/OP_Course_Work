#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>
#include <cstdlib>

#include "start_instruction.h"
#include "globals.h"
#include "ship_struct.h"
#include "game_zone.h"

using namespace std;

bool is_valid_input(const string& input) {
    return input == "1" || input == "start" || input == "2" || input == "exit";
}

string get_valid_input(Start_instruction &instruction) {
    string input;

    while (true) {
        cin >> input;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (is_valid_input(input)) {
            return input;
        } else {
            instruction.custom_message("Invalid input. Please try again.");
            
        }
    }
}

int main(void) {
    cout << endl;

    Start_instruction instruction;
    Game game;
    instruction.show();  
    
    string choice = get_valid_input(instruction);

    if(choice == "1" || choice == "start"){
        instruction.clear_screen();
        instruction.custom_message("Let's start!");
        instruction.custom_only_text("So, let's look what field do we have!");
        instruction.up_and_bot();

        game.print(g_play_zone, instruction);
        //int temp_zone[7][9]; 
       // game.copy_zone(g_play_zone, temp_zone);
        //int ships_placed_count = 0;
        /*if (game.place_all_ships(temp_zone, game.ship_list, 0, ships_placed_count)) {
            cout << "Ships placed successfully!" << endl;
        } else {
            cout << "ERROR." << endl;
        }
        game.print(temp_zone);
        cout << "Total ships placed: " << game.get_ship_placing_counter() << endl;
        cout << "Total ships deleted: " << game.get_ship_deleting_counter() << endl;
        cout << endl;
        */

    }else{
        instruction.custom_message("Goodbye! Hope we will meet again!");
        return 0;
    }

  

    cout << endl;
    return 0;
}
