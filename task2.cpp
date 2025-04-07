#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>
#include "start_instruction.h"

using namespace std;

bool is_valid_input(const string& input) {
    return input == "1" || input == "start" || input == "2" || input == "exit";
}

string get_valid_input(StartInstruction &instruction) {
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

    StartInstruction instruction;
    instruction.show();  
    
    string choice = get_valid_input(instruction);

    if(choice == "1" || choice == "start"){
        //
    }else{
        instruction.custom_message("Goodbye! Hope we will meet again!");
        return 0;
    }
    cout << endl;
    return 0;
}
