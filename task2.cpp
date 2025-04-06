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

string get_valid_input() {
    string input;

    while (true) {
        cin >> input;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (is_valid_input(input)) {
            return input;
        } else {
            up_bot_fill();
            controlled_output("Invalid input. Please try again.");
            up_bot_fill();
        }
    }
}

int main(void){
    cout << endl;

    start_tabel();
    const string before_start_text = "If you undestood everything do you want to start?";
    controlled_output(before_start_text);
    const string start_or_not = "Type: (1) or \"start\" | (2) or \"exit\"";
    controlled_output(start_or_not);
    up_bot_fill();
    
    string choice = get_valid_input();
    if(choice == "1" || choice == "start"){
        //
    }else{
        up_bot_fill();
        controlled_output("Goodbye! Hope we will meet again!");
        up_bot_fill();
        return 0;
    }

    cout << endl;
    return 0;
}