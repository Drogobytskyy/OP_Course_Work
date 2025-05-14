#include "ship_struct.h"

/*
    constucting ships
*/
Linked_ships :: Linked_ships(int len) {
    head = nullptr;

    for(int i = 0; i < len; i++){

        Ship *newShip = new Ship();
        newShip->data = len;
        newShip->next = head;
        head = newShip;
    }
}

/*
    destructing ships
*/
Linked_ships :: ~Linked_ships(){
    Ship *current = head;

    while(current){

        Ship* temp = current;
        current = current->next;
        delete temp;
    }
}
// method that return number with what ship is represented
int Linked_ships :: get_data() const {
    return head ? head->data : -1; 
}

// return the start of the ship.
Ship* Linked_ships :: get_head() const {
    return head; 
}
