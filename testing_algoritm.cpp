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

    for(int i = 0; i < 7; i++){
        cout << endl;
        for(int j = 0; j < 9; j++){
            if(play_zone[i][j] == SPECIAL){
                cout << "  -  "; 
            }else{
                cout << "  " << play_zone[i][j] << "  ";
            }

        }
        cout << endl;
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


        int get_data() const {
            return head ? head->data : -1;
        }

        Ship* get_head() const {
            return head;
        }
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

// check if INSIDE
bool is_inside_zone(int x, int y) {
    return x >= 0 && x < 7 && y >= 0 && y < 9;
}

// check if VALID
bool is_valid(int *zone){
    return *zone == VALID;
}
// check if SHIP
bool is_ship(int *zone){
    return *zone != VALID && *zone != INVALID && *zone !=SPECIAL;
}

bool has_nearby_ship(int x, int y, int play_zone[7][9]) {
    int dx[] = {-1, -1, -1,  0, 0, 1, 1, 1};
    int dy[] = {-1,  0,  1, -1, 1,-1, 0, 1};

    for (int dir = 0; dir < 8; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (is_inside_zone(nx, ny) && is_ship(&play_zone[nx][ny])) {
            return true;
        }
    }
    return false;
}

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

    print(play_zone);
    cout << endl;

    int ship_index = 0;
    Ship* current = ship_list[ship_index]->get_head();



    for(int x = 0; x < 7; x++){
        for(int y = 0; y < 9; y++){

            if(current != nullptr){
                if(is_valid(&play_zone[x][y]) && !has_nearby_ship(x, y, play_zone)){
                    play_zone[x][y] = current->data;
                    current = current->next;

                    if (current == nullptr && ship_index + 1 < (int)ship_list.size()) {
                        ship_index++;
                        current = ship_list[ship_index]->get_head();  
                    }

                }else{
                    continue;
                }


            }


        }
    }
    cout << endl;

    print(play_zone);

    // ships deleting
    for (Linked_ships* sh : ship_list) {
        delete sh;
    }

    cout << endl;
    return 0;
}