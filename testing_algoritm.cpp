#include <iostream>

#define VALID 1
#define INVALID 0 
#define SPECIAL -1

using namespace std;


// only zone was creating
//  [9][7]
int main(void){
    cout << endl;

    int play_zone[7][9] = {
        { INVALID, INVALID, VALID, INVALID, VALID, INVALID, INVALID, INVALID, INVALID },
        { VALID, VALID, VALID, INVALID, VALID, INVALID, VALID, VALID, VALID },
        { INVALID, VALID, VALID, VALID, VALID, INVALID, VALID, VALID, VALID },
        { VALID, VALID, SPECIAL, VALID, VALID, VALID, VALID, VALID, INVALID },
        { VALID, VALID, VALID, VALID, VALID, VALID, VALID, VALID, INVALID },
        { INVALID, VALID, VALID, VALID, VALID, VALID, INVALID, INVALID, INVALID },
        { INVALID, VALID, VALID, VALID, INVALID, INVALID, INVALID, INVALID, INVALID,}
    };

    for (int i = 0; i < 7; i++){
        cout << "\n";
        for(int j = 0; j < 9; j++){
            if(play_zone[i][j] == 1){
                cout << "1 ";
            }else if(play_zone[i][j] == -1){
                cout << "3 ";
            }else{
                cout << "0 ";
            }
        }
    }


    cout << endl;
    return 0;
}