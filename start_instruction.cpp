#include "start_instruction.h"

#define WIDTH 75
#define BORDER '|'
using namespace std;

void Start_instruction::up_bottom_fill() {
    cout << " ";
    for (int i = 0; i < WIDTH - 1; ++i) {
        cout << "-";
    }
    cout << "\n";
}

void Start_instruction::controlled_output(const string& s) {

    int space_betw = (WIDTH - s.length() - 1) / 2;
    int totalLength = (space_betw * 2) + s.length() + 1;

    if (s.find("\u2248") != string::npos) {
        space_betw++;
    }

    if (s.find("[0m") != string::npos) {
        space_betw += 4;
        cout << BORDER << string(space_betw, ' ') << s << string(space_betw + 1, ' ') << BORDER;

    }else if (totalLength != WIDTH) {
        if (totalLength > WIDTH)
            cout << BORDER << string(space_betw, ' ') << s << string(space_betw - 1, ' ') << BORDER;
        else
            cout << BORDER << string(space_betw, ' ') << s << string(space_betw + 1, ' ') << BORDER;
            
    }else {
        cout << BORDER << string(space_betw, ' ') << s << string(space_betw, ' ') << BORDER;
    }

    cout << endl;
}

void Start_instruction::show_message_block(const vector<string>& messages) {
    for(int i = 0; i < messages.size(); i++){
        controlled_output(messages[i]);
    }
}

void Start_instruction::custom_message(const string &message){
    up_bottom_fill();
    controlled_output(message);
    up_bottom_fill();
}

void Start_instruction::up_and_bot(){
    up_bottom_fill();
}

void Start_instruction::custom_only_text(const string &message){
    controlled_output(message);
}

void Start_instruction::show_ships() {

    // one-sector ship
    vector<string> one_column_ship;
    one_column_ship.push_back("*****     ----------");
    one_column_ship.push_back("| 1 |  -  four ships");
    one_column_ship.push_back("*****     ----------");

    // two-sector ship
    vector<string> two_column_ship;
    two_column_ship.push_back("*********    -----------");
    two_column_ship.push_back("| 2 | 2 |  - three ships");
    two_column_ship.push_back("*********    -----------");

    // three-sector ship
    vector<string> three_column_ship;
    three_column_ship.push_back("*************    ---------");
    three_column_ship.push_back("| 3 | 3 | 3 |  - two ships");
    three_column_ship.push_back("*************    ---------");

    // four-sector ship
    vector<string> four_column_ship;
    four_column_ship.push_back("*****************    --------");
    four_column_ship.push_back("| 4 | 4 | 4 | 4 |  - one ship");
    four_column_ship.push_back("*****************    --------");

    // all ships
    vector<vector<string> > ships;  
    ships.push_back(one_column_ship);
    ships.push_back(two_column_ship);
    ships.push_back(three_column_ship);
    ships.push_back(four_column_ship);

    for(int i = 0; i < ships.size(); i++){
        show_message_block(ships[i]);
    }
}

void Start_instruction::show_squares() {

    // green square
    vector<string> yes_square;
    yes_square.push_back("\033[32m*****   -------------\033[0m");
    yes_square.push_back("\033[32m|   | - Can be placed\033[0m");
    yes_square.push_back("\033[32m*****   -------------\033[0m");

    // red square
    vector<string> no_square;
    no_square.push_back("\033[31m*****   -----------------\033[0m");
    no_square.push_back("\033[31m| \u2248 | - against the rules\033[0m");
    no_square.push_back("\033[31m*****   -----------------\033[0m");

    // both squares
    vector<vector<string> > squares;
    squares.push_back(yes_square);
    squares.push_back(no_square);

    for (int i = 0; i < squares.size();i++){
        show_message_block(squares[i]);
    }
        
}

void Start_instruction::show() {
    const string s1 = "I welcome you into my coursework project!";
    const string s2 = "We will see the result of task2 solution";
    const string s3 = "Task is to place ships in the right way";
    const string s4 = "And the main task is to:";
    const string s5 = "that the ships don`t collide even diagonally at the corners";
    const string s6 = "*** Extra condition ***";
    const string s7 = "So ships CAN`T be placed into square with approximately equal sign";
    const string s8 = "Let`s look what we have in our game:";
    const string s9 = "Ships:";
    const string s10 = "Also we have approximately equal sing:";
    const string s11 = "\u2248";
    const string s12 = "We cant place ship into square with this sign!";
    const string s13 = "If you undestood everything do you want to start?";
    const string s14 = "Type: (1) or \"start\" | (2) or \"exit\"";

    // vector of first part
    vector<string> first_message;
    first_message.push_back(s1);
    first_message.push_back(s2);
    first_message.push_back(s3);
    first_message.push_back(s4);
    first_message.push_back(s5);
    first_message.push_back(s6);
    first_message.push_back(s7);

    // vector of second part
    vector<string> second_message;
    second_message.push_back(s8);
    second_message.push_back(s9);
    
    // vector of third part
    vector<string> third_message;
    third_message.push_back(s10);
    third_message.push_back(s11);
    third_message.push_back(s12);

    // vector of fourth part
    vector<string> fourth_message;
    fourth_message.push_back(s13);
    fourth_message.push_back(s14);

    up_bottom_fill();
    show_message_block(first_message);
    up_bottom_fill();
    show_message_block(second_message);
    show_ships();
    show_message_block(third_message);
    show_squares();
    up_bottom_fill();
    show_message_block(fourth_message);
    up_bottom_fill();

}
