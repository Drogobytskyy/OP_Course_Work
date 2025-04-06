#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "start_instruction.h"

#define UP_BOT 75
#define first_last '|'

using namespace std;

void up_bot_fill(){
    cout << " ";
    for(int i = 0; i < UP_BOT - 1; i++){
        cout << "-";
    }
    cout << " ";
    cout << endl;
}

void controlled_output(const string s){
    int space_betw = (UP_BOT - s.length() - 1) / 2;

    int totalLength = (space_betw * 2) + s.length() + 1;

    // corecting table for text with uni code(approximately equal sing)
    if(s.find("\u2248") != string::npos){
        space_betw = space_betw + 1;
    }

    // corecting table for text with color change
    if(s.find("[0m") != string::npos){

        space_betw = space_betw + 4;
        cout << first_last << string(space_betw, ' ') << s << string(space_betw + 1, ' ') << first_last;

    }else if(totalLength != 75){

        if(totalLength > 75){
            cout << first_last << string(space_betw, ' ') << s << string(space_betw - 1, ' ') << first_last;
        }else{
            cout << first_last << string(space_betw, ' ') << s << string(space_betw + 1, ' ') << first_last;
        }
        
    }else{
        cout << first_last << string(space_betw, ' ') << s << string(space_betw, ' ') << first_last;
    }

    cout << endl;
}

void start_tabel(){

    // strings that will be displayed
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
    const string first_message[] = {s1,s2,s3,s4,s5,s6,s7};
    const string second_message[] = {s8,s9};
    const string third_message[] = {s10,s11,s12};

    up_bot_fill();

    // first text to show
    for(int i = 0; i < sizeof(first_message) / sizeof(first_message[0]); i++){
        controlled_output(first_message[i]);
    }
    up_bot_fill();

    // second text to show
    for(int i = 0; i < sizeof(second_message) / sizeof(second_message[0]); i++){
        controlled_output(second_message[i]);
    }

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

    // displaying ships
    for(int i = 0; i < ships.size(); i++){
        for (int j = 0; j < ships[i].size(); j++) {
            controlled_output(ships[i][j]);
        }
    }

    // third text to show
    for(int i = 0; i < sizeof(third_message) / sizeof(third_message[0]); i++){
        controlled_output(third_message[i]);
    }
    
    // squares yes and no
    vector<string> yes_square;
    yes_square.push_back("\033[32m*****   -------------\033[0m");
    yes_square.push_back("\033[32m|   | - Can be placed\033[0m");
    yes_square.push_back("\033[32m*****   -------------\033[0m");

    vector<string> no_square;
    no_square.push_back("\033[31m*****   -----------------\033[0m");
    no_square.push_back("\033[31m| \u2248 | - against the rules\033[0m");
    no_square.push_back("\033[31m*****   -----------------\033[0m");

    vector<vector<string> > squares;
    squares.push_back(yes_square);
    squares.push_back(no_square);

    // squares showing
    for(int i = 0; i < squares.size(); i++){
        for (int j = 0; j < squares[i].size(); j++) {
            controlled_output(squares[i][j]);
        }
    }
    up_bot_fill();
}
