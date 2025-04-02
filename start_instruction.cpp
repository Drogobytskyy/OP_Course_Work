#include <iostream>
#include <iomanip>
#include <string>
#include "start_instruction.h"

#define UP_BOT 75
#define first_last '|'

using namespace std;

void up_bot_fill(){
    cout << " ";
    for(int i = 0; i < UP_BOT - 1; i++){
        cout << "_";
    }
    cout << " ";
    cout << endl;
}

void controlled_output(const string s){
    double space_betw = (UP_BOT - s.length() - 1) / 2;

    double totalLength = (space_betw * 2) + s.length() + 1;
    if(totalLength != 75){
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
    const string s1 = "I welcome you into my coursework project!";
    const string s2 = "We will see the result of task2 solution";
    const string s3 = "Task is to place ships in the right way";
    const string s4 = "And the main task is to:";
    const string s5 = "that the ships don`t collide even diagonally at the corners";
    const string s6 = "*** Extra condition ***";
    const string s7 = "So ships CAN`T be placed into square with approximately equal sign";
    const string S[] = {s1,s2,s3,s4,s5,s6,s7};
    up_bot_fill();
    for(int i = 0; i < sizeof(S) / sizeof(S[0]); i++){
        controlled_output(S[i]);
    }

    up_bot_fill();

}
