#include "start_instruction.h"

// we will understang the sceen as a 75 len 
#define WIDTH 75
#define BORDER '|'
using namespace std;

void Start_instruction :: up_bottom_fill() {
    cout << " ";
    for (int i = 0; i < WIDTH - 1; ++i) {
        cout << "\033[33m" << "-" << "\033[0m";
    }
    cout << "\n";
}

// main block for output
void Start_instruction :: controlled_output(const string& text_to_show) {

    try{
        if(text_to_show.length() > 75){
            throw runtime_error("You try to use too long text");
        }
    
        int space_betw = (WIDTH - text_to_show.length() - 1) / 2;
        int totalLength = (space_betw * 2) + text_to_show.length() + 1;

        if (text_to_show.find("\u2248") != string::npos) {
            space_betw++;
        }

        if (text_to_show.find("[0m") != string::npos) {
            space_betw += 4;
            cout << "\033[33m" << BORDER << "\033[0m" << string(space_betw, ' ') << text_to_show << string(space_betw + 1, ' ') << "\033[33m" << BORDER << "\033[0m";

        }else if (totalLength != WIDTH) {
            if (totalLength > WIDTH)
                cout << "\033[33m" << BORDER << "\033[0m" << string(space_betw, ' ') << text_to_show << string(space_betw - 1, ' ') << "\033[33m" << BORDER << "\033[0m";
            else
                cout << "\033[33m" << BORDER << "\033[0m" << string(space_betw, ' ') << text_to_show << string(space_betw + 1, ' ') << "\033[33m" << BORDER << "\033[0m";
                
        }else {
            cout << "\033[33m" << BORDER << "\033[0m" << string(space_betw, ' ') << text_to_show << string(space_betw, ' ') << "\033[33m" << BORDER << "\033[0m";
        }

        cout << endl;
    } catch (const runtime_error& e){
        cerr << "\033[31mError: " << e.what() << "\033[0m" << endl;
    }
}

void Start_instruction :: show_message_block(const vector<string>& messages) {
    for(int i = 0; i < (int)messages.size(); i++){
        controlled_output(messages[i]);
    }
}

// method to print any message in box
void Start_instruction :: custom_message(const string &message){
    up_bottom_fill();
    controlled_output(message);
    up_bottom_fill();
}

void Start_instruction :: up_and_bot(){
    up_bottom_fill();
}

// if we need only specifie a text this help us
void Start_instruction :: custom_only_text(const string &message){
    controlled_output(message);
}

void Start_instruction :: show_ships() {

    // one-sector ship
    vector<string> one_column_ship = {
        "*****     ----------",
        "| 1 |  -  four ships",
        "*****     ----------"
    };

    // two-sector ship
    vector<string> two_column_ship = {
        "*********    -----------",
        "| 2 | 2 |  - three ships",
        "*********    -----------"
    };

    // three-sector ship
    vector<string> three_column_ship = {
        "*************    ---------",
        "| 3 | 3 | 3 |  - two ships",
        "*************    ---------"
    };

    // four-sector ship
    vector<string> four_column_ship = {
        "*****************    --------",
        "| 4 | 4 | 4 | 4 |  - one ship",
        "*****************    --------"
    };

    vector<vector<string> > ships = {
        one_column_ship, two_column_ship, three_column_ship, four_column_ship
    };  

    for(int i = 0; i < (int)ships.size(); i++){
        show_message_block(ships[i]);
    }
}

void Start_instruction :: show_squares() {

    // green square
    vector<string> yes_square = {
        "\033[32m*****   -------------\033[0m",
        "\033[32m|   | - Can be placed\033[0m",
        "\033[32m*****   -------------\033[0m"
    };

    // red square
    vector<string> no_square = {
        "\033[31m*****   -----------------\033[0m",
        "\033[31m| \u2248 | - against the rules\033[0m",
        "\033[31m*****   -----------------\033[0m"
    };
   
    vector<vector<string> > squares = {
        yes_square, no_square
    };

    for (int i = 0; i < (int)squares.size();i++){
        show_message_block(squares[i]);
    }
        
}

void Start_instruction :: show() {
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

    // vector of first part
    vector<string> first_message = {
        s1, s2, s3, s4, s5, s6, s7
    };

    // vector of second part
    vector<string> second_message = {
        s8, s9
    };
    
    // vector of third part
    vector<string> third_message = {
        s10, s11, s12
    };

    up_bottom_fill();
    show_message_block(first_message);
    up_bottom_fill();
    show_message_block(second_message);
    show_ships();
    show_message_block(third_message);
    show_squares();
    up_bottom_fill();

}

