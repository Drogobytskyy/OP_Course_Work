#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "start_instruction.h"
#include "globals.h"
#include "ship_struct.h"
#include "game.h"

using namespace std;
using namespace chrono;

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

void processing_time_spend(){
    cout << "Loading";
    for (int i = 0; i < 5; ++i) {
        cout << "."; 
        cout.flush();     
        this_thread::sleep_for(chrono::seconds(1)); 
    }
}

int main(void) {
    cout << endl;

    auto start_time = high_resolution_clock::now();

    Start_instruction instruction;
    Game game;

    instruction.show();  
    instruction.up_and_bot();

    instruction.custom_only_text("If you undestood everything do you want to start?");
    instruction.custom_only_text("Type: (1) or \"start\" | (2) or \"exit\"");

    instruction.up_and_bot();

    string choice = get_valid_input(instruction);

    if(choice == "1" || choice == "start"){
        instruction.clear_screen();

        instruction.custom_message("Let's start!");
        instruction.custom_only_text("So, let's look what field do we have!");

        instruction.up_and_bot();

        game.print_start_zone(g_play_zone, instruction);

        while(true){
            instruction.custom_only_text("Did you understand the rules?");
            instruction.up_and_bot();

            instruction.custom_only_text("If you undestood everything do you want to start?");
            instruction.custom_only_text("Type: (1) or \"start\" | (2) or \"exit\"");

            instruction.up_and_bot();

            string choice_to_continue = get_valid_input(instruction);

            if(choice_to_continue == "1" || choice == "start"){

                instruction.custom_message("So program starts and need some time");
                break;

            }else if(choice_to_continue == "exit"){

                instruction.custom_message("Goodbye! Hope we will meet again!");
                exit(1);
            }else{
                instruction.clear_screen();
                instruction.show();
            }
        }

        int temp_zone[7][9]; 
        game.copy_zone(g_play_zone, temp_zone);
        int ships_placed_count = 0;

        if (game.place_all_ships(temp_zone, game.ship_list, 0, ships_placed_count)) {

            processing_time_spend();
            cout << " \033[32m Ships placed successfully!\033[0m" << endl;

            processing_time_spend();
            instruction.clear_screen();
            instruction.custom_message("Now you can see the result!");
            game.print_final_zone(temp_zone, instruction);

            instruction.custom_message("And final EXTRA informations:");
            int placed = game.get_ship_placing_counter();
            int deleted = game.get_ship_deleting_counter();

            instruction.custom_only_text("By the time algoritm worked");
            instruction.custom_only_text("Total ships was placed: " + to_string(placed));
            instruction.custom_only_text("Total ships was removed: " + to_string(deleted));

            auto end_time = high_resolution_clock::now();
            auto duration = duration_cast<seconds>(end_time - start_time);
            instruction.custom_only_text("Program worked for: " + to_string(duration.count()) + " seconds");
            instruction.up_and_bot();
            
        } else {
            cout << "ERROR." << endl;
        }
        
    }else{
        instruction.custom_message("Goodbye! Hope we will meet again!");
        return 0;
    }

    cout << endl;
    return 0;
}
