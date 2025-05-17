/* -----------------------------------------------------<Header>-

Name: task2.cpp
Title: place ships in the field

Group: TB-41
Student: Drogobytskyy V.Y.
Written: 14.05.2025
Revised: 18.05.2025

Description: Write a programm that places all the ships
            in field with non standart form. Also it 
            has to solve this task with some specific
            rules. The main thing is that: ships can`t 
            touch each other even diagonally in the cornenrs.
            One more rule is that we can`t place ship in the box
            with approximately equal sing.

 -----------------------------------------------------<Header>-*/



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

/* ----------------------------------------------------------------------[<]-
    Function: is_valid_input 
    Synopsis: function return true only in right
    and valid input, and are used just like a small helpful
    part in another system.
    ---------------------------------------------------------------------[>]-*/

bool is_valid_input(const string& input) {
    return input == "1" || input == "start" || input == "2" || input == "exit";
}

/*
    name of the function talks by itself
*/
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

// just making the view of working
void processing_time_spend(){
    cout << "Loading";
    for (int i = 0; i < 5; ++i) {
        cout << "."; 
        cout.flush();     
        this_thread::sleep_for(chrono::seconds(1)); 
    }
}

/*
    the main block of programm like a heart of the whole mechanism.
*/
int main(void) {
    cout << endl;

    auto start_time = high_resolution_clock::now();

    Start_instruction instruction;
    Game game;

    instruction.show();  
    instruction.up_bottom_fill();

    instruction.custom_only_text("If you undestood everything do you want to start?");
    instruction.custom_only_text("Type: (1) or \"start\" | (2) or \"exit\"");

    instruction.up_bottom_fill();

    string choice = get_valid_input(instruction);

    // starting from here
    if(choice == "1" || choice == "start"){
        instruction.clear_screen();

        instruction.custom_message("Let's start!");
        instruction.custom_only_text("So, let's look what field do we have!");

        instruction.up_bottom_fill();

        game.print_start_zone(g_play_zone, instruction);

        while(true){
            instruction.up_bottom_fill();
            instruction.custom_only_text("Did you understand the rules?");
            instruction.up_bottom_fill();

            instruction.custom_only_text("If you undestood everything do you want to start?");
            instruction.custom_only_text("Type: (1) or \"start\" | (2) - to see instructin again or \"exit\"");

            instruction.up_bottom_fill();

            string choice_to_continue = get_valid_input(instruction);

            // under if creating posibillity to swap instruction and field

            if(choice_to_continue == "1" || choice_to_continue == "start"){

                instruction.custom_message("So program starts and need some time");
                break;

            }else if(choice_to_continue == "exit"){

                instruction.custom_message("Goodbye! Hope we will meet again!");
                exit(1);
            }else{
                instruction.clear_screen();
                instruction.show();
                instruction.custom_only_text("If you undestood everything do you want to start?");
                instruction.custom_only_text("Type: (1) or \"start\" | (2) - to see field again or \"exit\"");
                instruction.up_bottom_fill();

                string choice_of_choices = get_valid_input(instruction);

                if(choice_of_choices == "2"){

                    instruction.clear_screen();
                    instruction.up_bottom_fill();
                    instruction.custom_only_text("So, let's look what field do we have!");
                    game.print_start_zone(g_play_zone, instruction);

                }else if(choice_of_choices == "exit"){

                    instruction.custom_message("Goodbye! Hope we will meet again!");
                    exit(1);
                }else{
                    break;
                }
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

            instruction.custom_message("EXTRA informations:");
            int placed = game.get_ship_placing_counter();
            int deleted = game.get_ship_deleting_counter();

            // extra informations
            instruction.custom_only_text("By the time algoritm worked");
            instruction.custom_only_text("Total ships was placed: " + to_string(placed));
            instruction.custom_only_text("Total ships was removed: " + to_string(deleted));

            auto end_time = high_resolution_clock::now();
            auto duration = duration_cast<seconds>(end_time - start_time);
            instruction.custom_only_text("Program worked for: " + to_string(duration.count()) + " seconds");
            instruction.up_bottom_fill();
            
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
