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

static int g_ship_placing_counter = 0;
static int g_ship_deleting_counter = 0;

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
        int get_data() const { return head ? head->data : -1; }
        Ship* get_head() const { return head; }
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

bool is_inside_zone(int x, int y) {
    return x >= 0 && x < 7 && y >= 0 && y < 9;
}

bool is_valid(int *zone) {
    return *zone == VALID;
}

bool is_ship(int *zone) {
    return *zone != VALID && *zone != INVALID && *zone != SPECIAL;
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

bool place_ship_if_possible(int play_zone[7][9], Linked_ships* ship, int x, int y, bool vertical, int &ships_placed_count) {
    int length = ship->get_data();
    
    if (vertical) {
        if (x + length > 7) {
            return false;
        }
        
        for (int i = 0; i < length; ++i) {
            if (!is_valid(&play_zone[x + i][y]) || has_nearby_ship(x + i, y, play_zone)) {
                return false;
            }
        }

        for (int i = 0; i < length; ++i) {
            play_zone[x + i][y] = ship->get_data();
        }
        
        ships_placed_count++;
        
        return true;

    } else {

        if (y + length > 9) {
            return false;
        }

        for (int i = 0; i < length; ++i) {
            if (!is_valid(&play_zone[x][y + i]) || has_nearby_ship(x, y + i, play_zone)) {
                return false;
            }
        }

        for (int i = 0; i < length; ++i) {
            play_zone[x][y + i] = ship->get_data();
        }
        
        ships_placed_count++;

        return true;
    }
}

bool remove_ship(int play_zone[7][9], Linked_ships* ship, int x, int y, bool vertical, int &ships_placed_count) {
    int length = ship->get_data();

    if (vertical) {
        for (int i = 0; i < length; ++i) {
            play_zone[x + i][y] = VALID;
        }
    } else {
        for (int i = 0; i < length; ++i) {
            play_zone[x][y + i] = VALID;
        }
    }
   
    ships_placed_count--;
    g_ship_deleting_counter++;

    return true;
}

bool place_all_ships(int play_zone[7][9], ship_vector& ship_list, int idx, int &ships_placed_count) {
    if (idx == (int)ship_list.size()) return true;

    Linked_ships* ship = ship_list[idx];
    
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 9; y++) {
            if (place_ship_if_possible(play_zone, ship, x, y, true, ships_placed_count)) {
                g_ship_placing_counter++;
                if (place_all_ships(play_zone, ship_list, idx + 1, ships_placed_count)) {
                    return true;
                }
                remove_ship(play_zone, ship, x, y, true, ships_placed_count);
            }
            if (place_ship_if_possible(play_zone, ship, x, y, false, ships_placed_count)) {
                g_ship_placing_counter++;
                if (place_all_ships(play_zone, ship_list, idx + 1, ships_placed_count)) {
                    return true;
                }
                remove_ship(play_zone, ship, x, y, false, ships_placed_count);
            }
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

    cout << endl;

    print(play_zone);
    cout << endl;

    int temp_zone[7][9]; 
    copy_zone(play_zone, temp_zone);

    int ships_placed_count = 0;

    if (place_all_ships(temp_zone, ship_list, 0, ships_placed_count)) {
        cout << "Ships placed successfully!" << endl;
    } else {
        cout << "ERROR." << endl;
    }

    print(temp_zone);
    cout << "Total ships placed: " << g_ship_placing_counter << endl;
    cout << "Total ships deleted: " << g_ship_deleting_counter << endl;
    cout << endl;

    for (Linked_ships* sh : ship_list) {
        delete sh;
    }

    cout << endl;
    return 0;
}
