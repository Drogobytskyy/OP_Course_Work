#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <vector>

#define VALID 9
#define INVALID 0 
#define SPECIAL -1

using namespace std;


int play_zone[7][9] = {
    { INVALID, INVALID, VALID, INVALID, VALID, INVALID, INVALID, INVALID, INVALID },
    { VALID, VALID, VALID, INVALID, VALID, INVALID, VALID, VALID, VALID },
    { INVALID, VALID, VALID, VALID, VALID, INVALID, VALID, VALID, VALID },
    { VALID, VALID, SPECIAL, VALID, VALID, VALID, VALID, VALID, INVALID },
    { VALID, VALID, VALID, VALID, VALID, VALID, VALID, VALID, INVALID },
    { INVALID, VALID, VALID, VALID, VALID, VALID, INVALID, INVALID, INVALID },
    { INVALID, VALID, VALID, VALID, INVALID, INVALID, INVALID, INVALID, INVALID,}
};

void print(int play_zone[7][9]){

    for (int i = 0; i < 7; i++){
        cout << "\n";
        for(int j = 0; j < 9; j++){
            if(play_zone[i][j] == 1){
                cout << " ";
                cout << "1 ";
            }else if(play_zone[i][j] == -1){
                cout << " ";
                cout << "3 ";
            }else{
                cout << " ";
                cout << "0 ";
            }
        }
    }
}

struct Ship{
    int data;
    Ship *next;
};



class Linked_ships{
    Ship *head;

    public:
        Linked_ships(int n) {
            head = nullptr;

            for(int i = 0; i < n; i++){

                Ship *newShip = new Ship();
                newShip->data = n;
                newShip->next = head;
                head = newShip;
            }
        }

        ~Linked_ships(){
            Ship *current = head;

            while(current){
                Ship* temp = current;
                current = current->next;
                delete temp;
            }

            cout << "destructor have worked" << endl;
        }

        void show_ship();

};

void Linked_ships::show_ship(){
    Ship *current = head;
    while(current){
        cout << current->data;  
        current = current->next;
        if(current){
            cout << " - ";
        }
    }
    cout << endl;
}

typedef vector<Linked_ships*> ship_vector;

int main(void){
    cout << endl;
    ship_vector ship_list;

    ship_list.push_back(new Linked_ships(4));
    ship_list.push_back(new Linked_ships(3));
    ship_list.push_back(new Linked_ships(3));
    ship_list.push_back(new Linked_ships(2));
    ship_list.push_back(new Linked_ships(2));
    ship_list.push_back(new Linked_ships(2));
    ship_list.push_back(new Linked_ships(1));
    ship_list.push_back(new Linked_ships(1));
    ship_list.push_back(new Linked_ships(1));
    ship_list.push_back(new Linked_ships(1));

    // ships output
    for(Linked_ships *sh : ship_list){
        sh->show_ship();
    }

    cout << endl;

    // ships deleting
    for (Linked_ships* sh : ship_list) {
        delete sh;
    }

    cout << endl;
    return 0;
}