#include "ship_struct.h"

Linked_ships :: Linked_ships(int len) {
    head = nullptr;

    for(int i = 0; i < len; i++){

        Ship *newShip = new Ship();
        newShip->data = len;
        newShip->next = head;
        head = newShip;
    }
}

Linked_ships :: ~Linked_ships(){
    Ship *current = head;

    while(current){

        Ship* temp = current;
        current = current->next;
        delete temp;
    }
}

int Linked_ships :: get_data() const {
    return head ? head->data : -1; 
}

Ship* Linked_ships :: get_head() const {
    return head; 
}
