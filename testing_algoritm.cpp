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

void copy_zone(int src[7][9], int dest[7][9]) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            dest[i][j] = src[i][j];
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

bool try_place_ship(int play_zone[7][9], Ship* current, int data) {
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 9; y++) {

            Ship* cursor = current;
            int temp_zone[7][9];
            copy_zone(play_zone, temp_zone);

            if (cursor != nullptr && is_valid(&temp_zone[x][y]) && !has_nearby_ship(x, y, temp_zone)) {
                temp_zone[x][y] = cursor->data;
                cursor = cursor->next;

                if (cursor != nullptr && is_inside_zone(x + 1, y) && is_valid(&temp_zone[x + 1][y]) && temp_zone[x][y] == data) {
                    for (int x2 = x + 1; x2 < 7; x2++) {
                        if (temp_zone[x2][y] == SPECIAL) break;

                        if (is_valid(&temp_zone[x2][y])) {
                            temp_zone[x2][y] = cursor->data;
                            cursor = cursor->next;
                            if (cursor == nullptr) break;
                        }
                    }
                }else if(cursor != nullptr && is_inside_zone(x, y + 1) && is_valid(&temp_zone[x][y + 1]) && temp_zone[x][y] == data){
                    for (int y2 = y + 1; y2 < 9; y2++) {
                        if (temp_zone[x][y2] == SPECIAL) break;

                        if (is_valid(&temp_zone[x][y2])) {
                            temp_zone[x][y2] = cursor->data;
                            cursor = cursor->next;
                            if (cursor == nullptr) break;
                        }
                    }
                }

                

                if (cursor == nullptr) {
                    copy_zone(temp_zone, play_zone);  
                    return true;
                }
            }
        }
    }
    return false;  
}


void place_ships_on_map(int play_zone[7][9], ship_vector &ship_list) {
    int ship_index = 0;
    
    while (ship_index < (int)ship_list.size()) {
        Ship* current = ship_list[ship_index]->get_head();
        int backup_zone[7][9];
        copy_zone(play_zone, backup_zone);

        if (try_place_ship(play_zone, current, current->data)) {
            ship_index++; 
        } else {
            cout << "Retrying placement for ship of size " << current->data << "...\n";
            copy_zone(backup_zone, play_zone); 
            
            break;
        }
    }
}


int main(void){
    cout << endl;
    ship_vector ship_list;

    ship_list.push_back(new Linked_ships(1));
    ship_list.push_back(new Linked_ships(3));
    ship_list.push_back(new Linked_ships(1));
    ship_list.push_back(new Linked_ships(2));
    ship_list.push_back(new Linked_ships(2));
    ship_list.push_back(new Linked_ships(1));
    ship_list.push_back(new Linked_ships(2));
    ship_list.push_back(new Linked_ships(1));
    ship_list.push_back(new Linked_ships(4));
    ship_list.push_back(new Linked_ships(3));


    // ships output
    for(Linked_ships *sh : ship_list){
        sh->show_ship();
    }

    cout << endl;

    print(play_zone);
    cout << endl;

    place_ships_on_map(play_zone, ship_list);

    cout << endl;

    print(play_zone);

    // ships deleting
    for (Linked_ships* sh : ship_list) {
        delete sh;
    }

    cout << endl;
    return 0;
}