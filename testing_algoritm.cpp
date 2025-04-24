#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random> 
#include <chrono> 

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

bool try_place_ship(int play_zone[7][9], Ship* current) {
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 9; y++) {

            if (!is_valid(&play_zone[x][y]) || has_nearby_ship(x, y, play_zone)) {
                continue;
            }

            int length = 0;
            Ship* temp = current;
            while (temp != nullptr) {
                length++;
                temp = temp->next;
            }

            bool can_place_vertically = true;
            for (int i = 0; i < length; ++i) {

                int xi = x + i;
                if (xi >= 7 || !is_inside_zone(xi, y) || !is_valid(&play_zone[xi][y]) || has_nearby_ship(xi, y, play_zone)) {
                    can_place_vertically = false;
                    break;
                }
            }

            if (can_place_vertically) {

                Ship* cursor = current;
                for (int i = 0; i < length; ++i) {
                    play_zone[x + i][y] = cursor->data;
                    cursor = cursor->next;
                }
                return true;
            }

            bool can_place_horizontally = true;
            for (int i = 0; i < length; ++i) {

                int yi = y + i;
                if (yi >= 9 || !is_inside_zone(x, yi) || !is_valid(&play_zone[x][yi]) || has_nearby_ship(x, yi, play_zone)) {
                    can_place_horizontally = false;
                    break;
                }
            }

            if (can_place_horizontally) {

                Ship* cursor = current;
                for (int i = 0; i < length; ++i) {
                    play_zone[x][y + i] = cursor->data;
                    cursor = cursor->next;
                }
                return true;
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

        if (try_place_ship(play_zone, current)) {
            ship_index++; 
        } else {
            break;
        }
    }
    
}
bool try_all_random_permutations(ship_vector& ship_list, int play_zone[7][9]) {
    vector<int> lengths;
    for (Linked_ships* ship : ship_list) {
        lengths.push_back(ship->get_data());
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 rng(seed);

    int attempts = 0;

    while (true) {
        shuffle(lengths.begin(), lengths.end(), rng);
        ship_vector permuted;

        for (int len : lengths) {
            permuted.push_back(new Linked_ships(len));
        }

        int temp_zone[7][9];
        copy_zone(play_zone, temp_zone);

        bool success = true;
        for (Linked_ships* ship : permuted) {
            if (!try_place_ship(temp_zone, ship->get_head())) {
                success = false;
                break;
            }
        }

        attempts++;

        if (success) {
            copy_zone(temp_zone, play_zone);
            cout << "\nSolution found in " << attempts << " attempts:" << endl;
            for (int len : lengths) {
                cout << len << " ";
            }
            cout << "\n";
            for (Linked_ships* sh : permuted) delete sh;
            return true;
        }

        for (Linked_ships* sh : permuted) delete sh;
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
    
    cout << endl;

    print(play_zone);
    cout << endl;

    for (int i = 0; i < 5; i++) {
        int temp_zone[7][9]; 
        copy_zone(play_zone, temp_zone);
    
        cout << "Attempt " << i + 1 << ":\n";
        if (try_all_random_permutations(ship_list, temp_zone)) {
            cout << "EXCELLENT" << endl;
        } else {
            cout << "ERROR." << endl;
        }
    
        print(temp_zone);
        cout << endl; 
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