#ifndef SHIP_STRUCT_H
#define SHIP_STRUCT_H

#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <algorithm>

/* ----------------------------------------------------------------------[<]-
    Class: Linked_ships

    Synopsis: this header was created for making ships like a 
    linked-list objects.
    ---------------------------------------------------------------------[>]-*/
struct Ship{
    int data;
    Ship *next;
};

class Linked_ships{
    Ship *head;

    public:
        Linked_ships(int len);
        ~Linked_ships();

        int get_data() const;
        Ship* get_head() const;
};

typedef std::vector<Linked_ships*> ship_vector;

#endif