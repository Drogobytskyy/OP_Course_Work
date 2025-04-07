#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include "start_instruction.h"

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
    instruction.show();  
    
    string choice = get_valid_input(instruction);

    if(choice == "1" || choice == "start"){
        instruction.clear_screen();
        instruction.custom_message("Let's start!");
        instruction.custom_only_text("So, let's look what field do we have!");
        instruction.up_and_bot();
    }else{
        instruction.custom_message("Goodbye! Hope we will meet again!");
        return 0;
    }
    cout << endl;
    return 0;
}
